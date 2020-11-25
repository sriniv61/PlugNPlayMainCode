/*
 * pong_buffer_funcs.h
 *
 *  Created on: Nov 25, 2020
 *      Author: terrencerandall
 */

#ifndef SRC_VISUALS_PONG_BUFFER_FUNCS_H_
#define SRC_VISUALS_PONG_BUFFER_FUNCS_H_

#include "buffer_funcs.h"
#include "main.h"
#include "../pong.h"


// Functions called from the pong game
void pongStartupScreen();
void displayPauseScreen();
void displayGame(uint8_t player1Score, uint8_t player2Score, Object* Ball, Object * leftPaddle, Object * rightPaddle);

// utility functions within pong_buffer_funcs.c
void clearScreen();

#endif /* SRC_VISUALS_PONG_BUFFER_FUNCS_H_ */
