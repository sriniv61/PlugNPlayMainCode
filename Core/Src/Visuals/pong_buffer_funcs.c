/*
 * pong_buffer_funcs.c
 *
 *  Created on: Nov 25, 2020
 *      Author: terrencerandall
 */

#include "pong_buffer_funcs.h"
#include "vga.h"


/*
 * - Clearing the entire screen and displaying the playing options to the user in the middle of the screen
 *
 *	Up = move paddle up
 *	Down = move paddle down
 *	Start = pause the game (can quit to the main menu from here)
 */
void pongStartupScreen(){
	clearScreen();
	print_string("WELCOME TO PONG", 15, 0, 15, W, B);
	print_string("UP = MOVE PADDLE UP", 19, 3, 13, W, B);
	print_string("DOWN = MOVE PADDLE DOWN", 23, 4, 11, W, B);
	print_string("START = PAUSE", 13, 5, 16, W, B);
	print_string("PRESS ANYTHING TO PLAY", 22, 7, 12, W, B);
}

/*
 * - Simply displaying that the user is in the pong screen
 * - That an APress will return them to the main menu
 * - That a BPress will return them to the game
 *
 */
void displayPauseScreen(){
	//clearScreen();
	print_string("GAME PAUSED", 11, 1, 18, W, B);
	print_string("A = QUIT TO MENU", 16, 3, 15, W, B);
	print_string("B = RETURN TO GAME", 18, 4, 14, W, B);
}

/*
 * Function for displaying the score, the ball, and both paddles
 */
void displayGame(uint8_t player1Score, uint8_t player2Score, Object* ball, Object * leftPaddle, Object * rightPaddle){

	// Checking for drawNewFrame Ensures that the visuals look smooth (only necessary sometimes)
	if(drawNewFrame){
		clearScreen();
		printScore(player1Score, player2Score);
		printObject(leftPaddle);
		printObject(rightPaddle);
		printObject(ball);

		drawNewFrame = 0;
	}
	// if we can't draw, throw a delay so that the game doesn't go too fast for the user
	else
		HAL_Delay(10);
}

void gameOverDisplay(uint8_t player){
	// if player 1 won
	if (player == 1){
		print_string("PLAYER 1 WINS", 13, 3, 17, W, B);
		print_string("PLAYER 1 PRESS B", 16, 6, 15, W, B);
		print_string("TO RETURN TO MENU", 17, 7, 15, W, B);
	}
	// if player 2 won
	else if (player == 2){
		print_string("PLAYER 2 WINS", 13, 3, 17, W, B);
		print_string("PLAYER 2 PRESS B", 16, 6, 15, W, B);
		print_string("TO RETURN TO MENU", 17, 7, 15, W, B);
	}
	// someone quit
	else{
		// clear screen since the score doesn't matter anymore
		clearScreen();
		print_string("EXITING GAME", 12, 3, 18, W, B);
		print_string("PRESS B", 7, 6, 20, W, B);
		print_string("TO RETURN TO MENU", 17, 7, 15, W, B);
	}


}

/*
 * -Utility function to clear the screen
 *
 * -Creating a white boarder around the playing area
 */
void clearScreen(){
	for(int column = 0; column < 200; column++) {
			for(int row = 0; row < 150; row++) {
				if (row == 2 || row == 147)
					framebuffer[row][column] = W;
				else if (column == 2 || column == 197)
					framebuffer[row][column] = W;
				else
					framebuffer[row][column] = B;
			}
		}
}

/*
 * - Utility function to print the score
 */
void printScore(uint8_t left, uint8_t right){
	switch(left){
		case 0:
			print_string("0", 1, 0, 21, W, B);
			break;
		case 1:
			print_string("1", 1, 0, 21, W, B);
			break;
		case 2:
			print_string("2", 1, 0, 21, W, B);
			break;
		case 3:
			print_string("3", 1, 0, 21, W, B);
			break;
		case 4:
			print_string("4", 1, 0, 21, W, B);
			break;
		case 5:
			print_string("5", 1, 0, 21, W, B);
			break;
		case 6:
			print_string("6", 1, 0, 21, W, B);
			break;
		case 7:
			print_string("7", 1, 0, 21, W, B);
			break;
		case 8:
			print_string("8", 1, 0, 21, W, B);
			break;
		case 9:
			print_string("9", 1, 0, 21, W, B);
			break;
		default:
			print_string("ERR", 3, 0, 21, W, B);
			break;
	}

	switch(right){
		case 0:
			print_string("0", 1, 0, 25, W, B);
			break;
		case 1:
			print_string("1", 1, 0, 25, W, B);
			break;
		case 2:
			print_string("2", 1, 0, 25, W, B);
			break;
		case 3:
			print_string("3", 1, 0, 25, W, B);
			break;
		case 4:
			print_string("4", 1, 0, 25, W, B);
			break;
		case 5:
			print_string("5", 1, 0, 25, W, B);
			break;
		case 6:
			print_string("6", 1, 0, 25, W, B);
			break;
		case 7:
			print_string("7", 1, 0, 25, W, B);
			break;
		case 8:
			print_string("8", 1, 0, 25, W, B);
			break;
		case 9:
			print_string("9", 1, 0, 25, W, B);
			break;
		default:
			print_string("ERR", 3, 0, 25, W, B);
			break;
	}

}

/*
 * - Utility function to print an object to the screen (works for paddles and balls)
 */
void printObject(Object * thing){
	uint8_t startingRow = BOARD_HEIGHT - thing->topLeftY;

	for(int column = thing->topLeftX; column < thing->topLeftX + thing->width; column++) {
		for(int row = startingRow; row < startingRow + thing->height; row++) {
				framebuffer[row + 3][column + 3] = W;
		}
	}
}

