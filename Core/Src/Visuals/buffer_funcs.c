/*
 * buffer_funcs.c
 *
 *  Created on: Nov 7, 2020
 *      Author: Gokul Srinivasan
 */
#include "buffer_funcs.h"


/*
 * menu_init used for initializing menu upon start up
 */
void menu_init() {
	for(int column = 0; column < 200; column++) {
		for(int row = 0; row < 150; row++) {
			if (column < 3 || column > 196)
				framebuffer[row][column] = B;
			else if (row < 3 || row > 146)
				framebuffer[row][column] = B;
			else
				framebuffer[row][column] = G;
		}
	}
	print_string("MAIN  MENU", 10, 0, 18, B, G);
	print_string("> GAME SELECTION", 16, 2, 2, B, G);
	print_string("GAME SETTINGS", 13, 3, 4, B, G);
	print_string("VOLUME", 6, 4, 8, B, G);
	print_string("CONTROL SET", 11, 5, 6, B, G);
}

/* menu_update
 *
 * used for updating the menu cursor and the options displayed on the menu screen
 *
 */
void menu_update(int cursorPos, menuState state, settingsState sState)  {
	for(int column = 100; column < 197; column++) {
		for(int row = 21; row < 147; row++) {
			framebuffer[row][column] = G;
		}
	}
	switch(state){
		case Welcome:
			for(int i = 0; i < 4; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 2, B, G);
				else print_string(">", 1, i + 2, 2, P, G);
			}
			break;
		case GameSelection:
			print_string("CHESS", 5, 2, 32, B, G);
			print_string("PONG", 4, 3, 32, B, G);
			print_string("SNAKE", 5, 4, 32, B, G);
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26, B, G);
				else print_string(">", 1, i + 2, 26, P, G);
			}
			break;
		case GameSettings:
			switch(sState) {
				case None:
					print_string("CHESS", 5, 2, 32, B, G);
					print_string("PONG", 4, 3, 32, B, G);
					print_string("SNAKE", 5, 4, 32, B, G);
					break;
				case Chess:
					print_string("CHOOSE PIECE SET", 16, 1, 27, B, G);
					print_string("MODERN PIECES", 13, 2, 28, B, G);
					print_string("CLASSIC PIECES", 14, 3, 28, B, G);
					break;
				case Pong:
					print_string("CHOOSE BALL SIZE", 16, 1, 26, B, G);
					print_string("SMALL", 5, 2, 31, B, G);
					print_string("LARGE", 5, 3, 31, B, G);
					break;
				case Snake:
					print_string("CHOOSE GAME SPEED", 17, 1, 25, B, G);
					print_string("SLOW", 4, 2, 31, B, G);
					print_string("NORMAL", 6, 3, 30, B, G);
					print_string("FAST", 4, 4, 31, B, G);
					print_string("VERY FAST", 9, 5, 30, B, G);
					break;
			}
			for(int i = 0; i < 4; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26, B, G);
				else print_string(">", 1, i + 2, 26, P, G);
			}
			break;
		case VolumeControl:
			print_string("OFF", 3, 2, 33, B, G);
			print_string("ON", 2, 3, 34, B, G);
			print_string("TEST", 4, 4, 33, B, G);
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26, B, G);
				else print_string(">", 1, i + 2, 26, P, G);
			}
			break;
		case ControllerSettings:
			print_string("NUM OF CONTROLLERS?", 19, 1, 24, B, G);
			print_string("ONE", 3, 2, 32, B, G);
			print_string("TWO", 3, 3, 32, B, G);
			for(int i = 0; i < 2; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26, B, G);
				else print_string(">", 1, i + 2, 26, P, G);
			}
			break;
	}
}

/*
 * print_string is a general function aimed for use in the main menu
 *
 * Pass a string, the amount of characters in the string (a max of 48), the row the string is to be printed on (0 to 7 inclusive),
 * and the start position (from 0 to 47 inclusive, 48 being the max number of characters in a row)
 */
void print_string(char * str, int size, float row, int startCharPos, uint8_t charColor, uint8_t backColor) {
	int startColumn;
	int startRow;
	for(int i = 0; i < size; i++){
		startColumn = 4 + startCharPos * 4 + i * 4;
		startRow = 10 + 18 * row;
		switch(str[i]) {
		case 'A':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (a_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'B':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (b_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'C':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (c_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'D':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (d_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'E':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (e_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'F':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (f_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'G':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (g_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'H':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (h_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'I':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (i_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'J':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (j_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'K':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (k_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'L':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (l_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'M':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (m_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'N':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (n_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'O':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (o_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'P':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (p_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'Q':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (q_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'R':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (r_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'S':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (s_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'T':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (t_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'U':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (u_char2[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'V':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (v_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'W':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (w_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'X':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (x_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'Y':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (y_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case 'Z':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (z_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '=':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (eq_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '?':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (qu_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '>':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (triangle_cursor[row - startRow][column - startColumn] == P)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case ' ':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (sp_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case ':':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (co_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '0':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (zero_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '1':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (one_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '2':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (two_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '3':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (three_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '4':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (four_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '5':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (five_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '6':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (six_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '7':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (seven_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '8':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (eight_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;
		case '9':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					if (nine_char[row - startRow][column - startColumn] == B)
						framebuffer[row][column] = charColor;
					else
						framebuffer[row][column] = backColor;
				}
			}
			break;

		}
	}
}

/*
 * Update_feedback function is aimed at the chess game (but can potentially be used elsewhere)
 * NOTE: if used elsewhere, the characters will be black and the background will be beige***
 *
 * pass the function a string (with a max of 12 characters, the amount of characters in the string
 * and the desired row (from 0 to 7 inclusive)
 *
 * Notes: Strings must be all capital letters, no numbers, and can use " ", "?", and "="
 */

void update_feedback(char * str, int size, int row) {
	int startColumn;
	int startRow;
	for(int i = 0; i < size; i++){
		startColumn = 148 + i * 4;
		startRow = 10 + 18 * row;
		switch(str[i]) {
		case 'A':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = a_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'B':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = b_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'C':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = c_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'D':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = d_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'E':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = e_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'F':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = f_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'G':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = g_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'H':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = h_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'I':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = i_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'J':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = j_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'K':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = k_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'L':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = l_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'M':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = m_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'N':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = n_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'O':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = o_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'P':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = p_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'Q':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = q_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'R':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = r_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'S':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = s_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'T':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = t_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'U':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = u_char2[row - startRow][column - startColumn];
				}
			}
			break;
		case 'V':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = v_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'W':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = w_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'X':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = x_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'Y':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = y_char[row - startRow][column - startColumn];
				}
			}
			break;
		case 'Z':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = z_char[row - startRow][column - startColumn];
				}
			}
			break;
		case '=':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = eq_char[row - startRow][column - startColumn];
				}
			}
			break;
		case '?':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = qu_char[row - startRow][column - startColumn];
				}
			}
			break;
		case ' ':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = sp_char[row - startRow][column - startColumn];
				}
			}
			break;
		}
	}
}

/*
 * Update_options used almost exclusively for chess game
 *
 * Used for updating the user options on the lower right side of the screen
 *
 * Pass through the game state and the value of the promotion variable
 */
void update_options(gameState state, int promotion) {
	switch(state) {
	case pieceSelection:
		update_feedback("B = TAKEBACK", 12, 5);
		update_feedback("SE = RESIGN", 12, 6);
		update_feedback("ST = DRAW", 10, 7);
		break;
	case destinationSelection:
		update_feedback("B = UNDO", 8, 5);
		update_feedback("SE = RESIGN", 12, 6);
		update_feedback("ST = DRAW", 10, 7);
		break;
	case promotionSelection:
		// writing 6 characters to each so that it clears the previous promotion option
		switch (promotion){
			case QUEEN:
				update_feedback("QUEEN ", 6, 6);
				break;
			case KNIGHT:
				update_feedback("KNIGHT", 6, 6);
				break;
			case BISHOP:
				update_feedback("BISHOP", 6, 6);
				break;
			case ROOK:
				update_feedback("ROOK  ", 6, 6);
				break;
		}
		update_feedback("A = SELECT", 10, 7);
		break;
	default:
		break;
	}
}

/* Clear_feedback is used for clearing the user feedback portion of the screen on the right side where the chess
 * board is no being displayed
 *
 *
 */
void clear_feedback() {
	for (int column = 147; column < 197; column++){
		for (int row = 3; row < 147; row++){
			framebuffer[row][column] = BEIGE;
		}
	}
}

/* Update_square used almost exclusively for chess game
 *
 * Pass through the position you'd like to draw, the piece, the piececolor (B or W), if the location is highlighted (1 or 0)
 * if the location contains the cursor (1 or 0), and the perpective (1 or 0)
 */

void update_square(int position, uint8_t piece, int pieceColorBit, int highlighted, int cursor, int perspective)
{
	//Find x and y position
	if(perspective) {
		position = 63 - position;
	}
	int x = BOARD_UPPER_LEFT_X + 18 * (position % 8);
	int y = BOARD_UPPER_LEFT_Y + 18 * ((int) (63 - position) / 8);

	//Find color of square
	uint8_t oddRow = (position / 8) % 2;
	uint8_t squareColor = (oddRow && (position % 2) || !oddRow && !(position % 2)) ? GREEN : GRAY;
	uint8_t pieceColor = pieceColorBit ? B : W;
	uint8_t highlightedColor = PURPLE;
	uint8_t cursorColor = YELLOW;

	switch(piece) {
	case PAWN:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (pawn_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (pawn_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case KING:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (king_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (king_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case QUEEN:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (queen_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (queen_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case ROOK:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (rook_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (rook_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case BISHOP:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (bishop_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (bishop_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case KNIGHT:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if(piece_set == 0){
					if (knight_m[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
				else{
					if (knight_c[i][j] == 0){
						framebuffer[y + i][x + j] = squareColor;
					}
					else{
						framebuffer[y + i][x + j] = pieceColor;
					}
				}
			}
		}
		break;
	case EMPTY:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (empty[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
			}
		}
		break;
	}
	if(cursor) {
		framebuffer[y + 8][x + 8] = cursorColor;
		framebuffer[y + 8][x + 9] = cursorColor;
		framebuffer[y + 9][x + 8] = cursorColor;
		framebuffer[y + 9][x + 9] = cursorColor;
		framebuffer[y + 7][x + 7] = cursorColor;
		framebuffer[y + 10][x + 10] = cursorColor;
		framebuffer[y + 7][x + 10] = cursorColor;
		framebuffer[y + 10][x + 7] = cursorColor;
	}
	if(highlighted) {
		framebuffer[y + 8][x + 8] = highlightedColor;
		framebuffer[y + 8][x + 9] = highlightedColor;
		framebuffer[y + 9][x + 8] = highlightedColor;
		framebuffer[y + 9][x + 9] = highlightedColor;
	}

}
