/*
 * buttons.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Gokul Srinivasan
 */

#include "buttons.h"

// Global variables to hold the values to be checked against

static uint8_t left = ~(0xfc) ;
static uint8_t up = ~(0xf3);
static uint8_t right1 = ~(0x7e);
static uint8_t right2 = ~(0xfe);
static uint8_t down = ~(0xf9);

static uint8_t a = ~(0x3f);
static uint8_t b = ~(0x9f);
static uint8_t select = ~(0xcf);
static uint8_t start = ~(0xe7);

/*
 * getButtonPress
 *
 * Polling function that will wait until the selected controller makes a button press
 *
 */
buttonPress getButtonPress(SPI_HandleTypeDef * hspi2, int controller){
	// Inside the parenthesis is what we see on logic analyzer
	// taking the inverse to more easily provide button precedence
	uint8_t invertedData;

	HAL_StatusTypeDef spiStatus = HAL_OK;
	uint8_t latch [1] = {0x80};
	uint8_t data [1] = {0xff}; //Initializing to when no button is being pressed

	buttonPress buttonPress = NoPress; //1=a, 2=up, 3=down, 4=right, 5=left, 6=start, 7=select, 8=b


	// Commented for testing purposes
	/*
	// Sends a logic high to a multiplexer to determine which controller inputs are being read from
	if (controller == 0){
		HAL_GPIO_WritePin(GPIOE, BUTTON_SELECT, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOE, BUTTON_SELECT, GPIO_PIN_SET);
	}
	*/

	while(data[0] == 0xff) {
		spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
		HAL_Delay(1);
		if(spiStatus != HAL_OK) break;
	}

	invertedData = ~(data[0]);

	// a gets highest precedence and so on
	if ((invertedData & a) == a){
		// LED feedback -- Only for testing
//		HAL_GPIO_WritePin(GPIOE, A_LED, GPIO_PIN_SET);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_WritePin(GPIOE, A_LED, GPIO_PIN_RESET);

		buttonPress = APress;
	}
	else if ((invertedData & up) == up){
		// LED feedback -- Only for testing
//		HAL_GPIO_TogglePin(GPIOD, ORANGE_TOPLED);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_TogglePin(GPIOD, ORANGE_TOPLED);

		buttonPress = UPress;
	}
	else if((invertedData & down) == down){
		// LED feedback -- Only for testing
//		HAL_GPIO_TogglePin(GPIOD, BLUE_BOTTOMLED);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_TogglePin(GPIOD, BLUE_BOTTOMLED);

		buttonPress = DPress;
	}
	else if ((invertedData & left) == left){
		// LED feedback -- Only for testing
//		HAL_GPIO_TogglePin(GPIOD, GREEN_LEFTLED);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_TogglePin(GPIOD, GREEN_LEFTLED);

		buttonPress = LPress;
	}
	else if ((invertedData & start) == start){
		// LED feedback -- Only for testing
//		HAL_GPIO_WritePin(GPIOE, START_LED, GPIO_PIN_SET);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_WritePin(GPIOE, START_LED, GPIO_PIN_RESET);

		buttonPress = StPress;
	}
	else if ((invertedData & select) == select){
		// LED feedback -- Only for testing
//		HAL_GPIO_WritePin(GPIOE, SELECT_LED, GPIO_PIN_SET);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_WritePin(GPIOE, SELECT_LED, GPIO_PIN_RESET);

		buttonPress = SePress;
	}
	else if ((invertedData & b) == b){
		// LED feedback -- Only for testing
//		HAL_GPIO_WritePin(GPIOE, B_LED, GPIO_PIN_SET);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_WritePin(GPIOE, B_LED, GPIO_PIN_RESET);

		buttonPress = BPress;
	}
	else if ((invertedData & right1) == right1 || (invertedData & right2) == right2){
		// LED feedback -- Only for testing
//		HAL_GPIO_TogglePin(GPIOD, RED_RIGHTled);

		while(data[0] != 0xff) {
			spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			if(spiStatus != HAL_OK) break;
		}

//		HAL_GPIO_TogglePin(GPIOD, RED_RIGHTled);

		buttonPress = RPress;
	}

	return buttonPress;

}


/*
 * getButtonPress_noWait
 *
 * Non-polling function that will only ask the selected user twice for a button press
 *
 * (asking twice to give a larger margin of error)
 *
 */
buttonPress getButtonPress_noWait(SPI_HandleTypeDef * hspi2, int controller){
	// Inside the parenthesis is what we see on logic analyzer
	// taking the inverse to more easily provide button precedence
	uint8_t invertedData;

	HAL_StatusTypeDef spiStatus = HAL_OK;
	uint8_t latch [1] = {0x80};
	uint8_t data [1] = {0xff}; //Initializing to when no button is being pressed

	buttonPress buttonPress = NoPress; //1=a, 2=up, 3=down, 4=right, 5=left, 6=start, 7=select, 8=b

	// Variable to tell us how many times to ask the user for an input
	uint8_t timesToAsk = 2;
	uint8_t counter = 0;

	// Commented for testing purposes
	/*
	// Sends a logic high to a multiplexer to determine which controller inputs are being read from
	if (controller == 0){
		HAL_GPIO_WritePin(GPIOE, BUTTON_SELECT, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOE, BUTTON_SELECT, GPIO_PIN_SET);
	}
	*/

	// Asking for a user input however many times has been determined above
	while ((data[0] == 0xff) && (counter < timesToAsk)){
		counter++;
		// Asking the user for an input
		spiStatus = HAL_SPI_TransmitReceive(hspi2, latch, data, 1, HAL_MAX_DELAY);
			// Might need to add a HAL_delay(1) here like above
		invertedData = ~(data[0]);

		if ((invertedData & a) == a){
			return APress;
		}
		else if ((invertedData & up) == up){
			return UPress;
		}
		else if ((invertedData & down) == down){
			return DPress;
		}
		else if ((invertedData & left) == left){
			return LPress;
		}
		else if ((invertedData & start) == start){
			return StPress;
		}
		else if ((invertedData & select) == select){
			return SePress;
		}
		else if ((invertedData & b) == b){
			return BPress;
		}
		else if ((invertedData & right1) == right1 || (invertedData & right2) == right2){
			return RPress;
		}
	}

	return NoPress;


}

/*
 * An additional initialization function to ensure that SPI2 had been initialized to desired specifications
 *
 */
void My_SPI2_INIT(SPI_HandleTypeDef * hspi2){

	GPIO_InitTypeDef GPIO_InitStruct = {0};


	HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(SPI2_CLK_GPIO_Port, SPI2_CLK_Pin|SPI2_MOSI_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(SPI2_MISO_GPIO_Port, SPI2_MISO_Pin, GPIO_PIN_RESET);


	/*Configure GPIO pins : PE10 PE11 PE14 PE15 */
	  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);


	// Us for SPI2
	GPIO_InitStruct.Pin = SPI2_CLK_Pin|SPI2_MOSI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(SPI2_CLK_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI2_MISO_Pin|SPI2_MOSI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(SPI2_MISO_GPIO_Port, &GPIO_InitStruct);
	hspi2->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	HAL_SPI_Init(hspi2);
}
