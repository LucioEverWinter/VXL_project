/*
 * fsm.c
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#include "fsm.h"

int state = 4;
int Traffic_1 = 0;
int Traffic_2 = 0;

int flag_stay = 0;

int timeRED  = 5000;
int timeGREEN  = 3000;
int timeYELLOW  = 2000;

int tempRED = 0;
int tempYELLOW = 0;
int tempGREEN = 0;

void fsm_run() {
	switch (state) {
	case Manual_INIT:
		setTimer1(1000);
		setTimer2(1000);

		HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 0);
		HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 0);

		HAL_GPIO_WritePin(Traffic2_1_GPIO_Port, Traffic2_1_Pin, 0);
		HAL_GPIO_WritePin(Traffic2_2_GPIO_Port, Traffic2_2_Pin, 0);

		state = Manual_RUN;
		break;
	case Manual_RUN:
		if (isButton1Pressed() == 1) {
			state = Manual_RED;

			HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 0);
			HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 0);

			HAL_GPIO_WritePin(Traffic2_1_GPIO_Port, Traffic2_1_Pin, 0);
			HAL_GPIO_WritePin(Traffic2_2_GPIO_Port, Traffic2_2_Pin, 0);
		}
		else if (isButton2Pressed() == 1) {
			flag_stay = 1;
			fsm_pes();
		}
		else {
			fsm_auto();
		}
		break;
	case Manual_RED:
		if (isButton1Pressed() == 1) {
			state = Manual_YELLOW;
		}

		if (isButton2Pressed() == 1) {
			tempRED++;
			if (tempRED >= 100) tempRED = 0;
		}

		if (isButton3Pressed() == 1) {
			timeRED = tempRED * 1000;
			tempRED = 0;
		}
		break;
	case Manual_YELLOW:
		if (isButton1Pressed() == 1) {
			state = Manual_GREEN;
		}

		if (isButton2Pressed() == 1) {
			tempYELLOW++;
			if (tempYELLOW >= 100) tempYELLOW = 0;
		}

		if (isButton3Pressed() == 1) {
			timeYELLOW = tempYELLOW * 1000;
			tempYELLOW = 0;
		}
		break;
	case Manual_GREEN:
		if (isButton1Pressed() == 1) {
			state = Manual_INIT;
		}

		if (isButton2Pressed() == 1) {
			tempGREEN++;
			if (tempGREEN >= 100) tempGREEN = 0;
		}

		if (isButton3Pressed() == 1) {
			timeGREEN = tempGREEN * 1000;
			tempGREEN = 0;
		}
		break;
	default:
		break;
	}
}

void fsm_auto() { // auto fsm for normal run
	switch (Traffic_1) {
		case Traffic_INIT:
			setTimer1(timeGREEN);
			Traffic_1 = Traffic_GREEN;
			HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 0);
			HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 1);
			break;
		case Traffic_RED:
			if (timer1_flag == 1) {
				setTimer1(timeGREEN);
				Traffic_1 = Traffic_GREEN;
				HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 0);
				HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 1);
			}
			break;
		case Traffic_YELLOW:
			if (timer1_flag == 1) {
				setTimer1(timeRED);
				Traffic_1 = Traffic_RED;
				HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 1);
				HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 0);
			}
			break;
		case Traffic_GREEN:
			if (timer1_flag == 1) {
				setTimer1(timeYELLOW);
				Traffic_1 = Traffic_YELLOW;
				HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 1);
				HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 1);
			}
			break;
		default:
			break;
	}

	switch (Traffic_2) {
		case Traffic_INIT:
			setTimer1(timeRED);
			Traffic_2 = Traffic_RED;
			HAL_GPIO_WritePin(Traffic1_1_GPIO_Port, Traffic1_1_Pin, 1);
			HAL_GPIO_WritePin(Traffic1_2_GPIO_Port, Traffic1_2_Pin, 0);
			break;
		case Traffic_RED:
			if (timer2_flag == 1) {
				setTimer2(timeGREEN);
				Traffic_2 = Traffic_GREEN;
				HAL_GPIO_WritePin(Traffic2_1_GPIO_Port, Traffic2_1_Pin, 0);
				HAL_GPIO_WritePin(Traffic2_2_GPIO_Port, Traffic2_2_Pin, 1);
			}
			break;
		case Traffic_YELLOW:
			if (timer2_flag == 1) {
				setTimer2(timeRED);
				Traffic_2 = Traffic_RED;
				HAL_GPIO_WritePin(Traffic2_1_GPIO_Port, Traffic2_1_Pin, 1);
				HAL_GPIO_WritePin(Traffic2_2_GPIO_Port, Traffic2_2_Pin, 0);
			}
			break;
		case Traffic_GREEN:
			if (timer2_flag == 1) {
				setTimer2(timeYELLOW);
				Traffic_2 = Traffic_YELLOW;
				HAL_GPIO_WritePin(Traffic2_1_GPIO_Port, Traffic2_1_Pin, 1);
				HAL_GPIO_WritePin(Traffic2_2_GPIO_Port, Traffic2_2_Pin, 1);
			}
			break;
		default:
			break;
	}
}

void fsm_pes(){
	if (isButton3Pressed() == 1) {
		flag_stay = 0;
	}
}
