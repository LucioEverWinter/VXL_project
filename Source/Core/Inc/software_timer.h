/*
 * software_timer.h
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

void setTimer0(int duration);
void setTimer1(int duration);
void setTimer2(int duration);
void timer_run();
extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;
#endif /* INC_SOFTWARE_TIMER_H_ */
