/*
 * main_menu.h
 *
 *  Created on: Nov 18, 2020
 *      Author: Gokul Srinivasan
 */

#ifndef SRC_MAIN_MENU_H_
#define SRC_MAIN_MENU_H_

#include "../Inc/main.h"

#define MAX_WELCOME_OPTIONS 4
#define MAX_GAMES 3
#define MAX_CHESS_SETTINGS 2
#define MAX_PONG_SETTINGS 3
#define MAX_VOLUME_SETTINGS 3
#define MAX_CONTROLLER_SETTING 2

//typedef enum menuState {Welcome, GameSelection, GameSettings, VolumeControl} menuState;
//typedef enum settingsState {None, Chess} settingsState;

void state_change(buttonPress button, SPI_HandleTypeDef * hspi2);
void main_menu(SPI_HandleTypeDef * hspi2);


// Global variable defining what piece set the user wants to use
volatile int piece_set;//0 = modern 1 = classic

volatile int two_controller_mode;

#endif /* SRC_MAIN_MENU_H_ */
