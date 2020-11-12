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
#include "uci.h"

#define GRAY 42
#define GREEN 4
#define YELLOW 60
#define BEIGE 62
#define G 62//shorthand beige
#define PURPLE 34
#define BLUE 7

#define BOARD_UPPER_LEFT_X 3
#define BOARD_UPPER_LEFT_Y 3

#define BOARD_UPPER_LEFT_X 3
#define BOARD_UPPER_LEFT_Y 3
#define TILE_WIDTH 18
#define B 0
#define W 63

void update_square(int position, uint8_t piece, int pieceColorBit, int highlighted, int cursor, int perspective);
void update_feedback(char * letter_array, int size, int row);
//void write_char(uint8_t ** letter_array, int startColumn, int startRow);
void update_options(gameState state);
void clear_feedback();

static uint8_t a_char[5][3] = {

    {B, B, B},
    {B, G, B},
    {B, B, B},
    {B, G, B},
    {B, G, B}
};

static uint8_t b_char[5][3] = {

    {B, B, G},
    {B, G, B},
    {B, B, G},
    {B, G, B},
    {B, B, G}
};

static uint8_t c_char[5][3] = {

    {G, B, B},
    {B, G, G},
    {B, G, G},
    {B, G, G},
    {G, B, B}
};

static uint8_t d_char[5][3] = {

    {B, B, G},
    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, B, G}
};

static uint8_t e_char[5][3] = {

    {B, B, B},
    {B, G, G},
    {B, B, B},
    {B, G, G},
    {B, B, B}
};

static uint8_t f_char[5][3] = {

    {B, B, B},
    {B, G, G},
    {B, B, B},
    {B, G, G},
    {B, G, G}
};

static uint8_t g_char[5][3] = {

    {G, B, B},
    {B, G, G},
    {B, G, B},
    {B, G, B},
    {G, B, B}
};

static uint8_t h_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {B, B, B},
    {B, G, B},
    {B, G, B}
};

static uint8_t i_char[5][3] = {

    {B, B, B},
    {G, B, G},
    {G, B, G},
    {G, B, G},
    {B, B, B}
};

static uint8_t j_char[5][3] = {

    {G, G, B},
    {G, G, B},
    {G, G, B},
    {B, G, B},
    {B, B, B}
};

static uint8_t k_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {B, B, G},
    {B, G, B},
    {B, G, B}
};

static uint8_t l_char[5][3] = {

    {B, G, G},
    {B, G, G},
    {B, G, G},
    {B, G, G},
    {B, B, B}
};

static uint8_t m_char[5][3] = {

    {B, G, B},
    {B, B, B},
    {B, G, B},
    {B, G, B},
    {B, G, B}
};

static uint8_t n_char[5][3] = {

    {B, B, B},
    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, G, B}
};

static uint8_t o_char[5][3] = {

    {B, B, B},
    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, B, B}
};

static uint8_t p_char[5][3] = {

    {B, B, B},
    {B, G, B},
    {B, B, B},
    {B, G, G},
    {B, G, G}
};

static uint8_t q_char[5][3] = {

    {B, B, G},
    {B, B, G},
    {B, B, G},
    {B, B, G},
    {B, B, B}
};

static uint8_t r_char[5][3] = {

    {B, B, G},
    {B, G, B},
    {B, B, G},
    {B, G, B},
    {B, G, B}
};

static uint8_t s_char[5][3] = {

    {G, B, B},
    {B, G, G},
    {G, B, G},
    {G, G, B},
    {B, B, G}
};

static uint8_t t_char[5][3] = {

    {B, B, B},
    {G, B, G},
    {G, B, G},
    {G, B, G},
    {G, B, G}
};

static uint8_t u_char2[5][3] = {

    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, B, B}
};

static uint8_t v_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, B, G}
};

static uint8_t w_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {B, G, B},
    {B, B, B},
    {B, G, B}
};

static uint8_t x_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {G, B, G},
    {B, G, B},
    {B, G, B}
};

static uint8_t y_char[5][3] = {

    {B, G, B},
    {B, G, B},
    {G, B, G},
    {G, B, G},
    {G, B, G}
};

static uint8_t z_char[5][3] = {

    {B, B, B},
    {G, G, B},
    {G, B, G},
    {B, G, G},
    {B, B, B}
};

static uint8_t sp_char[5][3] = {

    {G, G, G},
    {G, G, G},
    {G, G, G},
    {G, G, G},
    {G, G, G}
};

static uint8_t qu_char[5][3] = {

    {B, B, B},
    {G, G, B},
    {G, B, B},
    {G, G, G},
    {G, B, G}
};

static uint8_t eq_char[5][3] = {

    {G, G, G},
    {B, B, B},
    {G, G, G},
    {B, B, B},
    {G, G, G}
};


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
