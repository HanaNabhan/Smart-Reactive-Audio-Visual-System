#include "GPIO.h"

#include "TM4C123GH6PM.h"

static GPIOA_Type* const GPIO_PORTS[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};

void GPIO_EnableClock(char port) {
		volatile int delay = 0; // Use a volatile variable to prevent optimization

    SYSCTL->RCGC2 |= (1 << port); 
    for (delay = 0; delay < 4; delay++); // Simple loop for delay

    	
}
void GPIO_Init(char port ,char pin ,char dir ,char mode ){
		GPIO_EnableClock(port);
		if (dir == INPUT) {
        GPIO_PORTS[port]->DIR &= ~(1 << pin); 
    } else {
        GPIO_PORTS[port]->DIR |= (1 << pin);  
    }
			
		if (mode == DIGITAL) { 
        GPIO_PORTS[port]->AMSEL &= ~(1 << pin);  
        GPIO_PORTS[port]->DEN |= (1 << pin);     
    } else {         
        GPIO_PORTS[port]->DEN &= ~(1 << pin);    
        GPIO_PORTS[port]->AMSEL |= (1 << pin);   
    }
	}

	
void GPIO_SetDirection(char port, char pin, char dir) {
    if (dir == INPUT) {
        GPIO_PORTS[port]->DIR &= ~(1 << pin);
    } else {
        GPIO_PORTS[port]->DIR |= (1 << pin);
    }
}
void GPIO_analog_digital(char port, char pin, char digt_ana) {
    if (digt_ana == DIGITAL) { 
        GPIO_PORTS[port]->AMSEL &= ~(1 << pin);  
        GPIO_PORTS[port]->DEN |= (1 << pin);     
    } else {         
        GPIO_PORTS[port]->DEN &= ~(1 << pin);    
        GPIO_PORTS[port]->AMSEL |= (1 << pin);   
    }
}

int GPIO_ReadPin(char port, char pin) {
    return (GPIO_PORTS[port]->DATA & (1 << pin)) ? 1 : 0;
}
void GPIO_WritePin(char port, char pin, int value) {
    if (value) {
        GPIO_PORTS[port]->DATA |= (1 << pin);  
    } else {
        GPIO_PORTS[port]->DATA &= ~(1 << pin);
    }
}
void GPIO_EnablePullUp(char port, char pin) {
    GPIO_PORTS[port]->PUR |= (1 << pin); 
}
