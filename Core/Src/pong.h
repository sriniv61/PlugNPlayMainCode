/*
 * pong.h
 *
 *  Created on: Nov 21, 2020
 *      Author: terrencerandall
 */

#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include "main.h"
#include "buttons.h"
#include "audio.h"

#define BOARD_HEIGHT 144
#define BOARD_WIDTH 194
#define WINNING_SCORE 7

#define MAX_BALL_MOMENTUM 1 // Keeping things simple (get's rid of need for anticipate function)

#define BALL_WIDTH 3
#define BALL_HEIGHT BALL_WIDTH
#define PADDLE_WIDTH 3
#define PADDLE_HEIGHT 10

/* GAME NOTES:
 *
 * - Paddles will be 3 pixels wide and 14 pixels high
 * - The ball will be 3 x 3 pixels
 * - The ball will initially travel towards whichever side scored last
 * - The far bottom left of the board will be location 0,0
 * - The board is only height 144 by width 194, but we'll consider the entire 
 *
 */

// Create a struct to hold the values for each object
typedef struct {
    uint8_t topLeftX;
    uint8_t topLeftY;
    uint8_t width;
    uint8_t height;

    uint8_t x_momentum;  // only used for the ball
    uint8_t y_momentum;  // only used for the ball

} Object;

void pong_game (SPI_HandleTypeDef *hspi2);
void updatePaddleLocation(Object * paddle, buttonPress curInput, buttonPress lastInput, buttonPress lastLastInput);
void checkBallPaddleCollision(Object * paddle, Object * ball, uint8_t * rallyCount, uint8_t rightSide);
void updateBallPosition(Object * ball);





#endif /* SRC_PONG_H_ */
