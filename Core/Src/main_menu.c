#include <stdio.h>
#include <stdlib.h>
#include "main_menu.h"
#define MAX_WELCOME_OPTIONS 3
#define MAX_GAMES 3
#define MAX_CHESS_SETTINGS 2
#define MAX_VOLUME_SETTINGS 2

int audio_level; //Audio: 0 - low; 1 - med; 2 - high
int cursorPosition = 0;
menuState state = Welcome;
settingsState sState = None;

/*
Cursor is signified by "|" character when run in the terminal. This needs highlighted in a different color
The font for the heading, ex. "Welcome!" preferrably bigger
The whole thing could be preferrably centered
The audio setting is only for demonstrating that our menu has the capability for the PSSC
Same with game choice
*/


void state_change(buttonPress button, SPI_HandleTypeDef * hspi2){
    switch (state){
        case (Welcome):
            switch (button){
                case (UPress):
                    if (cursorPosition > 0)
                        cursorPosition--;
                    break;
                case (DPress):
                    if (cursorPosition < MAX_WELCOME_OPTIONS - 1)
                        cursorPosition++;
                    break;
                case (APress):
                    switch (cursorPosition){
                        case 0:
                            // state change to game selection
                        	state = GameSelection;
                            break;
                        case 1:
                        	state = GameSettings;
                            break;
                        case 2:
                        	state = VolumeControl;
                            break;
                    }
					cursorPosition = 0;
                    break;
				default:
					break;
            }
            break;
        case (GameSelection):
            switch (button){
				case UPress:
                    if (cursorPosition > 0)
                        cursorPosition--;
					break;
				case DPress:
                    if (cursorPosition < MAX_GAMES - 1)
                        cursorPosition++;
					break;
				case APress:
					if(cursorPosition == 0) {
						uci_main(hspi2);
						menu_init();
						state = Welcome;
						cursorPosition = 0;
					}
					break;
				case BPress:
					cursorPosition = 0;
            		state = Welcome;
					break;
				default:
					break;
            }
            break;
		case (GameSettings):
			switch(sState) {
			case None:
				switch (button){
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_GAMES - 1)
							cursorPosition++;
						break;
					case APress:
						if(cursorPosition == 0) {
							sState = Chess;
							cursorPosition = 0;
						}
						break;
					case BPress:
						cursorPosition = 0;
	            		state = Welcome;
						break;
					default:
						break;
				}
				break;
			case Chess:
				switch (button){
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_CHESS_SETTINGS - 1)
							cursorPosition++;
						break;
					case APress:
						piece_set = cursorPosition == 0 ? 0 : 1;
						state = Welcome;
						cursorPosition = 0;
						break;
					case BPress:
						sState = None;
						cursorPosition = 0;
						break;
					default:
						break;
				}
				break;
			}
			break;
        case (VolumeControl):
			switch (button){
				case UPress:
					if (cursorPosition > 0)
						cursorPosition--;
					break;
				case DPress:
					if (cursorPosition < MAX_VOLUME_SETTINGS - 1)
						cursorPosition++;
					break;
				case APress:
					volume = cursorPosition;
            		state = Welcome;
					cursorPosition = 0;
					break;
				case BPress:
            		state = Welcome;
					cursorPosition = 0;
					break;
				default:
					break;
			}
            break;
        default:
            break;
    }
}



void main_menu(SPI_HandleTypeDef * hspi2)
{
	menu_init();
    while(1){
    	buttonPress inp = getButtonPress(hspi2, 0);
        state_change(inp, hspi2);
    	if(inp == UPress || inp == DPress) audio_flag = 7;
    	if(inp == APress) audio_flag = 1;
    	menu_update(cursorPosition, state, sState);
    }

    return;
}
