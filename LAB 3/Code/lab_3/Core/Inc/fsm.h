/*
 * fsm.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Hihi
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "button.h"
#include "main.h"
#include "timer.h"
#include "7seg.h"
#include "led.h"

#define RED		11
#define YEL		22
#define GRN		33
#define ALL 	44

#define INIT 1

#define MANUAL_RED 10
#define MANUAL_YEL	20
#define	MANUAL_GRN 30
#define	MANUAL_RESET 40

#define IDLE 	-1

void segmentUpdateAuto();

void mode_changing();

void fsm_run();
void fsm_mod1_ngang();
void fsm_mod1_doc();
void fsm_manual();

#endif /* INC_GLOBAL_H_ */
