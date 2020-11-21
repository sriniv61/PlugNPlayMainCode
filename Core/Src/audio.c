/*
 * audio.c
 *
 *  Created on: Nov 20, 2020
 *      Author: terrencerandall
 */


#include "audio.h"

/*
	Audio IRQ handler that deals with all audio processing
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
