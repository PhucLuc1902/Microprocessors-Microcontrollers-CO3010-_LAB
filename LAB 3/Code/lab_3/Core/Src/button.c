/*
 * button.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Hihi
 */


#include "button.h"

int buttonFlag[NUM_OF_BUTTON] = {0, 0, 0};
int timeout[NUM_OF_BUTTON] = {100, 100, 100}; // Kiem tra co phai giu hay ko

int button_stage_0[NUM_OF_BUTTON] = {RELEASED, RELEASED, RELEASED}; // Lan bam dau
int button_stage_1[NUM_OF_BUTTON] = {RELEASED, RELEASED, RELEASED}; // Lich su lan bam 1
int button_stage_2[NUM_OF_BUTTON] = {RELEASED, RELEASED, RELEASED}; // Lich su lan bam 2
int button_stage_3[NUM_OF_BUTTON] = {RELEASED, RELEASED, RELEASED}; // Lich su lan bam 3

int isButtonPressed(int num){
	if (buttonFlag[num] == 1){
		buttonFlag[num] = 0;
		return 1;
	}
	return 0;
}

void buttonRead(){
	for (int i = 0; i < NUM_OF_BUTTON; i++){
		button_stage_2[i] = button_stage_1[i];
		button_stage_1[i] = button_stage_0[i];
		button_stage_0[i] = HAL_GPIO_ReadPin(sw0_GPIO_Port, sw0_Pin << i);
		if ((button_stage_1[i] == button_stage_0[i]) && (button_stage_1[i] == button_stage_2[i])){
			if (button_stage_2[i] != button_stage_3[i]){ // stage2 != stage3
				button_stage_3[i] = button_stage_2[i];
				if (button_stage_0[i] == PRESSED){
					timeout[i] = 100;
					buttonFlag[i] = 1;
				}
			}
			else { //stage2 == stage3
				timeout[i]--;
				if (timeout[i] == 0){
					timeout[i] = 10;
					if (button_stage_3[i] == PRESSED){
						buttonFlag[i] = 1;
					}
				}
			}
		}
	}
}
