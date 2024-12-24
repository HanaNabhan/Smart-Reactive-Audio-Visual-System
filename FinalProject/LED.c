#include "LED.h"
#include "GPIO.h"

void LED_voidINIT(char port, char pin){

	GPIO_Init(port, pin, OUTPUT, DIGITAL);

}
void LED_voidON(char port, char pin){

	GPIO_WritePin(port,pin,1);

}
void LED_voidOFF(char port, char pin){

	GPIO_WritePin(port,pin,0);

}

