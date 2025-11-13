/*
 * button.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Hihi
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "fsm.h"

#define NUM_OF_BUTTON 3
#define PRESSED 0
#define RELEASED 1

int isButtonPressed(int);
void buttonRead();

#endif /* INC_BUTTON_H_ */
