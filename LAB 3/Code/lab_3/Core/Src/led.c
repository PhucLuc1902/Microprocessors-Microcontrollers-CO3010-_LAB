/*
 * led.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Hihi
 */

#include "led.h"

int Ngang_State= 0;
int Doc_State= 0;

void setLedNgang(int colour){
	switch(colour){
	case RED:
		HAL_GPIO_WritePin(red_n_GPIO_Port, red_n_Pin, LED_ON);
		HAL_GPIO_WritePin(yel_n_GPIO_Port, yel_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_n_GPIO_Port, grn_n_Pin, LED_OFF);
		Ngang_State= RED;
		break;
	case YEL:
		HAL_GPIO_WritePin(red_n_GPIO_Port, red_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_n_GPIO_Port, yel_n_Pin, LED_ON);
		HAL_GPIO_WritePin(grn_n_GPIO_Port, grn_n_Pin, LED_OFF);
		Ngang_State= YEL;
		break;
	case GRN:
		HAL_GPIO_WritePin(red_n_GPIO_Port, red_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_n_GPIO_Port, yel_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_n_GPIO_Port, grn_n_Pin, LED_ON);
		Ngang_State= GRN;
		break;
	case ALL:
		HAL_GPIO_WritePin(red_n_GPIO_Port, red_n_Pin, LED_ON);
		HAL_GPIO_WritePin(yel_n_GPIO_Port, yel_n_Pin, LED_ON);
		HAL_GPIO_WritePin(grn_n_GPIO_Port, grn_n_Pin, LED_ON);
		Ngang_State = ALL;
		break;
	default:
		HAL_GPIO_WritePin(red_n_GPIO_Port, red_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_n_GPIO_Port, yel_n_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_n_GPIO_Port, grn_n_Pin, LED_OFF);
		Ngang_State= 0;
		break;
	}
}

void setLedDoc(int colour){
	switch(colour){
	case RED:
		HAL_GPIO_WritePin(red_d_GPIO_Port, red_d_Pin, LED_ON);
		HAL_GPIO_WritePin(yel_d_GPIO_Port, yel_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_d_GPIO_Port, grn_d_Pin, LED_OFF);
		Doc_State= RED;
		break;
	case YEL:
		HAL_GPIO_WritePin(red_d_GPIO_Port, red_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_d_GPIO_Port, yel_d_Pin, LED_ON);
		HAL_GPIO_WritePin(grn_d_GPIO_Port, grn_d_Pin, LED_OFF);
		Doc_State= YEL;
		break;
	case GRN:
		HAL_GPIO_WritePin(red_d_GPIO_Port, red_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_d_GPIO_Port, yel_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_d_GPIO_Port, grn_d_Pin, LED_ON);
		Doc_State= GRN;
		break;
	case ALL:
		HAL_GPIO_WritePin(red_d_GPIO_Port, red_d_Pin, LED_ON);
		HAL_GPIO_WritePin(yel_d_GPIO_Port, yel_d_Pin, LED_ON);
		HAL_GPIO_WritePin(grn_d_GPIO_Port, grn_d_Pin, LED_ON);
		Doc_State = ALL;
		break;
	default:
		HAL_GPIO_WritePin(red_d_GPIO_Port, red_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(yel_d_GPIO_Port, yel_d_Pin, LED_OFF);
		HAL_GPIO_WritePin(grn_d_GPIO_Port, grn_d_Pin, LED_OFF);
		Doc_State= 0;
		break;
	}
}

