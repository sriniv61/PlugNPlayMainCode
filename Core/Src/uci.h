#ifndef UCI_H
#define UCI_H


typedef enum gameState {waitingForFirst, waitingForSecond, waitingForThird, checking} gameState;

void uci_main(SPI_HandleTypeDef * hspi2);
//void audio_out();

#endif
