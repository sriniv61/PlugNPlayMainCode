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

	// Initializing status variables
	uint8_t ball_in_play = 0;		// making zero before the game starts
	uint8_t previous_point = 0;		// 1 indicates that player 1 scored last, 2 that player 2 scored last
	uint8_t quit = 0;				// 0 means that neither player has quit

	// Variable to control the pace of the game
	uint8_t rallyCount = 0;			// keeping track of the number of collisions to increase speed of the ball

	// Initializing objects
	Object ball;
	Object leftPaddle;
	Object rightPaddle;

	memset(&ball, 0, sizeof(Object));
	memset(&leftPaddle, 0, sizeof(Object));
	memset(&rightPaddle, 0, sizeof(Object));

	ball.width = ball_size;
	ball.height = ball_size;
	leftPaddle.width = rightPaddle.width = PADDLE_WIDTH;
	leftPaddle.height = rightPaddle.height = PADDLE_HEIGHT;

	// Initializing user input variables
	buttonPress leftInput = NoPress;
	buttonPress rightInput = NoPress;

	// (VGA) Display the game controls before the game starts and ask for confirmation before continuing
	pongStartupScreen();

	while ( (leftInput == NoPress) && (rightInput = NoPress) ){
		leftInput = getButtonPress_noWait(hspi2, 0);
		rightInput = getButtonPress_noWait(hspi2, 1);
	}
	audio_flag = MENU_CURSOR;

	// Until we've found a winner or one of the players has decided to quit
	while ((playerOne_score < WINNING_SCORE) && (playerTwo_score < WINNING_SCORE) && (quit == 0)){

		// Resetting objects
			// Resetting ball to the middle of the field
		ball.topLeftX = BOARD_WIDTH/2 - 1;
		ball.topLeftY = BOARD_HEIGHT/2 + 1;
			// Resetting both paddles to the middle of their respective sides
		leftPaddle.topLeftX = 1;
		leftPaddle.topLeftY = BOARD_HEIGHT/2 + 7;
		rightPaddle.topLeftX = BOARD_WIDTH - 4;
		rightPaddle.topLeftY = BOARD_HEIGHT/2 + 7;

		// wait a bit after scoring to re-serve the ball
		HAL_Delay(1500);

		// Send the ball moving
			// Update the ball's momentum based on who scored last
		if (previous_point == 2){
			ball.x_momentum = -1;
			ball.y_momentum = -1;
		}
		else{
			ball.x_momentum = 1;
			ball.y_momentum = -1;
		}
			// Set ball_in_play
		ball_in_play = 1;

		// The rally logic
		while (ball_in_play && (quit == 0)){
			// Get player inputs
				leftInput = getButtonPress_noWait(hspi2, 0);

				rightInput = getButtonPress_noWait(hspi2, 1);

			// Handling the pause screen
				// If a player quits, set quit to 1
			if (leftInput == StPress){
				// (VGA) print the pause screen
				displayPauseScreen();
					// a = quit to main menu
					// b = return to game
				// Ask for inputs until they say "A" or "B"
				while ((leftInput != APress) && (leftInput != BPress) ) {
					leftInput = getButtonPress(hspi2, 0);
				}
				// Set the quit status if they decide to quit
				if(leftInput == APress){
					quit = 1;
				}
				else{
					// (VGA) print out the pong game again
					displayGame(playerOne_score, playerTwo_score, &ball, &leftPaddle, &rightPaddle);
				}
			}
			// Only allowing one user to pause per "clock cycle"
			else if (rightInput == StPress){
				// (VGA) print the pause screen
				displayPauseScreen();
					// a = quit to main menu
					// b = return to game
				// Ask for inputs until they say "A" or "B"
				while ((rightInput != APress) && (rightInput != BPress) ) {
					rightInput = getButtonPress(hspi2, 1);
				}
				// Set the quit status if they decide to quit
				if(rightInput == APress){
					quit = 1;
				}
				else{
					// (VGA) print out the pong game again
					displayGame(playerOne_score, playerTwo_score, &ball, &leftPaddle, &rightPaddle);
				}
			}

			// Do the rest of the game logic if the user is not quitting
			if (quit == 0) {
				// Update player paddle objects
					updatePaddleLocation(&leftPaddle, leftInput);
					updatePaddleLocation(&rightPaddle, rightInput);

				// Check for ball and paddle collision
					// if the ball is on the left
					if (ball.topLeftX < BOARD_WIDTH / 2)
						checkBallPaddleCollision(&leftPaddle, &ball, &rallyCount, 0);
					// if the ball is on the right
					else
						checkBallPaddleCollision(&rightPaddle, &ball, &rallyCount, 1);

				// Update the ball's position
					updateBallPosition(&ball);

				// Check if the ball has gone out of bounds on the left side
				if (ball.topLeftX < 1){
					ball_in_play = 0;
					// Update the user scores
					playerTwo_score++;
					previous_point = 2;
					// Using the chess invalid sound as the sound effect for a point
					audio_flag = INVALID;
				}
				// Check if the ball has gone out of bounds on the right side
				else if (ball.topLeftX + 2 > BOARD_WIDTH - 1){ // this calculation might be wrong
						ball_in_play = 0;
						// Update the user scores
						playerOne_score++;
						previous_point = 1;
						// Using the chess invalid sound as the sound effect for a point
						audio_flag = INVALID;
					}

				// (VGA) Display the score on the screen (always want this to be showing at the top of the screen)
				displayGame(playerOne_score, playerTwo_score, &ball, &leftPaddle, &rightPaddle);
			}
		}
	}

	// If a user has quit
	if (quit == 1){
		// (VGA) displaying the quitting message
			// Prompt either user to press A to return to main 
		gameOverDisplay(0);
		leftInput = NoPress;
		rightInput = NoPress;
		while ( (leftInput != BPress) && (rightInput != BPress)){
			leftInput = getButtonPress_noWait(hspi2, 0);
			rightInput = getButtonPress_noWait(hspi2, 1);
		}
	}
	// If a user has won
	else{
		// (VGA) Displaying the winning message
			// Giving the winning sound
			audio_flag = WINNER;
		// if user one won
		if (playerOne_score == WINNING_SCORE){
			gameOverDisplay(1);
			leftInput = NoPress;
			while(leftInput != BPress) {
				leftInput = getButtonPress_noWait(hspi2, 0);
			}
		}
		// if user two won
		else{
			gameOverDisplay(2);
			rightInput = NoPress;
			while (rightInput != BPress) {
				rightInput = getButtonPress_noWait(hspi2, 1);
			}
		}

	}
}
/*
 * The function needs to make sure that there is still space left to move
 * And if there's not space left to move, it needs to make sure that the object is as far as it can go
 *
 * The paddle's y_momentum will be used to change the y_momentum of the ball
 */
void updatePaddleLocation(Object * paddle, buttonPress curInput){

	// Moving Down
	if (curInput == DPress){
		// If the paddle can't go any further down
		if (paddle->topLeftY - paddle->height <= 0){
			paddle->topLeftY = paddle->height;
		}
		else{
			paddle->topLeftY += -1;
		}
		// Set momentum to down regardless
		paddle->y_momentum = -1;
	}
	// Moving Up
	else if (curInput == UPress){
		// if the paddle can't go any further up
		if (paddle->topLeftY >= BOARD_HEIGHT){
			paddle->topLeftY = BOARD_HEIGHT;
			}
		else{
			paddle->topLeftY += 1;
		}
		// Set momentum to up regardless
		paddle->y_momentum = 1;
	}
	// paddle is not moving
	else{
		paddle->y_momentum = 0;
	}

	return;
}

void checkBallPaddleCollision(Object * paddle, Object * ball, uint8_t * rallyCount, uint8_t rightSide){

	// if there is a collision then set this to 1
	uint8_t collision = 0;

	/*
	 * What's being checked for:
	 * - the ball has reached the paddle
	 * - the ball is not above the paddle
	 * - the ball is not beneath the paddle
	 */

	if(rightSide){
		if ( (paddle->topLeftX == (ball->topLeftX + ball->width) || paddle->topLeftX + 1 == (ball->topLeftX + ball->width) )
			&& ( (ball->topLeftY - paddle->topLeftY) < ball->height)
			&&	( (paddle->topLeftY - ball->topLeftY) < paddle->height)
			 ) {
			collision = 1;
		}
	}
	else{
		if ( (ball->topLeftX  == (paddle->topLeftX + paddle->width) || ball->topLeftX - 1 == (paddle->topLeftX + paddle->width) )
			&& ( (ball->topLeftY - paddle->topLeftY) < ball->height)
			&&	( (paddle->topLeftY - ball->topLeftY) < paddle->height)
			 ) {
			collision = 1;
		}
	}

	if (collision){
		// Increment the rally count
		*rallyCount = *rallyCount + 1;
		// Just reverse the x momentum
		ball->x_momentum = ball->x_momentum * -1;
		// If the paddle was moving up, pushing the ball up faster
		if (paddle->y_momentum == 1){
			if (ball->y_momentum < MAX_BALL_MOMENTUM)
				ball->y_momentum += 1;
		}
		else if (paddle->y_momentum == -1){
			if (ball->y_momentum > -MAX_BALL_MOMENTUM)
				ball->y_momentum -= 1;
		}

		// Setting sound to main menu cursor sound
		audio_flag = MENU_CURSOR;
	}

	return;
}

void updateBallPosition(Object * ball){

	// IF the ball collided with the top of the screen
	if (ball->topLeftY >= BOARD_HEIGHT) {
		// Flip the momentum
		ball->y_momentum = -1;
		ball->topLeftY = BOARD_HEIGHT - 1;
	}
	// If the ball collided with the bottom
	else if (ball->topLeftY - ball->height <= 0){
		ball->y_momentum = 1;
		ball->topLeftY = ball->height + 1;
	}
	// No collision
	else{
		ball->topLeftY += ball->y_momentum;
	}
	// The x momentum will always be added like this
	ball->topLeftX += ball->x_momentum;


	return;
}

