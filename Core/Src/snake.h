/*
 * snake.h
 *
 *  Created on: Dec 1, 2020
 *      Author: Eric Bankert
 */

#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#include "stm32f4xx.h"
#include "Visuals/vga.h"
#include <stdlib.h>
#include "buttons.h"

#define SNAKE_BACKGROUND_COLOR_A 0b00010101
#define SNAKE_BACKGROUND_COLOR_B 0b00101010
#define SNAKE_COLOR 0b00001100
#define SNAKE_FOOD_COLOR 0b00110000


/*
 * type: {0:blank,  1:snake,  2:food}
 * nxt/lst: {1:up, 2:right, 3:down, 4:left}
 */
typedef struct
{
	int type;
	int nxt;
	int lst;
} snake_square;

typedef struct
{
	int a, b, direction;
} snake_controllerInput;

snake_controllerInput snake_input;

void drawGrid();
void drawSquare(int, int);
void snake_main(SPI_HandleTypeDef *hspi2);
int snake_generateFood();
int snake_calculateDestination(int, int);
void snake_parseInput(buttonPress);
int snake_oppositeDirection(int);


//This function exists only for testing. Can be replaced with any function that
//retrives the HSPI inputs
int snake_parseButtons();


// Snake option for user
int snake_framesPerMove;


#endif /* SRC_SNAKE_H_ */
