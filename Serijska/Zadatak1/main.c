#include <stdio.h>
#include <stdlib.h>

#include "usart.h"
#include "timer0.h"

#define MAX_BUFFER_SIZE 64

int16_t main(){

	int8_t ImePrezime[MAX_BUFFER_SIZE + 1];

	usartInit(9600);
	timer0InteruptInit();

	while(1){
		usartPutString("Unesite svoje ime i prezime:");

		while(usartAvailable() == 0);
		timer0DelayMs(100);

		usartGetString(ImePrezime);
		timer0DelayMs(100);

		usartPutString("Zdravo, ");
		usartPutString(ImePrezime);
	}
	return 0;
}
