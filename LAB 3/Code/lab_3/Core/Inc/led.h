/*
 * led.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Hihi
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include "fsm.h"

#define LED_ON		0
#define LED_OFF		1

extern int Ngang_State;
extern int Doc_State;

void setLedNgang (int);
void setLedDoc (int);

#endif /* INC_LED_H_ */
