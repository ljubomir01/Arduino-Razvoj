#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timer0.h"
#include "keypad.h"
#include "usart.h"

#define MAX_BUFFER_SIZE 64

uint8_t rows[4] = {11, 10, 9, 8};
uint8_t cols[4] = {7, 6, 5, 4};

int16_t main(){
	int8_t button;
	int8_t number;
	int8_t button_last_state = '\0';
	int8_t dozvola = '1';
	int8_t ulazni_broj[MAX_BUFFER_SIZE + 1];
	int8_t binarni[MAX_BUFFER_SIZE + 1];
	int8_t heksadecimalni[MAX_BUFFER_SIZE + 1];
	int16_t broj, i = 0, prost = 1;

	usartInit(9600);
	timer0InteruptInit();
	keypadInit(rows, cols);

	while(1){
		button = keypadScan();
		if(button != '\0' && dozvola = '1'){
			dozvola = 0;
			if(button >= '0' && button <= '9'){
				ulazni_broj [i] = button;
				ulazni_broj[i + 1] = '\0';
				i++;
			}else if(button == '#'){
				i = 0;
				broj = atoi(ulazni_broj);
				itoa(ulazni_broj, binarni, 2);
				itoa(ulazni_broj, heksadecimalni, 16);
				for(int j = 2; j <= j/2; j++)
					if(broj % 2 == 0)
						prost = 0;
				if (prost == 1)
					usartPutString("Je prost");
				else
					usartPutString("Nije prost");
				usartPutString("Bin:");
				usartPutString(binarni);

				usartPutString("Heks: ");
				usartPutString(heksadecimalni);
				prost = 1;
			}
		}
		if(button == '\0')
			dozvola = '1';
	}
	return 0;
}
