/*
 * vga.c
 *
 *  Created on: Nov 7, 2020
 *      Author: Gokul Srinivasan
 */



#include "stm32f4xx.h"
#include "vga.h"
#include "main.h"

void init_wavetable(void) {
	int x;
	for(x = 0; x<1000; x++){
		wavetable[x] = 32767 * sin(2 * 3.14159 * x / 1000);
	}
}

void initGPIO()
{
	//Configure GPIOC for DMA transfers
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD -> MODER |= 0x5555;
	GPIOD -> OSPEEDR |= 0xFFFF;

	//Hsync
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA -> MODER |= 0x8;
	GPIOA -> OSPEEDR |= 0xC;
	GPIOA -> AFR[0] |= 0x10;

	//Vsync
	GPIOA -> MODER |= 0x8000;
	GPIOA -> OSPEEDR |= 0xC000;
	GPIOA -> AFR[0] |= 0x20000000;
}

//CONFIGURED FOR TIM1 CCR1
void initDMA0()
{
	//Enable clock to DMA
	RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	//Select correct channel (6) at very high priority
	DMA2_Stream1 -> CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1 | DMA_SxCR_PL;
	DMA2_Stream1 -> CR |= DMA_SxCR_DIR_0 | DMA_SxCR_MINC | DMA_SxCR_CIRC;
	DMA2_Stream1 -> CR |= DMA_SxCR_DBM;
	DMA2_Stream1 -> CR &= ~(DMA_SxCR_PSIZE | DMA_SxCR_MSIZE);

	//Configure source and destination
	DMA2_Stream1 -> M0AR = (uint32_t) framebuffer[0];
	DMA2_Stream1 -> M1AR = (uint32_t) framebuffer[1];
	DMA2_Stream1 -> PAR = (uint32_t) &(GPIOD->ODR);

	//Set transfer count
	DMA2_Stream1 -> NDTR = VGA_W_PX + 1;	//201 Elements

	//Enable interrupt
	DMA2_Stream1 -> CR |= DMA_SxCR_TCIE;
	NVIC -> ISER[1] |= 1 << (DMA2_Stream1_IRQn - 32);

	DMA2_Stream1 -> CR |= DMA_SxCR_EN;
}


//This executes at the start of each line
//void DMA2_Stream1_IRQHandler()
//{
//}

void initTIM1()
{
	//Enable clock to timer
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	//Disable interrupt
	TIM1 -> DIER &= ~ TIM_DIER_UIE;

	TIM1 -> PSC = 1;
	TIM1 -> ARR = 7;
	TIM1 -> RCR = 200;

	//Enable DMA requests on CCR1 event
	TIM1 -> CCR1 = 3;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM1 -> CCER |= TIM_CCER_CC1E;
	TIM1 -> DIER |= TIM_DIER_CC1DE;

	//Configure as slave to TIM2, trigger mode
	TIM1 -> SMCR |= TIM_SMCR_TS_0;
	TIM1 -> SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1;

	TIM1 -> CR1 |= TIM_CR1_OPM;
	TIM1 -> BDTR |= TIM_BDTR_MOE;
}

void initTIM2()
{
	//Enable clock to timer
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2 -> PSC = 7;
	TIM2 -> ARR = 263;

	//Configure as master mode to timer 1
	TIM2 -> CCR1 = 21;
	//I was going to use 'active on match' but for some reason it only works correctly in PWM mode 2
	TIM2 -> CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM2 -> CCER |= TIM_CCER_CC1E;
	TIM2 -> CR2 |= TIM_CR2_MMS_2;
	TIM2 -> SMCR |= TIM_SMCR_MSM;

	//Sync pulse time using CCR2 on GPIO A pin 1
	TIM2 -> CCR2 = 231;
	TIM2 -> CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; //PWM Mode 1
	TIM2 -> CCER |= TIM_CCER_CC2E;

	//Enable the timer
	TIM2 -> CR1 |= TIM_CR1_CEN;
}



//SETUP PROCEDURE. GOOD LUCK UNDERSTANDING THIS MESS
void initTIM1prep(int rcr)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1 -> PSC = 1;
	TIM1 -> ARR = 7;
	TIM1 -> RCR = rcr;
	TIM1 -> CCR1 = 3;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM1 -> DIER |= TIM_DIER_CC1DE;
	TIM1 -> CR1 |= TIM_CR1_OPM;
	TIM1 -> BDTR |= TIM_BDTR_MOE;
	TIM1 -> DIER |= TIM_DIER_UIE;
	NVIC -> ISER[0] |= 1 << TIM1_UP_TIM10_IRQn;
	TIM1 -> CR1 |= TIM_CR1_CEN;
}
int numLinesCompleted = 0;
void TIM1_UP_TIM10_IRQHandler()
{
	TIM1 -> SR &= ~TIM_SR_UIF;
	numLinesCompleted += 1;
	if (numLinesCompleted < 608){
		initTIM1prep(200);
	} else {
		initTIM1();
		initTIM2();
		initTIM3();
	}
}

void initTIM3()
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	//Configure psc as 0
	TIM3 -> PSC = 0;
	TIM3 -> ARR = 627;

	//Generate Vsync
	TIM3 -> CCR2 = 624;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	TIM3 -> CCER |= TIM_CCER_CC2E;

	//Configure as slave to TIM2 in trigger mode
	TIM3 -> SMCR |= TIM_SMCR_SMS;
	TIM3 -> SMCR |= TIM_SMCR_TS_0;

	TIM3 -> CCR1 = 500;
	TIM3 -> CCMR1 |= TIM_CCMR1_OC1M_0;
	TIM3 -> CCER |= TIM_CCER_CC1E;
	TIM3 -> DIER |= TIM_DIER_CC1IE;
	NVIC -> ISER[0] |= 1 << TIM3_IRQn;

	TIM3 -> CR1 |= TIM_CR1_CEN;

}
