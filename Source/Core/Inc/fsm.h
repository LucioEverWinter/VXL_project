/*
 * fsm.h
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
//#include "global.h"
#include "button.h"

#define Traffic_INIT 0

#define Traffic_RED 1

#define Traffic_YELLOW 2

#define Traffic_GREEN 3

#define Manual_INIT 4

#define Manual_RUN 5 // I just name it like this for sake of easy to remember, it's actually auto run

#define Manual_RED 6

#define Manual_YELLOW 7

#define Manual_GREEN 8


void fsm_run();

void fsm_auto();

void fsm_pes();

#endif /* INC_FSM_H_ */
