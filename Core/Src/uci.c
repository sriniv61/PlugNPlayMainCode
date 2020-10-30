#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "move.h"
#include "uci.h"
#include "util.h"
#include "gen.h"
#include "main.h"

#define RESET -1

void uci_main(SPI_HandleTypeDef *hspi2, UART_HandleTypeDef *huart2) {
    bb_init();
//    return;
	Board board;
	actualUndo moveList[MAX_MOVES];
	memset(moveList, 0, sizeof(moveList));
	int curMoveNum = 0;
	setbuf(stdout, NULL);
	board_reset(&board);

	int winner = RESET; // 0 = white; 1 = black; 2 = draw
	int cursorPos = 0;
	buttonPress userInput = APress;
	gameState state = waitingForFirst;

	int source = RESET;
	int destination = RESET;
	unsigned char promotion = RESET;
	int index;

	Move legalMoves[MAX_MOVES];
	int numLegalMoves = 0;
	memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);

	int highlightedDests[MAX_MOVES];
	int numhighlightedDests = 0;
	memset(highlightedDests, -1, sizeof(int) * MAX_MOVES);

//	Move *currentMove = malloc(sizeof(Move));

	board_print(&board, huart2, cursorPos);
	char feedback[66] = {0};

//	int pressNum = 0;
//	buttonPress test[15] = {UPress, APress, UPress, APress, UPress, UPress, UPress, UPress, APress, DPress, APress, DPress, DPress, DPress, APress};
	while (winner == RESET) {
//		userInput = test[pressNum];
//		pressNum = pressNum + 1;
jumpBack:
		userInput = getButtonPress(hspi2, board.color);
		if((state == waitingForThird) && ((userInput != SePress) && (userInput != StPress) && (userInput != BPress)))
				goto jumpBack;
		switch (userInput) {
		case APress:
			switch (state) {
			case waitingForFirst:
				source = cursorPos;
				numLegalMoves = gen_legal_moves(&board, legalMoves);
				numhighlightedDests = 0;
				for (int i = 0; i < numLegalMoves; i++) {
					if (legalMoves[i].src == source) {
						highlightedDests[numhighlightedDests++] =
								legalMoves[i].dst;
					}
				}
				if (numhighlightedDests == 0) {
					// Jump to error state
					// Tell user their selection was invalid
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "Invalid piece selection made, try again.\r\n");
		            HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
					break;
				}
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Piece selected\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				state = waitingForSecond;
				// display highlighted squares
				break;

			case waitingForSecond:
				destination = cursorPos;
				for (index = 0; index < numhighlightedDests; index++) {
					if (destination == highlightedDests[index])
						break;
				}
				if (index == numhighlightedDests) {
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "Invalid destination selection made, try again.\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				}
				// it's already being checked for a valid move, can simply check the piece and destination
				else if (PIECE(board.squares[source]) == PAWN
						&& ((destination < 8) || (destination > 55))) {
					//promotion
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "SELECT: QUEEN\r\nSTART: KNIGHT\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
					state = waitingForThird;
				} else {
					// make the desired move
					// create a new move node (passing through the inputs and the current node)
					// Execute the new move on the actual board
					// Saving the move into currentMove
					moveList[curMoveNum].move.src = source;
					moveList[curMoveNum].move.dst = destination;
					moveList[curMoveNum].move.promotion = EMPTY;
					do_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
					curMoveNum++;

					// Reset selectedPiece, source, destination, and promotion to -1
					source = destination = promotion = RESET;
					// Then free the valid move list
					/*printf("Move list: \n");
					 for(index = 0; index < numLegalMoves; index++){
					 printf("src: %d, dest: %d\n", legalMoves[index].src, legalMoves[index].dst);
					 }*/
					memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
					memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
					state = checking;
					board_print(&board, huart2, cursorPos);
				}
				break;
			default:
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Please select a promotion option.\r\nSELECT: QUEEN\r\nSTART: KNIGHT\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
			}
			// After every move these things will be checked
			if (state == checking) {
				// Looking for checkmate
				// look for check before jumping into this to avoid wasting time
				numLegalMoves = gen_legal_moves(&board, legalMoves);
				if (numLegalMoves == 0) {
					if (is_check(&board)) {
						//checkmate
						if (board.color == BLACK)
							winner = 0;
						else
							winner = 1;
					} else {
						//stalemate
						winner = 2;
					}
				}
				// Checking for 3 fold repitions
				// winner = checkForRepetition(currentMove);
				// Looking for ...

				// Resetting state
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				state = waitingForFirst;
			}
			break;
		case BPress:
			// If the first selection has already been recieved, then we'll respond to this request
			if(state == waitingForFirst && curMoveNum > 0) {
				curMoveNum--;
				undo_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Takeback move\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
			}
			else if(state == waitingForFirst && curMoveNum == 0){
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Cannot takeback first move\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
			}
			else if (state == waitingForSecond || state == waitingForThird) {
				// Reset source and selectedPiece to -1
				source = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);

				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Move canceled\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				// Reverting the game state
				state = waitingForFirst;
			}
			break;
		case SePress:
			if(state == waitingForThird) {
				// make the desired move
				// create a new move node (passing through the inputs and the current node)
				// Execute the new move on the actual board
				// Saving the move into currentMove
				moveList[curMoveNum].move.src = source;
				moveList[curMoveNum].move.dst = destination;
				moveList[curMoveNum].move.promotion = QUEEN;
				do_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
				curMoveNum++;
				// Reset selectedPiece, source, destination, and promotion to -1
				source = destination = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
				state = checking;
				board_print(&board, huart2, cursorPos);
			}
			// User wants to resign
			else if (board.color){
				//resign text
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Black resigns\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				winner = 0;
			}
			else {
				//resign text
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "White resigns\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				winner = 1;
			}
			break;
		case StPress:
			if(state == waitingForThird) {
				// make the desired move
				// create a new move node (passing through the inputs and the current node)
				// Execute the new move on the actual board
				// Saving the move into currentMove
				moveList[curMoveNum].move.src = source;
				moveList[curMoveNum].move.dst = destination;
				moveList[curMoveNum].move.promotion = KNIGHT;
				do_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
				curMoveNum++;
				// Reset selectedPiece, source, destination, and promotion to -1
				source = destination = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
				state = checking;
				board_print(&board, huart2, cursorPos);
			}
			// User wants to offer draw
			else if (board.color){
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "Black offers draw\r\nSELECT: ACCEPT\r\nSTART: DECLINE\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				userInput = getButtonPress(hspi2, WHITE);
			    while(userInput != SePress && userInput != StPress) {
					userInput = getButtonPress(hspi2, WHITE);
			    }
			    if(userInput == SePress) {
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "White accepts draw\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				    winner = 2;
			    }
			    else {
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "White declines draw\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
			    }
			}
			else {
				memset(feedback, 0, sizeof(feedback));
				strcpy(feedback, "White offers draw\r\nSELECT: ACCEPT\r\nSTART: DECLINE\r\n");
			    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				userInput = getButtonPress(hspi2, BLACK);
			    while(userInput != SePress && userInput != StPress) {
					userInput = getButtonPress(hspi2, BLACK);
			    }
			    if(userInput == SePress) {
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "Black accepts draw\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
				    winner = 2;
			    }
			    else {
					memset(feedback, 0, sizeof(feedback));
					strcpy(feedback, "Black declines draw\r\n");
				    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
			    }
			}
			break;
		case UPress:
			if (cursorPos <= 55)
				cursorPos += 8;
			board_print(&board, huart2, cursorPos);
			break;
		case DPress:
			if (cursorPos >= 8)
				cursorPos -= 8;
			board_print(&board, huart2, cursorPos);
			break;
		case LPress:
			if (cursorPos % 8 != 0)
				cursorPos--;
			board_print(&board, huart2, cursorPos);
			break;
		case RPress:
			if (cursorPos % 8 != 7)
				cursorPos++;
			board_print(&board, huart2, cursorPos);
			break;
		case NoPress:
			break;
		}
	}
	if(winner == 2) {
		//display draw text on screen
		memset(feedback, 0, sizeof(feedback));
		strcpy(feedback, "Draw\r\n");
	    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
		//return to main menu
	}
	else if (winner == 1) {
		//display winner text on screen
		memset(feedback, 0, sizeof(feedback));
		strcpy(feedback, "Black wins\r\n");
	    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
	    HAL_Delay(1000);
		//return to main menu
	}
	else {
		//display winner text on screen
		memset(feedback, 0, sizeof(feedback));
		strcpy(feedback, "White wins\r\n");
	    HAL_UART_Transmit(huart2, (uint8_t *)(feedback), sizeof(feedback), HAL_MAX_DELAY);
	    HAL_Delay(1000);
		//return to main menu
	}
}
