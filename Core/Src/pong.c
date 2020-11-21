/*
 * pong.c
 *
 *  Created on: Nov 21, 2020
 *      Author: terrencerandall
 */

#include "pong.h"

void pong_game (SPI_HandleTypeDef *hspi2) {
	// Initializing player scores
	uint8_t playerOne_score = 0;
	uint8_t playerTwo_score = 0;
	uint8_t quit = 0;

	// Initializing status variables
	uint8_t ball_in_play = 0;		// making zero before the game starts
	uint8_t previous_point = 0;		// 1 indicates that player 1 scored last, 2 that player 2 scored last

	// Initializing physical features (these coordinates are the top right of the object)
		// The far bottom left of the board will be location 0,0
		// The board is only height 144 by width 194
	uint8_t ballLocation[2] = {0};		// top left x,y coordinates
	uint8_t playerOnePaddle[2] = {0}; 	// Leaving one pixel between the paddle and the end of the playing screen
	uint8_t playerTwoPaddle[2] = {0};	// Leaving one pixel between the paddle and the end of the playing screen

	// Initializing user input variables
		// need an extra one to account for momentum of the paddle




	// Until we've found a winner or one of the players has decided to quit
	while ((playerOne_score < 7) && (playerTwo_score < 7) && (quit == 0)){

		// Resetting objects
			// Resetting ball to the middle of the field
		ballLocation[0] = 99;
		ballLocation[1] = 76;
			// Resetting both paddles to the middle of their respective sides
		playerOnePaddle[0] = 1;
		playerOnePaddle[1] = 82;
		playerTwoPaddle[0] = 193;
		playerTwoPaddle[1] = 82;

		// The rally logic
		while (ball_in_play){

		}

		// Displaying the score


	}

	// Displaying the winning message and sound if there's a winner, otherwise the quitting message

	// Asking for feedback to return to the main menu

}
