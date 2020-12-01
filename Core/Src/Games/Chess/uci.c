#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "move.h"
#include "uci.h"
#include "util.h"
#include "gen.h"
#include "main.h"
#include "../../Visuals/buffer_funcs.h"
#include "../../External/audio.h"


void uci_main(SPI_HandleTypeDef *hspi2) {
	// Initialize the game variables (which are globally located) and initializing the board
    bb_init();
	Board board;
	board_reset(&board);

	// Initializing various lists
	actualUndo moveList[MAX_MOVES];
	memset(moveList, 0, sizeof(moveList));
	int curMoveNum = 0;

	Move legalMoves[MAX_MOVES];
	int numLegalMoves = 0;
	memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);

	int highlightedDests[64];
	int numhighlightedDests = 0;
	memset(highlightedDests, -1, sizeof(int) * 64);

	// Initializing the winner to nobody, and the cursor to the zero position
	int winner = RESET; // 0 = white; 1 = black; 2 = draw
	gameState state = pieceSelection;
	int cursorPos = 0;

	// Creating a userINput variable
	buttonPress userInput = APress;

	// Initializing "status" variables for piece movements
	int source = RESET;
	int destination = RESET;
	unsigned char promotion = RESET;

	// Creating index variable for "for-loops"
	int index;

	// Creating a variable to act as a buffer, so that audio can be set in a single place
	int next_audio_flag = 0;

	// Printing the board and clearing feedback from the right side of the screen prior to the start of the match
	board_print(&board, cursorPos, highlightedDests);
	clear_feedback();

	while (winner == RESET) {
		// Update the options according to the state and promotion value
		update_options(state, promotion);

	// Small loop to continuously get user input if expecting a promotion
jumpBack:
		userInput = getButtonPress(hspi2, board.color);
		if((state == promotionSelection) && (
				(userInput != DPress) &&
				(userInput != UPress) &&
				(userInput != BPress) &&
				(userInput != APress) ) )
				goto jumpBack;

		// The state machine is based entirely on the input given by the user
		switch (userInput) {
		case APress:
			switch (state) {

			case pieceSelection:
				source = cursorPos;
				numLegalMoves = gen_legal_moves(&board, legalMoves);
				numhighlightedDests = 0;
				for (int i = 0; i < numLegalMoves; i++) {
					if (legalMoves[i].src == source) {
						highlightedDests[numhighlightedDests++] =
								legalMoves[i].dst;
					}
				}
				// The user selected a place with either no piece or no available destinations from that piece
				if (numhighlightedDests == 0) {
		            clear_feedback();
		            update_feedback("INVALID", 7, 0);
		            update_feedback("PIECE", 5, 1);
		            next_audio_flag = INVALID;
					break;
				}
				state = destinationSelection;
				clear_feedback();
				board_print(&board, cursorPos, highlightedDests);
				break;

			case destinationSelection:
				destination = cursorPos;
				for (index = 0; index < numhighlightedDests; index++) {
					if (destination == highlightedDests[index])
						break;
				}
				// The user selected a destination that is not in the list of viable destinations
				if (index == numhighlightedDests) {
		            clear_feedback();
		            update_feedback("INVALID", 7, 0);
		            update_feedback("DESTINATION", 11, 1);
		            next_audio_flag = INVALID;
				}
				// handling pawn promotions
				else if (PIECE(board.squares[source]) == PAWN
						&& ((destination < 8) || (destination > 55))) {
					state = promotionSelection;
		            clear_feedback();
		            update_feedback("SELECT", 6, 0);
		            update_feedback("PROMOTION", 9, 1);
		            update_feedback("CHANGE WITH", 11, 2);
		            update_feedback("UP OR DOWN", 10, 3);

		            // initializing promotion as queen
		            promotion = QUEEN;

				}
				else {
					// make the desired move
					// create a new move node (passing through the inputs and the current node)
					// Execute the new move on the actual board
					// Saving the move into currentMove
					moveList[curMoveNum].move.src = source;
					moveList[curMoveNum].move.dst = destination;
					moveList[curMoveNum].move.promotion = EMPTY;
					if(board.squares[destination] == EMPTY){
						next_audio_flag = MOVE;
					}
					else {
						next_audio_flag = CAPTURE;
					}
					do_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
					curMoveNum++;

					// Reset selectedPiece, source, destination, and promotion to -1
					source = destination = promotion = RESET;
					// Then clear the valid move list and highlighted destination list
					memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
					memset(highlightedDests, -1, sizeof(Move) * 64);
					state = checking;
					clear_feedback();
					board_print(&board, cursorPos, highlightedDests);
				}
				break;

			case promotionSelection:
				// The choosing of the promotion is controlled below by the UPress and DPress logic
				// there the promotion value is determined, and here the move is executed after an
				// APress is received

				// make the desired move
				// create a new move node (passing through the inputs and the current node)
				// Execute the new move on the actual board
				// Saving the move into currentMove
				moveList[curMoveNum].move.src = source;
				moveList[curMoveNum].move.dst = destination;
				moveList[curMoveNum].move.promotion = promotion;
				do_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
				curMoveNum++;
				// Reset selectedPiece, source, destination, and promotion to -1
				source = destination = promotion = RESET;
				// Then clear the valid move list and highlighted destination list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * 64);
				state = checking;
				board_print(&board, cursorPos, highlightedDests);
				clear_feedback();
				break;

			default:
				break;
			}
			break;

		case BPress:
			// If the first selection has already been received, then we'll respond to this request
			if(state == pieceSelection && curMoveNum > 0) {
				curMoveNum--;
				undo_move(&board, &(moveList[curMoveNum].move), &(moveList[curMoveNum].undo));
			    clear_feedback();
	            update_feedback("LAST MOVE", 9, 0);
	            update_feedback("TAKEN BACK", 10, 1);
			}
			else if(state == pieceSelection && curMoveNum == 0){
			    clear_feedback();
	            update_feedback("CANNOT", 6, 0);
	            update_feedback("TAKE BACK", 9, 1);
	            update_feedback("FIRST MOVE", 10, 2);
	            next_audio_flag = INVALID;
			}
			else if (state == destinationSelection || state == promotionSelection) {
				// Reset source and selectedPiece to -1
				source = RESET;
				// Then clear the valid move list and highlighted destinations list
				memset(legalMoves, -1, sizeof(Move) * MAX_MOVES);
				memset(highlightedDests, -1, sizeof(Move) * 64);
				// Reverting the game state
				state = pieceSelection;
				clear_feedback();
	            update_feedback("MOVE ABORTED", 12, 0);
			}
			board_print(&board, cursorPos, highlightedDests);
			break;

		case SePress:
			// User wants to resign
			if (board.color){
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
			// User wants to offer draw
			if (board.color){
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
			// Changing promotion piece
			if (state == promotionSelection){
				if (promotion < QUEEN)
					promotion++;
			}
			// Moving cursor on white's turn
			else if(board.color == WHITE) {
				if (cursorPos <= 55)
					cursorPos += 8;
			}
			// Moving cursor on black's turn (because of inverted screen)
			else {
				if (cursorPos >= 8)
					cursorPos -= 8;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		case DPress:
			// Changing promotion piece
			if (state == promotionSelection){
				if (promotion > KNIGHT)
					promotion--;
			}
			// Moving cursor on white's turn
			else if(board.color == WHITE) {
				if (cursorPos >= 8)
					cursorPos -= 8;
			}
			// Moving cursor on black's turn (because of inverted screen)
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
			// Different due to inverted screen
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
			// Different due to inverted screen
			else {
				if (cursorPos % 8 != 0)
					cursorPos--;
			}
			board_print(&board, cursorPos, highlightedDests);
			break;
		// here for safety
		case NoPress:
			break;
		}
		// After every move these things will be checked
		if (state == checking) {
			// Looking for checkmate
			// If there is a check, trigger the check sound
			if(is_check(&board)) {
				next_audio_flag = CHECK;
			}
			numLegalMoves = gen_legal_moves(&board, legalMoves);
			if (numLegalMoves == 0) {
				next_audio_flag = 0;
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
			state = pieceSelection;
			clear_feedback();
		}
	// Setting the audio flag to it's buffered value and resetting the buffer variable
	audio_flag = next_audio_flag;
	next_audio_flag = 0;

	}

	// Exiting the while loop if we've found a winner or a stalemate has occurred

	if(winner == 2) {
        update_feedback("DRAW", 4, 2);
	}
	else if (winner == 1) {
        update_feedback("BLACK WINS", 10, 2);
        audio_flag = WINNER;
	}
	else {
        update_feedback("WHITE WINS", 10, 2);
        audio_flag = WINNER;
		//return to main menu
	}

	// Leaving the board on the screen until user #1 presses a
	update_feedback("USER ONE", 8, 4);
	update_feedback("PRESS A", 7, 5);
	update_feedback("TO RETURN", 9, 6);
	update_feedback("TO MENU", 7, 7);

	while (getButtonPress(hspi2, 0) != APress);

}
