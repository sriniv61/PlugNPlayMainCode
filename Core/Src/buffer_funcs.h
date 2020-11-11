/*
 * buffer_funcs.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Gokul Srinivasan
 */

#ifndef SRC_BUFFER_FUNCS_H_
#define SRC_BUFFER_FUNCS_H_

#include "../Inc/main.h"
#include "vga.h"
#include "board.h"

#define GRAY 42
#define GREEN 24
#define YELLOW 60
#define PURPLE 34
#define BLUE 7

#define BOARD_UPPER_LEFT_X 3
#define BOARD_UPPER_LEFT_Y 3

#define BOARD_UPPER_LEFT_X 3
#define BOARD_UPPER_LEFT_Y 3
#define TILE_WIDTH 18
#define B 0
#define W 63

void update_square(int position, uint8_t piece, int pieceColorBit, int highlighted, int cursor);


static uint8_t empty[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
};

static uint8_t pawn[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}
};

static uint8_t king[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, B, B, W, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, W, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, W, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, W, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, W, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, B, B, B, B, W, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}
};

static uint8_t queen[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, W, B, B, W, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, W, B, B, B, B, W, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, B, B, B, W, B, B, B, B, B},
	{B, B, B, B, B, B, W, B, B, B, B, W, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, W, B, B, W, B, W, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, W, W, B, B, B, W, W, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
};

static uint8_t bishop[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
};
static uint8_t rook[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, W, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, W, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
};

static uint8_t knight[18][18] =
{
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, W, B, B, B, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, W, B, B, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, W, B, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, W, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, W, B, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, W, B, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, W, B, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, W, B, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, W, W, B, B, B},
	{B, B, B, B, W, B, B, B, B, B, B, B, B, B, W, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
	{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
};

#endif /* SRC_BUFFER_FUNCS_H_ */
