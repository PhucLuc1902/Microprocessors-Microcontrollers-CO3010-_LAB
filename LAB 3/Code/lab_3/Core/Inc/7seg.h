/*
 * 7seg.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Hihi
 */

#ifndef INC_SEGMENT_H_
#define INC_SEGMENT_H_

#include "fsm.h"

extern int segment_buffer[4];

void set7SegNgang(int);
void set7SegDoc(int);
void scan7Seg(int);

void updateSegment2Digits(int, int);

#endif /* INC_SEGMENT_H_ */
