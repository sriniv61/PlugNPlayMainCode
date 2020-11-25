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
	uint32_t gameSpeed = 1000; 		// This variable controls how fast the game goes

	// Initializing objects
	Object ball;
	Object leftPaddle;
	Object rightPaddle;

	memset(&ball, 0, sizeof(Object));
	memset(&leftPaddle, 0, sizeof(Object));
	memset(&rightPaddle, 0, sizeof(Object));

	ball.width = BALL_WIDTH;
	ball.height = BALL_HEIGHT;
	leftPaddle.width = rightPaddle.width = PADDLE_WIDTH;
	leftPaddle.height = rightPaddle.height = PADDLE_HEIGHT;

	// Initializing user input variables
		// need an extra one to account for momentum of the paddle to allow it to move faster
	buttonPress leftInput = NoPress;
	buttonPress leftPrevInput = NoPress;
	buttonPress leftPrevPrevInput = NoPress;
	buttonPress rightInput = NoPress;
	buttonPress rightPrevInput = NoPress;
	buttonPress rightPrevPrevInput = NoPress;

	// (VGA) Display the game controls before the game starts and ask for confirmation before continuing
		/*
			Up = move paddle up
			Down = move paddle down
			Start = pause the game (can quit to the main menu from here)
		*/

	// Until we've found a winner or one of the players has decided to quit
	while ((playerOne_score < WINNING_SCORE) && (playerTwo_score < WINNING_SCORE) && (quit == 0)){

		// Resetting objects
			// Resetting ball to the middle of the field
		ball.topLeftX = BOARD_WIDTH/2 - 1;
		ball.topLeftY = BOARD_HEIGHT/2 +1;
			// Resetting both paddles to the middle of their respective sides
		leftPaddle.topLeftX = 1;
		leftPaddle.topLeftY = BOARD_HEIGHT/2 + 7;
		rightPaddle.topLeftX = BOARD_WIDTH - 1; 
		leftPaddle.topLeftY = BOARD_HEIGHT/2 + 7;

		// wait after scoring to re-serve the ball
		HAL_Delay(2000);
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
			// Set ball_in_play to 1
		ball_in_play = 1;

		// The rally logic
		while (ball_in_play && (quit == 0)){
			// Get player inputs
				leftPrevPrevInput = leftPrevInput;
				leftPrevInput = leftInput;
				leftInput = getButtonPress_noWait(hspi2, 0);

				rightPrevPrevInput = rightPrevInput;
				rightPrevInput = rightInput;
				rightInput = getButtonPress_noWait(hspi2, 1);
				// Here we'll handle the pause screen
					// If a player quits, set quit to 1
				if (leftInput == StPress){
					// (VGA) print the pause screen
						// a = quit to main menu
						// b = return to game
					// Ask for inputs until they say "A" or "B"
					while ((leftInput != APress) && (leftInput != BPress) ) {
						leftInput = getButtonPress(hspi2, 0);
					}
					// Set the quit status if they decide to quit
					if(leftInput == APress){
						quit = 0;
					}
				}
				if (rightInput == StPress){
					// (VGA) print the pause screen
						// a = quit to main menu
						// b = return to game
					// Ask for inputs until they say "A" or "B"
					while ((rightInput != APress) && (rightInput != BPress) ) {
						rightInput = getButtonPress(hspi2, 1);
					}
					// Set the quit status if they decide to quit
					if(rightInput == APress){
						quit = 0;
					}
				}
			// Update player paddle objects
				updatePaddleLocation(&leftPaddle, leftInput, leftPrevInput, leftPrevPrevInput);
				updatePaddleLocation(&rightPaddle, rightInput, rightPrevInput, rightPrevPrevInput);
				// (VGA) update the paddle on the screen

			// Check for ball and paddle collision
				// if the ball is on the left
				if (ball.topLeftX < BOARD_WIDTH / 2)
					checkBallPaddleCollision(&leftPaddle, &ball, &rallyCount, 0);
				// if the ball is on the right
				else
					checkBallPaddleCollision(&leftPaddle, &ball, &rallyCount, 1);

			// Update the ball's position
				updateBallPosition(&ball);
				// (VGA) Update ball on screen

			// Check if the ball has gone out of bounds
				// if the ball is on the left
				if (ball.topLeftX < BOARD_WIDTH / 2){
					// The ball can still be played if it's on the screen
					if (ball.topLeftX < 0){
						ball_in_play = 0;
						// Update the user scores
						playerTwo_score++;
						// Using the chess invalid sound as the sound effect for a point
						audio_flag = INVALID;
					}
				}
				// if the ball is on the right
				else{
					// The ball can still be played if it's on the screen
						// this calculation might be wrong
					if (ball.topLeftX + 2 > BOARD_WIDTH - 1){
						ball_in_play = 0;
						// Update the user scores
						playerOne_score++;
						// Using the chess invalid sound as the sound effect for a point
						audio_flag = INVALID;
					}
				}
			// (VGA) Display the score on the screen (always want this to be showing at the top of the screen)

			uint32_t x = 10000;
			HAL_Delay(x);
		}
	}

	// Displaying the winning message and sound if there's a winner, otherwise the quitting message
	if (quit == 1){
		// (VGA) displaying the quitting message
			// Prompt either user to press A to return to main 

		leftInput = NoPress;
		rightInput = NoPress;
		while ( (leftInput != APress) && (rightInput != APress)){
			leftInput = getButtonPress_noWait(hspi2, 0);
			rightInput = getButtonPress_noWait(hspi2, 1);
		}
	}
	else{
		// (VGA) Displaying the winning message
			// Giving the winning sound
			audio_flag = WINNER;
			// Prompt the winner to press A
		if (playerOne_score == WINNING_SCORE){
			leftInput = NoPress;
			while(leftInput != APress) {
				leftInput = getButtonPress_noWait(hspi2, 0);
			}
		}
		else{
			rightInput = NoPress;
			while (rightInput != APress) {
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
void updatePaddleLocation(Object * paddle, buttonPress curInput, buttonPress lastInput, buttonPress lastLastInput){

	// Moving Down
	if (curInput == DPress){
		// Holding down for three counts
		if ( (curInput == DPress) && (curInput == lastInput == lastLastInput) ) {
			if (paddle->topLeftY - paddle->height > 2){
				paddle->topLeftY-= 3;
				paddle->y_momentum = -1;
			}
			else
				paddle->topLeftY-= paddle->height;
		}
		// Holding down for 2 counts
		else if ( (curInput == DPress) && (curInput == lastInput) ) {
			if (paddle->topLeftY - paddle->height > 1){
				paddle->topLeftY-= 2;
				paddle->y_momentum = -1;
			}
			else
				paddle->topLeftY-= paddle->height;
		}
		// Holding down for 1 count
		else{
			if (paddle->topLeftY - paddle->height > 0){
				paddle->topLeftY-= 1;
				paddle->y_momentum = -1;
			}
		}
	}
	// Moving Up
	else if (curInput == UPress){
		// Holding up for three counts
		if ( (curInput == UPress) && (curInput == lastInput == lastLastInput) ) {
			if (paddle->topLeftY < BOARD_HEIGHT-3){
				paddle->topLeftY+= 3;
				paddle->y_momentum = 1;
			}
			else
				paddle->topLeftY+= BOARD_HEIGHT-1;
		}
		// Holding up for 2 counts
		else if ( (curInput == UPress) && (curInput == lastInput) ) {
			if (paddle->topLeftY < BOARD_HEIGHT-2){
				paddle->topLeftY+= 2;
				paddle->y_momentum = 1;
			}
			else
				paddle->topLeftY+= BOARD_HEIGHT-1;
		}
		// Holding up for 1 count
		else{
			if (paddle->topLeftY < BOARD_HEIGHT-1){
				paddle->topLeftY+= 1;
				paddle->y_momentum = 1;
			}
		}
	}
	// paddle is not moving
	else{
		paddle->y_momentum = 0;
	}

	return;
}

void checkBallPaddleCollision(Object * paddle, Object * ball, uint8_t * rallyCount, uint8_t rightSide){

	// if there is a collison then set this to 1
	uint8_t collision = 0;

	/*
	 * What's being checked for:
	 * - the ball has reached the paddle
	 * - the ball is not above the paddle
	 * - the ball is not beneath the paddle
	 */

	if(rightSide){
		if ( (paddle->topLeftX == (ball->topLeftX + ball->width) )
			&& ( (ball->topLeftY - paddle->topLeftY) < ball->height)
			&&	( (paddle->topLeftY - ball->topLeftY) < paddle->height)
			 ) {
			collision = 1;
		}
	}
	else{
		if ( (ball->topLeftX  == (paddle->topLeftX + paddle->width) )
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
		ball->x_momentum = -ball->x_momentum;
		// If the paddle was moving up, pushing the ball up faster (with a max of 10)
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

	// ball is moving up so check the top of the playing field before updating
	if (ball->y_momentum > 0){
		// if the ball might move through the top of the screen, just set its position to the top where it would hit and reverse its y direction

	}
	// ball is moving down so check the bottom of the playing field before updating
	else if (ball->y_momentum < 0){
		// if the ball might move through the bottom of the screen, just set its position to the bottom where it would hit and reverse its y direction

	}
	// ball is moving straight
	else{
		ball->topLeftX += ball->x_momentum;
	}


	// Update the ball's position based on it's momentum
				// Check if the ball is colliding with the bottom or top of the field (since we've already checked with the paddles)
	return;
}

/*
 * (UNNECESSARY now that we'll just be reducing the HAL_Delay() at the end of the rally while-loop
 * This function will determine if the ball is about to collide with one of the paddles
 *
 * If so it will advance the ball up to the point where it would satisfy the collision requirement if the game weren't operating
 * in discrete time intervals
 *
 * Similar to the checkBallPaddleCollision function except will need a for loop to iterate through the spaces where the ball could be at
 * and see if any of those points have a collision [an imperfect approximation is fine since for example if the x momentum
 * is 3 and y momentum is 5 and the ball is 2 pixels away from colliding, we can just move the ball 2 pixels over so that it
 * satisfies the collide condition and 2 pixels up since integer division give us (5/3 = 1, 1 * 2 = 2) ]
 */
void anticipateCollision(Object * ball, Object * paddle, uint8_t rightSide){
	return;
}
