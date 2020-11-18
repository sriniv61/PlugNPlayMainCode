#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "move.h"
#include "uci.h"
#include "util.h"
#include "gen.h"
#include "main.h"
#include "buffer_funcs.h"

#define RESET -1

//void audio_out(){
//	audio_flag = 1;
//	TIM6->DIER |= TIM_DIER_UIE;
//	TIM6->CR1 |= TIM_CR1_CEN;
//	audio_flag = 0;
//	TIM6->DIER &= ~TIM_DIER_UIE;
//	TIM6->CR1 &= ~TIM_CR1_CEN;
//}

void uci_main(SPI_HandleTypeDef *hspi2) {
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

	int highlightedDests[64];
	int numhighlightedDests = 0;
	memset(highlightedDests, -1, sizeof(int) * 64);

	int next_audio_flag = 0;
	board_print(&board, cursorPos, highlightedDests);
	clear_feedback();

//	int pressNum = 0;
//	buttonPress test[15] = {UPress, APress, UPress, APress, UPress, UPress, UPress, UPress, APress, DPress, APress, DPress, DPress, DPress, APress};
	while (winner == RESET) {
		update_options(state);
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
		            clear_feedback();
		            update_feedback("INVALID", 7, 0);
		            update_feedback("PIECE", 5, 1);
					break;
				}
				state = waitingForSecond;
				clear_feedback();
				// display highlighted squares
				board_print(&board, cursorPos, highlightedDests);
				break;

			case waitingForSecond:
				destination = cursorPos;
//				destination = 16;
				for (index = 0; index < numhighlightedDests; index++) {
					if (destination == highlightedDests[index])
						break;
				}
				if (index == numhighlightedDests) {
		            clear_feedback();
		            update_feedback("INVALID", 7, 0);
		            update_feedback("DESTINATION", 11, 1);
		            next_audio_flag = 2;
				}
				// it's already being checked for a valid move, can simply check the piece and destination
				else if (PIECE(board.squares[source]) == PAWN
						&& ((destination < 8) || (destination > 55))) {
					state = waitingForThird;
		            clear_feedback();
		            update_feedback("SELECT", 6, 0);
		            update_feedback("PROMOTION", 9, 1);
				} else {
					// make the desired move
					// create a new move node (passing through the inputs and the current node)
					// Execute the new move on the actual board
					// Saving the move into currentMove
					moveList[curMoveNum].move.src = source;
					moveList[curMoveNum].move.dst = destination;
					moveList[curMoveNum].move.promotion = EMPTY;
					if(board.squares[destination] == EMPTY){
						next_audio_flag = 1;
					}
					else {
						next_audio_flag = 4;
					}
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
					memset(highlightedDests, -1, sizeof(Move) * 64);
					state = checking;
					clear_feedback();
					board_print(&board, cursorPos, highlightedDests);
				}
				break;
			default:
				break;
			}
			break;
		case BPress:
			// If the first selection has already been recieved, then we'll respond to this request
			if(state == waitingForFirst && curMoveNum > 0) {
				curMoveNum--;
				undo_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
			    clear_feedback();
	            update_feedback("LAST MOVE", 9, 0);
	            update_feedback("TAKEN BACK", 10, 1);
			}
			else if(state == waitingForFirst && curMoveNum == 0){
			    clear_feedback();
	            update_feedback("CANNOT", 6, 0);
	            update_feedback("TAKE BACK", 9, 1);
	            update_feedback("FIRST MOVE", 10, 2);
			}
			else if (state == waitingForSecond || state == waitingForThird) {
				// Reset source and selectedPiece to -1
				source = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * 64);
				// Reverting the game state
				state = waitingForFirst;
				clear_feedback();
	            update_feedback("MOVE ABORTED", 12, 0);
			}
			board_print(&board, cursorPos, highlightedDests);
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
				memset(highlightedDests, -1, sizeof(Move) * 64);
				state = checking;
				board_print(&board, cursorPos, highlightedDests);
				clear_feedback();
			}
			// User wants to resign
			else if (board.color){
				winner = 0;
				clear_feedback();
	            update_feedback("BLACK", 5, 0);
	            update_feedback("RESIGNS", 7, 1);
			}
			else {
				winner = 1;
				clear_feedback();
	            update_feedback("WHITE", 5, 0);
	            update_feedback("RESIGNS", 7, 1);
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
				memset(highlightedDests, -1, sizeof(Move) * 64);
				state = checking;
				board_print(&board, cursorPos, highlightedDests);
				clear_feedback();
			}
			// User wants to offer draw
			else if (board.color){
				clear_feedback();
	            update_feedback("BLACK OFFERS", 12, 0);
	            update_feedback("DRAW", 4, 1);
	            update_feedback("SE = ACCEPT", 11, 6);
	            update_feedback("ST = DECLINE", 12, 7);
				userInput = getButtonPress(hspi2, WHITE);
			    while(userInput != SePress && userInput != StPress) {
					userInput = getButtonPress(hspi2, WHITE);
			    }
			    if(userInput == SePress) {
				    winner = 2;
		            update_feedback("WHITE", 5, 3);
		            update_feedback("ACCEPTS", 7, 4);
		            HAL_Delay(2000);
		            clear_feedback();
			    }
			    else {
		            update_feedback("WHITE", 5, 3);
		            update_feedback("DECLINES", 8, 4);
		            HAL_Delay(2000);
		            clear_feedback();
			    }
			}
			else {
				clear_feedback();
	            update_feedback("WHITE OFFERS", 12, 0);
	            update_feedback("DRAW", 4, 1);
	            update_feedback("SE = ACCEPT", 11, 6);
	            update_feedback("ST = DECLINE", 12, 7);
				userInput = getButtonPress(hspi2, BLACK);
			    while(userInput != SePress && userInput != StPress) {
					userInput = getButtonPress(hspi2, BLACK);
			    }
			    if(userInput == SePress) {
				    winner = 2;
		            update_feedback("BLACK", 5, 3);
		            update_feedback("ACCEPTS", 7, 4);
		            HAL_Delay(2000);
					clear_feedback();
					//print draw
			    }
			    else {
		            update_feedback("BLACK", 5, 3);
		            update_feedback("DECLINES", 8, 4);
		            HAL_Delay(2000);
					clear_feedback();
					//black declines draw
			    }
			}
			break;
		case UPress:
			if(board.color == WHITE) {
				if (cursorPos <= 55)
					cursorPos += 8;
			}
			else {
				if (cursorPos >= 8)
					cursorPos -= 8;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		case DPress:
			if(board.color == WHITE) {
				if (cursorPos >= 8)
					cursorPos -= 8;
			}
			else {
				if (cursorPos <= 55)
					cursorPos += 8;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		case LPress:
			if(board.color == WHITE) {
				if (cursorPos % 8 != 0)
					cursorPos--;
			}
			else {
				if (cursorPos % 8 != 7)
					cursorPos++;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		case RPress:
			if(board.color == WHITE) {
				if (cursorPos % 8 != 7)
					cursorPos++;
			}
			else {
				if (cursorPos % 8 != 0)
					cursorPos--;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		case NoPress:
			break;
		}
		// After every move these things will be checked
		if (state == checking) {
			// Looking for checkmate
			// look for check before jumping into this to avoid wasting time
			if(is_check(&board)) {
				next_audio_flag = 3;
			}
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

			// Resetting state
			memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
			state = waitingForFirst;
			clear_feedback();
		}
		audio_flag = next_audio_flag;
		next_audio_flag = 0;
	}
	clear_feedback();
	if(winner == 2) {
        update_feedback("DRAW", 4, 1);
	}
	else if (winner == 1) {
        update_feedback("BLACK WINS", 10, 1);
        audio_flag = 5;
	}
	else {
        update_feedback("WHITE WINS", 10, 1);
        audio_flag = 5;
		//return to main menu
	}
	update_feedback("USER ONE", 8, 3);
	update_feedback("PRESS A", 7, 4);
	update_feedback("TO RETURN", 9, 5);
	update_feedback("TO MENU", 7, 6);

	while (getButtonPress(hspi2, 0) != APress);

}
