/*
 * vga.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Gokul Srinivasan
 */

#ifndef SRC_VGA_H_
#define SRC_VGA_H_

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "main.h"

#define VGA_H_PX 150
#define VGA_W_PX 200

#define RED0 GPIO_PIN_0
#define RED1 GPIO_PIN_1
#define GREEN0 GPIO_PIN_2
#define GREEN1 GPIO_PIN_3
#define BLUE0 GPIO_PIN_6
#define BLUE1 GPIO_PIN_7



void initGPIO();	//All VGA GPIO Configuration
void initDMA0();	//DMA that handles pixel transfers
void initTIM1();
void initTIM2();
void initTIM1prep();
void initTIM3();
void init_wavetable();

uint8_t framebuffer[VGA_H_PX + 1][VGA_W_PX + 1];

int framebufferLoop;
int drawnLines;
int nextFramebufferLine;
int nextBuffer;


#endif /* SRC_VGA_H_ */
