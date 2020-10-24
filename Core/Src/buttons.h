/*
 * buttons.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Gokul Srinivasan
 */

#include "main.h"

#ifndef SRC_BUTTONS_H_
#define SRC_BUTTONS_H_

#define BLUE_BOTTOMLED GPIO_PIN_15
#define GREEN_LEFTLED LD4_Pin
#define ORANGE_TOPLED LD3_Pin
#define RED_RIGHTled LD5_Pin

#define A_LED GPIO_PIN_15
#define B_LED GPIO_PIN_14
#define START_LED GPIO_PIN_11
#define SELECT_LED GPIO_PIN_10

#define BUTTON_SELECT GPIO_PIN_7

typedef enum buttonPress {APress, BPress, StPress, SePress, LPress, RPress, UPress, DPress, NoPress} buttonPress;

buttonPress getButtonPress(SPI_HandleTypeDef * hspi2, int controller);
void My_SPI2_INIT(SPI_HandleTypeDef * hspi2);



#endif /* SRC_BUTTONS_H_ */
