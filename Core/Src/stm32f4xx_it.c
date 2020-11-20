/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define freq_place 1
#define freq_error 2
#define freq_check 3
#define freq_capture 2
#define freq_win 7
#define freq_cursor 1
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_tim1_ch1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
/* USER CODE BEGIN EV */
int framebufferLoop = 0;
int drawnLines = 0;
int nextFramebufferLine;
int nextBuffer = 1;

#define FREQ_N  31
const static float FREQ_TABLE_HARRY_POTTER[FREQ_N] 	    = {123.47,	164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 146.83, 174.61, 123.47, 10.00, 123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 293.66, 277.18, 261.63, 207.65, 261.63, 246.94, 233.08, 116.54, 196.00, 164.81};
const static int TICK_TABLE_HARRY_POTTER[FREQ_N] 		= {5000, 7500, 2500, 5000, 10000, 5000, 15000, 15000, 7500, 2500, 5000, 10000, 5000, 25000, 2500, 5000, 7500, 2500, 5000, 10000, 5000, 10000, 5000, 10000, 5000, 7500, 2500, 5000, 10000, 5000, 25000};

const static float freq_array_place[freq_place] 	    = {523};
const static int tick_counts_place[freq_place] 		= {100};
const static float freq_array_error[freq_error] 	    = {783.99, 554.37};
const static int tick_counts_error[freq_error] 		= {50, 200};
const static float freq_array_check[freq_check] 	    = {146.83,138.59,130.81};
const static int tick_counts_check[freq_check] 		= {200, 200, 300};
const static float freq_array_capture[freq_capture] 	    = {146.83,185.00};
const static int tick_counts_capture[freq_capture] 		= {100, 200};
const static float freq_array_win[freq_win] 	    = {261.63, 329.63, 392.00, 1, 392.00, 329.63, 392.00};
const static int tick_counts_win[freq_win] 		= {250, 250, 250, 25, 375, 125, 500};
const static float freq_array_cursor[freq_cursor] 	    = {783.99};
const static int tick_counts_cursor[freq_cursor] 		= {30};

int offset = 0;
int tick_counter = 0;
int freq_idx = 0;
int step;

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
    TIM3 -> SR &= ~(TIM_SR_CC1IF);
    drawNewFrame = 1;

  /* USER CODE END TIM3_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	// If the user has turned the volume off, acknowledge the interrupt and return
	if(volume == 0){
		TIM6->SR &= ~TIM_SR_UIF;
		return;
	}
	switch(audio_flag){
		// Silent, only acknowledging the interrupt
		case 0:
			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// Sound for placing a piece
		case 1:
			step = freq_array_place[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_place[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_place) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// Sound for an error (invalid destination, etc.)
		case 2:
			step = freq_array_error[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_error[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_error) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// Sound when a player puts the other in check
		case 3:
			step = freq_array_check[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_check[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_check) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// Sound when a player captures one of the other player's pieces
		case 4:
			step = freq_array_capture[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_capture[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_capture) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// Sound when one of the players wins
		case 5:
			step = freq_array_win[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_win[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_win) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		// harry potter audio test
			case 6:
				step = FREQ_TABLE_HARRY_POTTER[freq_idx] * 1000 / 100000 * (1 << 16);
				tick_counter++;
				if(tick_counter >= TICK_TABLE_HARRY_POTTER[freq_idx] * 10) {
					freq_idx++;
					tick_counter = 0;
					if(freq_idx >= FREQ_N) {
						freq_idx = 0;
						audio_flag = 0;
					}
				}
				offset += step;
				if((offset>>16) >= 1000) {
				  offset -= 1000<<16;
				}
				HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
				while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

				TIM6->SR &= ~TIM_SR_UIF;
				break;
		// The sound when the cursor is moved on the main menu
		case 7:
			step = freq_array_cursor[freq_idx] * 1000 / 100000 * (1 << 16);
			tick_counter++;
			if(tick_counter >= tick_counts_cursor[freq_idx] * 100) {
				freq_idx++;
				tick_counter = 0;
				if(freq_idx >= freq_cursor) {
					freq_idx = 0;
					audio_flag = 0;
				}
			}
			offset += step;
			if((offset>>16) >= 1000) {
			  offset -= 1000<<16;
			}
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, wavetable[offset>>16] / 16 + 2048);
			while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);

			TIM6->SR &= ~TIM_SR_UIF;
			break;
		}

  /* USER CODE END TIM6_DAC_IRQn 0 */
//  HAL_DAC_IRQHandler(&hdac);
//  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

	//Clear the interrupt
	DMA2 -> LIFCR |= 0b111101000000;
	//Flip next buffer
	nextBuffer ^= 1;

	drawnLines += 1;	//How many VGA timing lines are sent
	framebufferLoop += 1;	//How many iterations through each framebuffer line
	if (framebufferLoop == 4)
	{
		framebufferLoop = 0;
		nextFramebufferLine += 1;	//After 4 loops, go to next line
	}
	if (nextFramebufferLine > 149)	//Only use up to 150th row (blank)
	{
		nextFramebufferLine = 150;
	}

	if (drawnLines == 628)
	{
		nextFramebufferLine = 0;
		drawnLines = 0;
		framebufferLoop = 0;
	}

	if (nextBuffer == 0)
	{
		DMA2_Stream1 -> M0AR = (uint32_t) framebuffer[nextFramebufferLine];
	}
	else
	{
		DMA2_Stream1 -> M1AR = (uint32_t) framebuffer[nextFramebufferLine];
	}
  /* USER CODE END DMA2_Stream1_IRQn 0 */
//  HAL_DMA_IRQHandler(&hdma_tim1_ch1);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */

  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
