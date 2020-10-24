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
//    bb_init();
//    return;
	Board board;
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

	Move *currentMove = malloc(sizeof(Move));

	board_print(&board, huart2, cursorPos);
	while (winner == RESET) {
		userInput = getButtonPress(hspi2, 0);
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
					printf("Invalid selection made, try again.\n");
					break;
				}
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
					printf("Invalid selection made, try again\n");
				}
				// it's already being checked for a valid move, can simply check the piece and destination
				else if (PIECE(board.squares[source]) == PAWN
						&& ((destination < 8) || (destination > 55))) {
					//promotion
					state = waitingForThird;
				} else {
					// make the desired move
					// create a new move node (passing through the inputs and the current node)
					// Execute the new move on the actual board
					// Saving the move into currentMove
					currentMove->src = source;
					currentMove->dst = destination;
					currentMove->promotion = EMPTY;
					make_move(&board, currentMove);
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
				// Hanlding pawn promotions
			case waitingForThird:
				// For pawn promotions Knight = 2, Bishop = 3, Rook = 4, Queen = 5
				promotion = (unsigned char) userInput;

				// make the desired move
				// create a new move node (passing through the inputs and the current node)
				// Execute the new move on the actual board
				// Saving the move into currentMove
				currentMove->src = source;
				currentMove->dst = destination;
				currentMove->promotion = promotion;
				make_move(&board, currentMove);
				// Reset selectedPiece, source, destination, and promotion to -1
				source = destination = promotion = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
				state = checking;
				board_print(&board, huart2, cursorPos);
				break;

			default:
				printf(
						"invalid state or jumped into checking state too early\n");
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
			if (state == waitingForSecond) {
				// Reset source and selectedPiece to -1
				source = RESET;
				// Then free the valid move list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * MAX_MOVES);
				// Reverting the game state
				state = waitingForFirst;
			} else if (state == waitingForThird) {
				// reset destination
				destination = RESET;
				// Reverting the game state
				state = waitingForSecond;
			}
			break;
		case SePress:
			// User wants to resign
			if (board.color)
				winner = 0;
			else
				winner = 1;
			break;
		case StPress:
			// User wants to offer draw
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
	if (winner) {
		//display winner text on screen
		//return to main menu
	} else {
		//display winner text on screen
		//return to main menu
	}
}
