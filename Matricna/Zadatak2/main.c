/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Ljubomir
 */
#include <stdio.h>
#include <stdlib.h>

#include "usart.h"
#include "timer0.h"
#include "keypad.h"

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main(){
	int8_t button;
	int8_t last_state_button = '\0';

	usartInit(9600);
	timer0InteruptInit();
	keypadInit(rows, cols);

	while(1){
		button = keypadScan();
		if(button != last_state_button){
			timer0DelayMs(10);
			button = keypadScan();
			if(button != last_state_button)
				if(button != 0x00)
					usartPutChar(button);
			}
		last_state_button = button;
	}
	return 0;
}
