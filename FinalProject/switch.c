#include "GPIO.h"
#include "switch.h"
#include "TM4C123GH6PM.h"




void BUTTON_voidINIT(char port , char  pin){
	  GPIO_Init(port, pin, INPUT, DIGITAL);
    GPIO_SetDirection(port, pin, INPUT);
    GPIO_EnablePullUp(port, pin);
}
char BUTTON_charRead(char port ,char pin){
	return GPIO_ReadPin(port,pin);
}
