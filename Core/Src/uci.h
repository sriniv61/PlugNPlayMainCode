#ifndef UCI_H
#define UCI_H

typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;

void uci_main(SPI_HandleTypeDef * hspi2, UART_HandleTypeDef * huart2);

#endif