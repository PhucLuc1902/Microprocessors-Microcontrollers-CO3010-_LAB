/*
 * fsm.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Hihi
 */


#include "fsm.h"

int fsm_state_ngang = 1;
int fsm_state_doc = 1;
int manual_state = IDLE;

int red_duration = 5;
int yel_duration = 2;
int grn_duration = 3;

int red_temp = 1;
int yel_temp = 1;
int grn_temp = 1;

int ngang_timer_counter = 0;
int doc_timer_counter = 0;
int scan = 0;

void segmentUpdateAuto(){
	updateSegment2Digits(ngang_timer_counter, doc_timer_counter);
}

void fsm_run(){
	fsm_mod1_ngang();
	fsm_mod1_doc();
	fsm_manual();
}

void mode_changing(){
	if (isButtonPressed(0) == 1){
		resetTimer(-1);
		ngang_timer_counter = 0, doc_timer_counter = 0;
		updateSegment2Digits(IDLE, IDLE);
		scan = 0;
		setLedNgang(IDLE);
		setLedDoc(IDLE);
		fsm_state_ngang = IDLE;
		fsm_state_doc = IDLE;
		manual_state = MANUAL_RED;
		setTimer1(100);
		setTimer3(100);
		return;
	}
}

void fsm_mod1_ngang(){
	switch(fsm_state_ngang){
	case INIT:
		setTimer1(red_duration * 1000); // bo dem thoi gian chuyen den
		setTimer2(1000); // gia tri cap nhat cho den 7SEG
		setTimer3(100);  //scan 7SEG
		ngang_timer_counter = red_duration;
		fsm_state_ngang = RED;
		break;
	case RED:
		setLedNgang(RED);
		if (flag2 == 1){
			ngang_timer_counter--;
			setTimer2(1000);
		}
		if (flag1 == 1){ //switch state
			setTimer1(grn_duration * 1000);
			ngang_timer_counter = grn_duration;
			fsm_state_ngang = GRN;
		}
		if (flag3 == 1){
			segmentUpdateAuto();
			scan = (scan == 1) ? 0 : 1;
			scan7Seg(scan);
			setTimer3(100);
		}
		mode_changing();
		break;
	case GRN:
		setLedNgang(GRN);
		if (flag2 == 1){
			ngang_timer_counter--;
			setTimer2(1000);
		}

		if (flag1 == 1){
			setTimer1(yel_duration * 1000);
			ngang_timer_counter = yel_duration;
			fsm_state_ngang = YEL;
		}
		if (flag3 == 1){
			segmentUpdateAuto();
			scan = (scan == 1) ? 0 : 1;
			scan7Seg(scan);
			setTimer3(100);
		}
		mode_changing();
		break;
	case YEL:
		setLedNgang(YEL);
		if (flag2 == 1){
			ngang_timer_counter--;
			setTimer2(1000);
		}

		if (flag1 == 1){
			setTimer1(red_duration * 1000);
			ngang_timer_counter = red_duration;
			fsm_state_ngang = RED;
		}
		if (flag3 == 1){
			segmentUpdateAuto();
			scan = (scan == 1) ? 0 : 1;
			scan7Seg(scan);
			setTimer3(100);
		}
		mode_changing();
		break;
	default: //IDLE
		break;
	}
}

void fsm_mod1_doc(){
    switch(fsm_state_doc){
    case INIT:
        setTimer4(grn_duration * 1000); // bo dem thoi gian chuyen den
        setTimer5(1000); //gia tri cap nhat cho den 7SEG
        doc_timer_counter = grn_duration;
        fsm_state_doc = GRN;
        break;
    case GRN:
    	setLedDoc(GRN);
    	if (flag5 == 1){
    		doc_timer_counter--;
    		setTimer5(1000);
    	}
    	if (flag4 == 1){
    		setTimer4(yel_duration * 1000);
    		doc_timer_counter = yel_duration;
    		fsm_state_doc = YEL;
    	}
    	break;
    case YEL:
    	setLedDoc(YEL);
    	if (flag5 == 1){
    		doc_timer_counter--;
    		setTimer5(1000);
    	}
    	if (flag4 == 1){
    		setTimer4(red_duration * 1000);
    		doc_timer_counter = red_duration;
    		fsm_state_doc = RED;
    	}
    	break;
    case RED:
    	setLedDoc(RED);
    	if (flag5 == 1){
    		doc_timer_counter--;
    		setTimer5(1000);
    	}
    	if (flag4 == 1){
    		setTimer4(grn_duration * 1000);
    		doc_timer_counter = grn_duration;
    		fsm_state_doc = GRN;
    	}
    	break;
    default: break;
    }
}


void fsm_manual(){
	switch(manual_state){
	case MANUAL_RED:
		updateSegment2Digits(red_temp, 1);
		if (isButtonPressed(0) == 1){
			red_temp = 1;
			manual_state = MANUAL_YEL;
			setLedDoc(IDLE);
			setLedNgang(IDLE);
			setTimer1(100);
			setTimer3(100);
		}

		if (isButtonPressed(1) == 1){ // Doi thoi gian tu 1-99
			red_temp = (red_temp == 99) ? 1 : red_temp + 1;

		}
		if (isButtonPressed(2) == 1){ //Nut 3 de luu gia tri
			red_duration = red_temp;
		}
		if (flag1 == 1){ // chuyen timer Led Red sang 2Hz
			HAL_GPIO_TogglePin(red_n_GPIO_Port, red_n_Pin);
			HAL_GPIO_TogglePin(red_d_GPIO_Port, red_d_Pin);
			setTimer1(250);
		}
		if (flag3 == 1){ // scan va hien 7SEG
			scan = (scan + 1)%2;
			scan7Seg(scan);
			setTimer3(100);
		}
		break;
	case MANUAL_YEL:
		updateSegment2Digits(yel_temp, 2);
		if (isButtonPressed(0) == 1){
			yel_temp = 1;
			manual_state = MANUAL_GRN;
			setLedDoc(IDLE);
			setLedNgang(IDLE);
			setTimer1(100);
			setTimer3(100);
		}

		if (isButtonPressed(1) == 1){ // Doi thoi gian tu 1-99
			yel_temp = (yel_temp == 99) ? 1 : yel_temp + 1;

		}
		if (isButtonPressed(2) == 1){ //Nut 3 de luu gia tri
			yel_duration = yel_temp;
		}
		if (flag1 == 1){ // chuyen timer Led Yel sang 2Hz
			HAL_GPIO_TogglePin(yel_n_GPIO_Port, yel_n_Pin);
			HAL_GPIO_TogglePin(yel_d_GPIO_Port, yel_d_Pin);
			setTimer1(250);
		}
		if (flag3 == 1){ // scan va hien 7SEG
			scan = (scan + 1)%2;
			scan7Seg(scan);
			setTimer3(100);
		}
		break;
	case MANUAL_GRN:
		updateSegment2Digits(grn_temp, 3);
		if (isButtonPressed(1) == 1){ // Doi thoi gian tu 1-99
			grn_temp = (grn_temp == 99) ? 1 : grn_temp + 1;
		}
		if (isButtonPressed(2) == 1){ //Nut 3 de luu gia tri
			grn_duration = grn_temp;
		}
		if (isButtonPressed(0) == 1){
			red_duration = grn_duration + yel_duration; //checking logic

			setLedNgang(ALL); // Ra tinh hieu reset
			setLedDoc(ALL);
            updateSegment2Digits(88, 88);

			setTimer1(500);
			manual_state = MANUAL_RESET;
			return;
		}

		if (flag1 == 1){ // chuyen timer Led Grn sang 2Hz
			HAL_GPIO_TogglePin(grn_n_GPIO_Port, grn_n_Pin);
			HAL_GPIO_TogglePin(grn_d_GPIO_Port, grn_d_Pin);
			setTimer1(250);
		}
		if (flag3 == 1){ // scan va hien 7SEG
			scan = (scan + 1)%2;
			scan7Seg(scan);
			setTimer3(100);
		}
		break;

	case MANUAL_RESET:
		if(flag1 == 1){ // reset lai sau 0.5s
			setLedDoc(IDLE);
			setLedNgang(IDLE);
			updateSegment2Digits(IDLE, IDLE);
			resetTimer(0);
			manual_state = IDLE;
			fsm_state_ngang = 1;
			fsm_state_doc = 1;
		}
		break;
	default:
		break;
	}
}
