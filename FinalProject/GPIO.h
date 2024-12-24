#ifndef GPIO_H
#define GPIO_H
#include "TM4C123GH6PM.h"

#define OUTPUT 1
#define INPUT 0
#define DIGITAL 1
#define ANALOG 0
#define PULLUP_EN 1
#define PULLDOWN_EN 0
#define MAX_PORTS 7
#define MAX_PINS 8
#define GPIO_MODE 0
#define Alternate_Function_MODE 1
static GPIOA_Type* const GPIO_PORTS[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};
void GPIO_EnableClock(char port);
void GPIO_Init(char port ,char pin ,char dir ,char mode );
void GPIO_SetDirection(char port , char pin , char dir);
void GPIO_analog_digital(char port , char pin , char digt_ana);
int GPIO_ReadPin(char port, char pin);
void GPIO_WritePin(char port, char pin, int value);
void GPIO_EnablePullUp(char port, char pin);
void GPIO_MODE_SELECT(char port,char pin,char mode);
#endif
