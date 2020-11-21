/*
 * pong.h
 *
 *  Created on: Nov 21, 2020
 *      Author: terrencerandall
 */

#ifndef SRC_PONG_H_
#define SRC_PONG_H_

/* GAME NOTES:
 *
 * - Paddles will be 3 pixels wide and 14 pixels high
 * - The ball will be 3 x 3 pixels
 * - The ball will initially travel towards whichever side scored last
 *
 */

void pong_game (SPI_HandleTypeDef *hspi2);

#endif /* SRC_PONG_H_ */
