/*
 * 7seg.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Hihi
 */


#include "7seg.h"

int segment_buffer[4] = {0};

GPIO_PinState pinArr[11][7] = {
	    {0, 0, 0, 0, 0, 0, 1}, //0
	    {1, 0, 0, 1, 1, 1, 1}, //1
	    {0, 0, 1, 0, 0, 1, 0}, //2
	    {0, 0, 0, 0, 1, 1, 0}, //3
	    {1, 0, 0, 1, 1, 0, 0}, //4
	    {0, 1, 0, 0, 1, 0, 0}, //5
	    {0, 1, 0, 0, 0, 0, 0}, //6
	    {0, 0, 0, 1, 1, 1, 1}, //7
	    {0, 0, 0, 0, 0, 0, 0}, //8
	    {0, 0, 0, 0, 1, 0, 0}, //9
		{1, 1, 1, 1, 1, 1, 1}  //ALL LED TURN OFF
};

void set7SegNgang(int num){
	if (num >= 0 && num <= 9){
		for (int state = 0; state < 7; state++){
			HAL_GPIO_WritePin(a_n_GPIO_Port, a_n_Pin << state, pinArr[num][state]);
		}
	}
	else{
		for(int state = 0; state < 7; state++){ // Turn off
			HAL_GPIO_WritePin(a_n_GPIO_Port, a_n_Pin << state, pinArr[10][state]);
		}
	}
}

void set7SegDoc(int num){
	if (num >= 0 && num <= 9){
		for (int state = 0; state < 7; state++){
			HAL_GPIO_WritePin(a_d_GPIO_Port, a_d_Pin << state, pinArr[num][state]);
		}
	}
	else {
		for(int state = 0; state < 7; state++){ // Turn off
			HAL_GPIO_WritePin(a_d_GPIO_Port, a_d_Pin << state, pinArr[10][state]);
		}
	}
}


void scan7Seg (int state){
	state = state % 2;
	switch (state){
	case 0:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, 0);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, 1);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, 0);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, 1);
		set7SegNgang(segment_buffer[0]);
		set7SegDoc(segment_buffer[2]);
		break;
	case 1:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, 1);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, 0);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, 1);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, 0);
		set7SegNgang(segment_buffer[1]);
		set7SegDoc(segment_buffer[3]);
		break;
	default:
		break;
	}
}

void updateSegment2Digits(int firstNum, int secNum){
	segment_buffer[0] = firstNum / 10;
	segment_buffer[1] = firstNum % 10;
	segment_buffer[2] = secNum / 10;
	segment_buffer[3] = secNum % 10;
}
