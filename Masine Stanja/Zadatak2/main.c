/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Ljubomir
 */
#include "usart.h"
#include "timer0.h"
#include "pin.h"

int8_t checkDigit(int8_t c){
	while(usartAvailable() == 0);
	if(usartGetChar() == c)
		return 1;
	else
		return 0;
}

int16_t main(){
	enum state_t{LOCKED, NUM1, NUM2, UNLOCKED, BROKEN};
	enum state_t state = LOCKED;

	pinInit(PORT_B, 5, OUTPUT);
	usartInit(115200);
	timer0InteruptInit();

	while(1){
		switch(state){
		case LOCKED:
			if(checkDigit('1')){
				pinPulsing(PORT_B, 5, 2000, 1);
				state = NUM1;
			}else{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case NUM1:
			if(checkDigit('2')){
				pinPulsing(PORT_B, 5, 2000, 1);
				state = NUM2;
			}else{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case NUM2:
			if(checkDigit(3)){
				pinPulsing(PORT_B, 5, 2000, 3);
				state = UNLOCKED;
			}else{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case BROKEN:
			if(checkDigit('7')){
				pinReversePulse(PORT_B, 5, 500);
				if(checkDigit('8')){
					pinReversePulse(PORT_B, 5, 500);
					if(checkDigit('9')){
						pinSetValue(PORT_B, 5, LOW);
						state = LOCKED;
					}else{
						pinReversePulse(PORT_B, 5, 500);
						pinReversePulse(PORT_B, 5, 500);
					}
				}else{
					pinReversePulse(PORT_B, 5, 500);
					pinReversePulse(PORT_B, 5, 500);
				}
			}else{
				pinReversePulse(PORT_B, 5, 500);
				pinReversePulse(PORT_B, 5, 500);
			}
			break;
		}
		case UNLOCKED:
			break;
	}
	return 0;
}

