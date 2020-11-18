/*
 * main_menu.h
 *
 *  Created on: Nov 18, 2020
 *      Author: Gokul Srinivasan
 */

#ifndef SRC_MAIN_MENU_H_
#define SRC_MAIN_MENU_H_

#include "../Inc/main.h"


void state_change(buttonPress button, SPI_HandleTypeDef * hspi2);
void main_menu(SPI_HandleTypeDef * hspi2);

#endif /* SRC_MAIN_MENU_H_ */
