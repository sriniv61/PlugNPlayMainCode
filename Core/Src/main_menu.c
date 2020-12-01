
#include "main_menu.h"


int audio_level; //Audio: 0 - low; 1 - med; 2 - high
int cursorPosition = 0;
menuState state = Welcome;
settingsState sState = None;

void state_change(buttonPress button, SPI_HandleTypeDef * hspi2){
	// Main switch statement for handling the main menu state change logic
    switch (state){
        case (Welcome):
            switch (button){
            	// Keeping the cursor in bounds
                case (UPress):
                    if (cursorPosition > 0)
                        cursorPosition--;
                    break;
                case (DPress):
                    if (cursorPosition < MAX_WELCOME_OPTIONS - 1)
                        cursorPosition++;
                    break;
                case (APress):
                	// The options from the main welcome screen
                    switch (cursorPosition){
                        case 0:
                        	state = GameSelection;
                            break;
                        case 1:
                        	state = GameSettings;
                            break;
                        case 2:
                        	state = VolumeControl;
                            break;
                        case 3:
                        	state = ControllerSettings;
                        	break;
                    }
					cursorPosition = 0;
                    break;
				default:
					audio_flag = 0;
					break;
            }
            break;
        case (GameSelection):
            switch (button){
            	// Keeping the cursor in bounds
				case UPress:
                    if (cursorPosition > 0)
                        cursorPosition--;
					break;
				case DPress:
                    if (cursorPosition < MAX_GAMES - 1)
                        cursorPosition++;
					break;
				case APress:
					// The options from the main Game Selection screen
					switch(cursorPosition) {
					case 0:
						uci_main(hspi2);
						cursorPosition = 0;
						menu_init();
						state = Welcome;
						break;
					case 1:
						pong_game(hspi2);
						cursorPosition = 0;
						menu_init();
						state = Welcome;
						break;
					case 2:
						snake_main(hspi2);
						cursorPosition = 0;
						menu_init();
						state = Welcome;
						break;
					default:
						// Only want to do the things above so that the main menu stays where it is
						break;
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
					// Keeping the cursor in bounds
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_GAMES - 1)
							cursorPosition++;
						break;
					case APress:
						// The options from the main Game Selection screen
						switch (cursorPosition){
							case 0:
								sState = Chess;
								cursorPosition = 0;
								break;
							case 1:
								sState = Pong;
								cursorPosition = 0;
								break;
							case 2:
								sState = Snake;
								cursorPosition = 0;
								break;
							default:
								break;
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
					// Keeping the cursor in bounds
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_CHESS_SETTINGS - 1)
							cursorPosition++;
						break;
						// Only two options for the chess game
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
			case Pong:
				switch (button){
					// Keeping the cursor in bounds
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_PONG_SETTINGS - 1)
							cursorPosition++;
						break;
						// Only two options for the chess game
					case APress:
						switch (cursorPosition){
							case 0:
								ball_size = 3;
								break;
							case 1:
								ball_size = 5;
								break;
						}
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
			case Snake:
				switch (button){
					// Keeping the cursor in bounds
					case (UPress):
						if (cursorPosition > 0)
							cursorPosition--;
						break;
					case (DPress):
						if (cursorPosition < MAX_SNAKE_SETTINGS - 1)
							cursorPosition++;
						break;
						// Only two options for the chess game
					case APress:
						switch (cursorPosition){
							case 0:
								snake_framesPerMove = 20;
								break;
							case 1:
								snake_framesPerMove = 15;
								break;
							case 2:
								snake_framesPerMove = 10;
								break;
							case 3:
								snake_framesPerMove = 3;
								break;
						}
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
					switch (cursorPosition){
						case 0:
							volume = 0;
							break;
						case 1:
							volume = 1;
							break;
						// Only for testing purposes, will play harry potter song
						case 2:
							audio_flag = HARRY_POTTER;
							break;
						default:
							break;
					}
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
		case ControllerSettings:
			switch(button){
			// Keeping the cursor in bounds
				case (UPress):
					if (cursorPosition > 0)
						cursorPosition--;
					break;
				case (DPress):
					if (cursorPosition < MAX_CONTROLLER_SETTING - 1)
						cursorPosition++;
					break;
					// Only two options for the chess game
				case APress:
					switch (cursorPosition){
						case 0:
							two_controller_mode = 0;
							break;
						case 1:
							two_controller_mode = 1;
							break;
						default:
							break;
					}
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

        // Give feedback sound
    	if(inp == UPress || inp == DPress) audio_flag = MENU_CURSOR;
    	if(inp == APress){
    		// If not testing audio, then set the click sound
    		if (audio_flag != HARRY_POTTER)
    			audio_flag = MOVE;
    	}

    	menu_update(cursorPosition, state, sState);
    }

    return;
}
