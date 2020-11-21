/*
 * audio.h
 *
 *  Created on: Nov 20, 2020
 *      Author: terrencerandall
 */

#ifndef SRC_AUDIO_H_
#define SRC_AUDIO_H_

#include "main.h"
#include "stm32f4xx_it.h"

#define freq_place 1
#define freq_error 2
#define freq_check 3
#define freq_capture 2
#define freq_win 7
#define freq_cursor 1

// Chess move sounds
#define MOVE 1
#define INVALID 2
#define CHECK 3
#define CAPTURE 4
#define WINNER 5


volatile int wavetable[1000];
volatile int audio_flag; //0 = nothing, 1 = place piece, 2 = error, 3 = check, 4 = capture, 5 = win, 6 = harry potter, 7 = menu cursor

#define FREQ_N  31
const static float FREQ_TABLE_HARRY_POTTER[FREQ_N] 	    = {123.47,	164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 146.83, 174.61, 123.47, 10.00, 123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 293.66, 277.18, 261.63, 207.65, 261.63, 246.94, 233.08, 116.54, 196.00, 164.81};
const static int TICK_TABLE_HARRY_POTTER[FREQ_N] 		= {5000, 7500, 2500, 5000, 10000, 5000, 15000, 15000, 7500, 2500, 5000, 10000, 5000, 25000, 2500, 5000, 7500, 2500, 5000, 10000, 5000, 10000, 5000, 10000, 5000, 7500, 2500, 5000, 10000, 5000, 25000};

const static float freq_array_place[freq_place] 	    = {523};
const static int tick_counts_place[freq_place] 		= {100};
const static float freq_array_error[freq_error] 	    = {783.99, 554.37};
const static int tick_counts_error[freq_error] 		= {50, 200};
const static float freq_array_check[freq_check] 	    = {146.83,138.59,130.81};
const static int tick_counts_check[freq_check] 		= {200, 200, 300};
const static float freq_array_capture[freq_capture] 	    = {146.83,185.00};
const static int tick_counts_capture[freq_capture] 		= {100, 200};
const static float freq_array_win[freq_win] 	    = {261.63, 329.63, 392.00, 1, 392.00, 329.63, 392.00};
const static int tick_counts_win[freq_win] 		= {250, 250, 250, 25, 375, 125, 500};
const static float freq_array_cursor[freq_cursor] 	    = {783.99};
const static int tick_counts_cursor[freq_cursor] 		= {30};

int offset;
int tick_counter;
int freq_idx;
int step;


#endif /* SRC_AUDIO_H_ */
