/*
 * snake.c
 *
 *  Created on: Dec 1, 2020
 *      Author: Eric Bankert
 */

#include "snake.h"


//THESE OPTIONS ARE CONFIGURABLE
int snake_width = 23;
int snake_height = 17;
int snake_squareSize = 8;	//Does not include grid

int snake_gridStartX = 3;
int snake_gridStartY = 14;



//THIS IS NOT
int snake_totalSize;


void drawGrid()
{
	//First clear the screen
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			framebuffer[j][i] = 0b00000000;
		}
	}

	int totalWidth = snake_width * snake_squareSize;
	int totalHeight = snake_height * snake_squareSize;
	//Fill the background color
	for (int i = 0; i < totalHeight; i++)
	{
		for (int j = 0; j < totalWidth; j++)
		{
			int col;
			if ((i % (2 * snake_squareSize)) - snake_squareSize < 0)
			{
				if ((j % (2 * snake_squareSize)) - snake_squareSize < 0)
					col = SNAKE_BACKGROUND_COLOR_B;
				else
					col = SNAKE_BACKGROUND_COLOR_A;
			}
			else
			{

				if ((j % (2 * snake_squareSize)) - snake_squareSize < 0)
					col = SNAKE_BACKGROUND_COLOR_A;
				else
					col = SNAKE_BACKGROUND_COLOR_B;
			}

			//if ((snake_gridStartY + i) < 150 && (snake_gridStartX + j) < 200)
			framebuffer[snake_gridStartY + i][snake_gridStartX + j] = col;
		}
	}
}

void drawSquare(int location, int type)
{
	int offsetX = (location % snake_width) * snake_squareSize;
	int offsetY = ((int) (location / snake_width)) * snake_squareSize;

	if (type == 0)
	{
		int col;
		if ((offsetY % (2 * snake_squareSize)) - snake_squareSize < 0)
		{
			if ((offsetX % (2 * snake_squareSize)) - snake_squareSize < 0)
				col = SNAKE_BACKGROUND_COLOR_B;
			else
				col = SNAKE_BACKGROUND_COLOR_A;
		}
		else
		{

			if ((offsetX % (2 * snake_squareSize)) - snake_squareSize < 0)
				col = SNAKE_BACKGROUND_COLOR_A;
			else
				col = SNAKE_BACKGROUND_COLOR_B;
		}

		for (int i = 0; i < snake_squareSize; i++)
		{
			for (int j = 0; j < snake_squareSize; j++)
			{
				framebuffer[snake_gridStartY + offsetY + i][snake_gridStartX + offsetX + j] = col;
			}
		}
	}
	else if (type == 1)
	{
		//Draw Square
		for (int i = 0; i < (snake_squareSize - 2); i++)
		{
			for (int j = 0; j < (snake_squareSize - 2); j++)
			{
				framebuffer[snake_gridStartY + offsetY + 1 + i][snake_gridStartX + offsetX + 1 + j] = SNAKE_COLOR;
			}
		}
	}
	else if (type == 2)
	{
		for (int i = 0; i < (snake_squareSize - 2); i++)
		{
			for (int j = 0; j < (snake_squareSize - 2); j++)
			{
				framebuffer[snake_gridStartY + offsetY + 1 + i][snake_gridStartX + offsetX + 1 + j] = SNAKE_FOOD_COLOR;
			}
		}
	}
}


void snake_main(SPI_HandleTypeDef *hspi2)
{
	//Calculate game size
	snake_totalSize = snake_width * snake_height;

	//Initialize game array
	snake_square* gameArray = malloc(snake_totalSize * sizeof(snake_square));
	for (int i = 0; i < snake_totalSize; i++)
	{
		gameArray[i].type = 0;
	}


	drawGrid();

	//Game parameters
	int snakeLength;
	int locationHead;
	int locationTail;
	int locationFood;
	int gameRunning = 1;
	int snakeWait = 0;
	int lastDirection = 1;
	int currentDirection = 0;
	snake_input.direction = 0;

	//Set the initial squares
	locationHead = (int) ((snake_totalSize / 2) - (((snake_totalSize % 2) ^ 1) * (1.5 * snake_width)));
	locationTail = locationHead + snake_width;

	gameArray[locationHead].type = 1;
	gameArray[locationHead].lst = 3;
	gameArray[locationTail].type = 1;
	gameArray[locationTail].nxt = 1;
	drawSquare(locationHead, 1);
	drawSquare(locationTail, 1);


	locationFood = snake_generateFood(gameArray);
	gameArray[locationFood].type = 2;
	drawSquare(locationFood, 2);

	/*
	volatile int z;
	for (int i = 0; i < 4800000; i++)
		z = i;
		*/
	//Start the game loop
	while (gameRunning == 1)
	{

		//parse the frame
		if (drawNewFrame)
		{
			drawNewFrame = 0;
			//parse the input. "snake_parseButtons()" should be replaced with hspi data
			snake_parseInput(getButtonPress_noWait(hspi2, 0));


			//Increment the wait counter
			snakeWait += 1;
			if (snakeWait >= snake_framesPerMove)
			{
				//Reset the wait counter
				snakeWait = 0;

				//Check what direction to move
				if (snake_input.direction == 0)
					currentDirection = lastDirection;
				else
					currentDirection = snake_input.direction;

				if (currentDirection == snake_oppositeDirection(lastDirection))
					currentDirection = lastDirection;

				//Check if the move is valid
				int destination = snake_calculateDestination(locationHead, currentDirection);

				if (destination == -1 || gameArray[destination].type == 1)
				{
					gameRunning = -1;
				}
				else
				{
					//See if food was eaten
					if (gameArray[destination].type == 2)
					{
						snakeLength += 1;
						gameArray[locationHead].nxt = currentDirection;
						gameArray[locationHead].type = 1;
						locationHead = destination;
						gameArray[locationHead].lst = snake_oppositeDirection(currentDirection);
						drawSquare(locationHead, 1);

						locationFood = snake_generateFood(gameArray);
						gameArray[locationFood].type = 2;
						drawSquare(locationFood, 2);
					}
					else
					{
						gameArray[locationHead].nxt = currentDirection;
						locationHead = destination;
						gameArray[locationHead].type = 1;
						gameArray[locationHead].lst = snake_oppositeDirection(currentDirection);
						drawSquare(locationHead, 1);


						gameArray[locationTail].type = 0;
						drawSquare(locationTail, 0);
						locationTail = snake_calculateDestination(locationTail, gameArray[locationTail].nxt);
					}
				}



				//Update the last durection
				lastDirection = currentDirection;
			}

			if (drawNewFrame != 0)
				framebuffer[0][0] = 0b00110000;
		}
	}

	free(gameArray);
	drawNewFrame = 0;
}


//This function generates a food location. Is not optimized if a moderate to high portion of board is filled
int snake_generateFood(snake_square* gameArray)
{
	int location;
	do
	{
		location = rand() % snake_totalSize;
	}
	while (gameArray[location].type == 1);

	return location;
}

int snake_calculateDestination(int start, int direction)
{
	//Generate preliminary result
	int prelim;
	switch (direction)
	{
		case 1: prelim = start - snake_width;	break;
		case 2: prelim = start + 1;				break;
		case 3: prelim = start + snake_width;	break;
		case 4: prelim = start - 1;				break;
		default: return -1;
	}

	//Now check if we are on any edge cases
	int edgeCase = 0;
	switch (direction)
	{
		case 1: edgeCase = start < snake_width ? 1 : 0;									break;
		case 2: edgeCase = (start % snake_width) == (snake_width - 1) ? 1 : 0;			break;
		case 3: edgeCase = start >= (snake_width * (snake_height - 1)) ? 1 : 0;			break;
		case 4: edgeCase = (start % snake_width) == 0 ? 1 : 0;							break;
	}

	if (edgeCase != 0)
	{
		return -1;
	}
	else
	{
		return prelim;
	}
}

int snake_oppositeDirection(int direction)
{
	switch (direction)
	{
		case 1: return 3;
		case 2: return 4;
		case 3: return 1;
		case 4: return 2;
		default: return 0;
	}
}

void snake_parseInput(buttonPress input_button)
{
	switch (input_button){
		case UPress:
			snake_input.direction = 1;
			break;
		case RPress:
			snake_input.direction = 2;
			break;
		case DPress:
			snake_input.direction = 3;
			break;
		case LPress:
			snake_input.direction = 4;
			break;
		default:
			break;
	}

	if (input_button == APress)
		snake_input.a = 1;
	else
		snake_input.a = 0;

	if (input_button == BPress)
		snake_input.b = 1;
	else
		snake_input.b = 0;
}




//THIS IS A TEMPORARY FUNCTION FOR READING FROM GPIO
int snake_parseButtons()
{
	return (GPIOB -> IDR) & 0xFF;
}

