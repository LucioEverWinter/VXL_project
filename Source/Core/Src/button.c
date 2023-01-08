/*
 * button.c
 *
 *  Created on: Nov 20, 2022
 *      Author: Admin
 */

#include "button.h"

int KeyReg0[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimeOutForKeyPress[3] = {300, 300, 300};
int TimeOutForNoKeyPress = 1000;
int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}

int isButton2Pressed(){
	if(button2_flag == 1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}

int isButton3Pressed(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int i){
	if(i == 0)
		button1_flag = 1;
	else if(i == 1)
		button2_flag = 1;
	else if(i == 2)
		button3_flag = 1;
}

void getKeyInput(){
	for (int i = 0; i < 3; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];

		if ( i == 0) {
			KeyReg0[i] = HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin);
		}
		else if ( i == 1) {
			KeyReg0[i] = HAL_GPIO_ReadPin(BUT2_GPIO_Port, BUT2_Pin);
		}
		else if ( i == 2) {
			KeyReg0[i] = HAL_GPIO_ReadPin(BUT3_GPIO_Port, BUT3_Pin);
		}

		  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
			  KeyReg3[i] = KeyReg2[i];

			  if (KeyReg2[i] == PRESSED_STATE){

				subKeyProcess(i);

				TimeOutForKeyPress[i] = 300; // note: not need for step 1
				//One pressed
			  }
			}else{
			   TimeOutForKeyPress[i] --;
				if (TimeOutForKeyPress[i] == 0){
				  if (KeyReg2[i] == PRESSED_STATE){
					  subKeyProcess(i);				  //Long pressed
				  }


				  TimeOutForKeyPress[i] = 300;
				}
		    }
		}
	}
}
