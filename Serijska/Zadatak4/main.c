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

#define MAX_BUFFER_SIZE 64
#define NUM_OF_ALPHABET 26

int16_t main(){
	int16_t is_pangram;
	int8_t text[MAX_BUFFER_SIZE + 1];
	int16_t all_letters[NUM_OF_ALPHABET];

	usartInit(9600);
	timer0InteruptInit();

	while(1){
		usartPutString("Ulaz: ");

		while(usartAvailable() == 0);

		usartGetString(text);
		usartPutString(text);

		for(int i = 0; text[i] != '\0'; i++){
			if(text[i] >= 'a' && text[i] <= 'z')
				all_letters[text[i] - 'a']++;
			else if(text[i] >= 'A' && text[i] <= 'Z')
				all_letters[text[i] - 'A']++;
		}
		for(int i = 0; i < NUM_OF_ALPHABETS; i++){
			if(all_letters[i] == 0)
				is_pangram = 0;
		}
		if(is_pangram)
			usartPutString("Jeste");
		else
			usartPutString("Nije");
	}
}
