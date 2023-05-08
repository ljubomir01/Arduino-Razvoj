/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Ljubomir
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "timer0.h"
#include "usart.h"

#define MAX_BUFFER_SIZE 64

int8_t capital(int8_t str[]);

int16_t main(){
	int8_t text[MAX_BUFFER_SIZE + 1];
	usartInit(9600);
	timer0InteruptInit();
	while(1){
		usartPutString("Ulaz:");
		while(usartAvailable() == 0);
		timer0DelayMs(500);
		usartGetString(text);
		usartPutString(text);
		text = capital(text);
		usartPutString("Izlaz:");
		usartPutString(text);
	}
	return 0;
}

int8_t capital(int8_t str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'a' && str[i] < 'z')
			str[i] -= 32;
	}
	return str;
}
