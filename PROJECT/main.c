#include "GPIO.h"
#include "LCD.h"
#include "LED.h"
#include "switch.h"
#include "timer.h"
#include "ADC.h"
#include <stdio.h>
#include <stdlib.h>
#include "TExaS.h"

#define TIMER2_ICR_R (*((volatile unsigned long *)0x40032024))
#define SWITCH1_PIN 2 // PA2 for LCD
#define SWITCH2_PIN 5 // PC5 for LED
#define LED1_PIN 3    // PA3
#define LED2_PIN 4    // PA4
#define LED3_PIN 5    // PA5
#define LED4_PIN 6    // PA6

unsigned int state1 = 0, state2 = 0; // Toggle the LED status
char flag1 = 1, flag2 = 1;           // Prevent multiple toggles in one push
unsigned int reading = 0;           // ADC reading

void displayOnLCD(unsigned int audio_value) {
    char buffer[16];
    sprintf(buffer, "Audio: %d", audio_value);
    LCD_vCLR();
    LCD_WriteString(buffer);
}

void displayOnLED(int audio_value) {
    if (audio_value < 155) { // Turn on 1 LED
        LED_voidON(0, LED1_PIN);
        LED_voidOFF(0, LED2_PIN);
        LED_voidOFF(0, LED3_PIN);
        LED_voidOFF(0, LED4_PIN);
    } else if (audio_value < 160) { // Turn on 2 LEDs
        LED_voidON(0, LED1_PIN);
        LED_voidON(0, LED2_PIN);
        LED_voidOFF(0, LED3_PIN);
        LED_voidOFF(0, LED4_PIN);
    } else if (audio_value < 4089) { // Turn on 3 LEDs
        LED_voidON(0, LED1_PIN);
        LED_voidON(0, LED2_PIN);
        LED_voidON(0, LED3_PIN);
        LED_voidOFF(0, LED4_PIN);
    } else { // Turn on 4 LEDs
        LED_voidON(0, LED1_PIN);
        LED_voidON(0, LED2_PIN);
        LED_voidON(0, LED3_PIN);
        LED_voidON(0, LED4_PIN);
    }
}

void TurnOffLEDS(void) {
    LED_voidOFF(0, LED1_PIN);
    LED_voidOFF(0, LED2_PIN);
    LED_voidOFF(0, LED3_PIN);
    LED_voidOFF(0, LED4_PIN);
}

void setup() {
    // Initialize drivers
    LCD4bits_Init();
    LCD_vCLR();
    BUTTON_voidINIT(0, SWITCH1_PIN); // Switch 1: Port A, Pin 2
    BUTTON_voidINIT(2, SWITCH2_PIN); // Switch 2: Port C, Pin 5
    LED_voidINIT(0, LED1_PIN); // init
    LED_voidINIT(0, LED2_PIN);
    LED_voidINIT(0, LED3_PIN);
    LED_voidINIT(0, LED4_PIN);
    ADC0_Init_Ch0();
    Timer2_Init(80000);
	LCD_vMoveCursor(1, 5);
    LCD_WriteString("WELCOME");
	LCD_vMoveCursor(2, 3);
    LCD_WriteString("SMART AUDIO!");
    Timer2_Delay(3000); 
}

int main() {

	TExaS_Init();
    setup();

    while (1) {
    // Read the current ADC value from a sensor
    reading = ADC0_Read();

    // Check if Switch 1 is pressed and handle its toggling state
    if ((!BUTTON_charRead(0, SWITCH1_PIN) && flag1)) {
        flag1 = 0;          // Reset the flag to avoid multiple toggles on one press
        state1 = !state1;   // Toggle state1
    }

    // Check if Switch 2 is pressed and handle its toggling state
    if ((!BUTTON_charRead(2, SWITCH2_PIN) && flag2)) {
        flag2 = 0;          // Reset the flag to avoid multiple toggles on one press
        state2 = !state2;   // Toggle state2
    }
		
		if( BUTTON_charRead(0, SWITCH1_PIN))
			   flag1 = 1;              // Reset the flag after the button is released

	  if (BUTTON_charRead(2, SWITCH2_PIN)) {
	    flag2 = 1;              // Reset the flag after the button is released
		}
		
		
		

    // Decide what to display based on the states of state1 and state2
    if (state1 == 1 && state2 == 1) {
        // If both states are active, display the ADC value on both LCD and LEDs
        displayOnLCD(reading);
        displayOnLED(reading);

    } else if (state1 == 0 && state2 == 0) {
        // If both states are inactive, clear the LCD and turn off all LEDs
        LCD_vCLR();
        TurnOffLEDS();
    } else if (state1 == 1) {
        // If only state1 is active, display the ADC value on the LCD and turn off LEDs
        displayOnLCD(reading);
        TurnOffLEDS();
			       

    } else if (state2 == 1) {
        // If only state2 is active, display the ADC value on the LEDs and clear the LCD
        displayOnLED(reading);
        LCD_vCLR();
    }

    // Add a small delay to control the speed of the loop and avoid excessive CPU usage
       Timer2_Delay(200);
}

}
