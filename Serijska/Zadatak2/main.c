/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Ljubomir
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "timer0.h"

int16_t main(){

	int8_t rec[65];
	int8_t samoglasnici = 0;
	int8_t samoglasnici_string[3];

	usartInit(9600);
	timer0InteruptInit();

	while(1){
		usartPutString("Unesite rec:");
		while(usartAvailable() == 0);
		timer0DelayMs(500);
		usartGetString(rec);
		for(int i = 0; rec[i] != '\0'; i++){
			if(rec[i] == 'a' || rec[i] == 'e' || rec[i] == 'i' || rec[i] == 'o' || rec[i] == 'u')
				samoglasnici++;
		}
	}
	itoa(samoglasnici, samoglasnici_string, 10);
	usartPutString("Rec ima ");
	usartPutString(samoglasnici_string);
	usartPutString(" samoglasnika.");
	return 0;
}
