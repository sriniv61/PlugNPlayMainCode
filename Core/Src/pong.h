/*
 * pong.h
 *
 *  Created on: Nov 21, 2020
 *      Author: terrencerandall
 *
 *
 *      GAME NOTES:
 *
 * - Paddles will be 3 pixels wide and 14 pixels high
 * - The ball will be 3 x 3 pixels
 * - The ball will initially travel towards whichever side scored last
 * - The far bottom left of the board will be location 0,0
 * - The board is only height 144 by width 194, but we'll consider the entire
 *
 */

#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include "main.h"
#include "buttons.h"
#include "audio.h"


// NOTE: This needs to be defined before including pong_buffer_funcs.h so that it can use this structure
	// Create a struct to hold the values for each object
typedef struct {
    uint8_t topLeftX;
    uint8_t topLeftY;
    uint8_t width;
    uint8_t height;

    uint8_t x_momentum;  // only used for the ball
    uint8_t y_momentum;  // only used for the ball

} Object;

#include "Visuals/pong_buffer_funcs.h"

#define BOARD_HEIGHT 144
#define BOARD_WIDTH 194
#define WINNING_SCORE 7

#define MAX_BALL_MOMENTUM 1 // Keeping things simple (get's rid of need for anticipate function)
#define MAX_GAME_SPEED_INCREASE 200
#define GAME_SPEED_INCREMENT 10

#define BALL_WIDTH 3
#define BALL_HEIGHT BALL_WIDTH
#define PADDLE_WIDTH 3
#define PADDLE_HEIGHT 10


void pong_game (SPI_HandleTypeDef *hspi2);
void updatePaddleLocation(Object * paddle, buttonPress curInput, buttonPress lastInput, buttonPress lastLastInput);
void checkBallPaddleCollision(Object * paddle, Object * ball, uint8_t * rallyCount, uint8_t rightSide);
void updateBallPosition(Object * ball);


volatile uint8_t startingSpeed;


#endif /* SRC_PONG_H_ */
