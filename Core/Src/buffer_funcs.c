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
void update_square(int position, uint8_t piece, int pieceColorBit, int highlighted, int cursor)
{
	//Find x and y position
	int x = BOARD_UPPER_LEFT_X + 18 * (position % 8);
	int y = BOARD_UPPER_LEFT_Y + 18 * ((int) (63 - position) / 8);

//	Get pointer to sample
//	uint8_t ** pointer;
//	switch (piece)
//	{
//		case 0: //pawn
//			pointer = (uint8_t**)pawn;
//			break;
//	}

	//Find color of square
	uint8_t oddRow = (position / 8) % 2;
	uint8_t squareColor = (oddRow && (position % 2) || !oddRow && !(position % 2)) ? GREEN : GRAY;
	uint8_t pieceColor = pieceColorBit ? W : B;
	uint8_t highlightedColor = PURPLE;
	uint8_t cursorColor = BLUE;

	switch(piece) {
	case PAWN:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (pawn[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(cursor) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
				else if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9 || i == 7 && j == 7 ||i == 10 && j == 10 ||i == 7 && j == 10 ||i == 10 && j == 7) {
						framebuffer[y + i][x + j] = cursorColor;
					}
				}
			}
		}
		break;
	case KING:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (king[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
			}
		}
		break;
	case QUEEN:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (queen[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
			}
		}
		break;
	case ROOK:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (rook[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
			}
		}
		break;
	case BISHOP:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (bishop[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
			}
		}
		break;
	case KNIGHT:
		for (int i = 0; i < 18; i++){
			for (int j = 0; j < 18; j++){
				if (knight[i][j] == 0){
					framebuffer[y + i][x + j] = squareColor;
				}
				else{
					framebuffer[y + i][x + j] = pieceColor;
				}
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
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
				if(highlighted) {
					if(i == 8 && j == 8 || i == 8 && j == 9 || i == 9 && j == 8 || i == 9 && j == 9) {
						framebuffer[y + i][x + j] = highlightedColor;
					}
				}
			}
		}
		break;
	}

}
