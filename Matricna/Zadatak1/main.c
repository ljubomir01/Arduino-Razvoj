/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Ljubomir
 */
#include <avr/io.h>
#include <stdint.h>

#include "usart.h"
#include "keypad.h"

uint8_t rows[4] = {11, 10, 9, 8};

uint8_t cols[4] = {7, 6, 5, 4};

int16_t main(){
	uint8_t button;
	usartInit(9600);
	keypadInit(rows, cols);
	while(1){
		button = keypadScan();
		if(button != 0x00){
			usartPutChar(button);
			usartPutChar('\n');
		}
	}
	return 0;
}
