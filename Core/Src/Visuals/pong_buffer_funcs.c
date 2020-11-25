/*
 * pong_buffer_funcs.c
 *
 *  Created on: Nov 25, 2020
 *      Author: terrencerandall
 */

#include "pong_buffer_funcs.h"


/*
 * - Clearing the entire screen and displaying the playing options to the user in the middle of the screen
 *
 *	Up = move paddle up
 *	Down = move paddle down
 *	Start = pause the game (can quit to the main menu from here)
 */
void pongStartupScreen(){

}

/*
 * - Simply displaying that the user is in the pong screen
 * - That an APress will return them to the main menu
 * - That a BPress will return them to the game
 *
 */
void displayPauseScreen(){


}

/*
 * Function for displaying the score, the ball, and both paddles
 */
void displayGame(uint8_t player1Score, uint8_t player2Score, Object* Ball, Object * leftPaddle, Object * rightPaddle){

}

/*
 * -Utility function to clear the screen
 *
 * -Creating a white boarder around the playing area
 */

void clearScreen(){
	for(int column = 2; column < 198; column++) {
			for(int row = 2; row < 148; row++) {
				if (row == 2 || row == 147)
					framebuffer[row][column] = W;
				else if (column == 2 || column == 197)
					framebuffer[row][column] = W;
				else
					framebuffer[row][column] = B;
			}
		}
}
