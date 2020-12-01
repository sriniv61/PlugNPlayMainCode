#ifndef UCI_H
#define UCI_H


#define RESET -1
typedef enum gameState {pieceSelection, destinationSelection, promotionSelection, checking} gameState;

void uci_main(SPI_HandleTypeDef * hspi2);
//void audio_out();

#endif
