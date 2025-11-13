/*
 * timer.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Hihi
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "fsm.h"

#define cycle 10
extern int flag1,
		   flag2,
		   flag3,
		   flag4,
		   flag5;


void setTimer1(int);
void setTimer2(int);
void setTimer3(int);
void setTimer4(int);
void setTimer5(int);
void resetTimer(int);

void timerRun();

#endif /* INC_TIMER_H_ */
