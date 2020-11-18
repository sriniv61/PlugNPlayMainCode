/*
 * buffer_funcs.c
 *
 *  Created on: Nov 7, 2020
 *      Author: Gokul Srinivasan
 */
#include "buffer_funcs.h"

//Color
//470powered, 1kground, = .42V
//470gnd, 1kpowered, = .2V

//position: tile to update
//piece: type of piece
//pieceColor: 0=white,1=black
//void write_char(uint8_t ** letter_array, int startColumn, int startRow) {
//}

void menu_init() {
	for(int column = 3; column < 197; column++) {
		for(int row = 3; row < 147; row++) {
			framebuffer[row][column] = G;
		}
	}
	print_string("MAIN  MENU", 10, 0, 18);
	print_string("> GAME SELECTION", 16, 2, 2);
	print_string("GAME SETTINGS", 13, 3, 4);
	print_string("VOLUME", 6, 4, 8);
}

void menu_update(int cursorPos, menuState state, settingsState sState)  {
	for(int column = 100; column < 197; column++) {
		for(int row = 21; row < 147; row++) {
			framebuffer[row][column] = G;
		}
	}
	switch(state){
		case Welcome:
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 2);
				else print_string(">", 1, i + 2, 2);
			}
			break;
		case GameSelection:
			print_string("CHESS", 5, 2, 32);
			print_string("GAME TWO", 8, 3, 31);
			print_string("GAME THREE", 10, 4, 30);
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26);
				else print_string(">", 1, i + 2, 26);
			}
			break;
		case GameSettings:
			switch(sState) {
				case None:
					print_string("CHESS", 5, 2, 32);
					print_string("GAME TWO", 8, 3, 31);
					print_string("GAME THREE", 10, 4, 30);
					break;
				case Chess:
					print_string("MODERN", 6, 2, 32);
					print_string("CLASSIC", 7, 3, 32);
					break;
			}
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26);
				else print_string(">", 1, i + 2, 26);
			}
			break;
		case VolumeControl:
			print_string("OFF", 3, 2, 33);
			print_string("ON", 2, 3, 34);
			for(int i = 0; i < 3; i++){
				if(i != cursorPos) print_string(" ", 1, i + 2, 26);
				else print_string(">", 1, i + 2, 26);
			}
			break;
	}
}

void print_string(char * str, int size, int row, int startCharPos) {
	int startColumn;
	int startRow;
	for(int i = 0; i < size; i++){
		startColumn = 4 + startCharPos * 4 + i * 4;
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
		case '>':
			for(int column = startColumn; column < startColumn + 3; column++) {
				for(int row = startRow; row < startRow + 5; row++) {
					framebuffer[row][column] = triangle_cursor[row - startRow][column - startColumn];
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

void update_options(gameState state) {
	switch(state) {
	case waitingForFirst:
		update_feedback("B = TAKEBACK", 12, 5);
		update_feedback("SE = RESIGN", 12, 6);
		update_feedback("ST = DRAW", 10, 7);
		break;
	case waitingForSecond:
		update_feedback("B = UNDO", 8, 5);
		update_feedback("SE = RESIGN", 12, 6);
		update_feedback("ST = DRAW", 10, 7);
		break;
	case waitingForThird:
		update_feedback("B = UNDO", 8, 5);
		update_feedback("SE = QUEEN", 11, 6);
		update_feedback("ST = KNIGHT", 12, 7);
		break;
	}
}

void clear_feedback() {
	for (int column = 147; column < 197; column++){
		for (int row = 3; row < 147; row++){
			framebuffer[row][column] = BEIGE;
		}
	}
}

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
