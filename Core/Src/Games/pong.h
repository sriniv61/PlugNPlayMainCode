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
#include "../External/buttons.h"
#include "../External/audio.h"


// NOTE: This needs to be defined before including pong_buffer_funcs.h so that it can use this structure
	// Create a struct to hold the values for each object
typedef struct {
    uint8_t topLeftX;
    uint8_t topLeftY;
    uint8_t width;
    uint8_t height;

    int x_momentum;  // only used for the ball
    int y_momentum;  // only used for the ball

} Object;

#include "../Visuals/pong_buffer_funcs.h"

#define BOARD_HEIGHT 144
#define BOARD_WIDTH 194
#define WINNING_SCORE 7

#define MAX_BALL_MOMENTUM 1 // Keeping things simple (get's rid of need for anticipate function)
#define GAME_SPEED_INCREMENT 10

#define BALL_WIDTH 3		// Standard size, but letting this be set by the user
#define BALL_HEIGHT BALL_WIDTH
#define PADDLE_WIDTH 3
#define PADDLE_HEIGHT 20


void pong_game (SPI_HandleTypeDef *hspi2);
void updatePaddleLocation(Object * paddle, buttonPress curInput);
void checkBallPaddleCollision(Object * paddle, Object * ball, uint8_t * rallyCount, uint8_t rightSide);
void updateBallPosition(Object * ball);


volatile uint8_t ball_size;
volatile uint8_t game_speed;


#endif /* SRC_PONG_H_ */
