#include "GPIO.h"
#include "TM4C123GH6PM.h"
#include "TExaS.h"
#include "switch.h"
#include "LED.h"

// Global Variables
void Delay(void);
void EnableInterrupts(void);

// Function to initialize Port F
void PortF_Init(void) {
    GPIO_EnableClock(5);  // Enable clock to Port F
    GPIO_Init(5, 4, INPUT, DIGITAL);  // Initialize PF4 as input (SW1)
    GPIO_EnablePullUp(5, 4);  // Enable pull-up resistor on PF4 (SW1)

    // Initialize PF1, PF2, PF3 as outputs (LEDs)
    GPIO_Init(5, 1, OUTPUT, DIGITAL);  // Initialize PF1 (Red LED)
    GPIO_Init(5, 2, OUTPUT, DIGITAL);  // Initialize PF2 (Blue LED)
    GPIO_Init(5, 3, OUTPUT, DIGITAL);  // Initialize PF3 (Green LED)
}

// MAIN
int main(void) {
    char In;
    PortF_Init();  // Initialize Port F
    TExaS_Init(SW_PIN_PF40, LED_PIN_PF321);  // Initialize the TExaS grader for lab 2
    EnableInterrupts();  // The grader uses interrupts
    
    // Initialize LEDs and switch
    BUTTON_voidINIT(5, 4);
    LED_voidINIT(5, 1);
    LED_voidINIT(5, 2);
    LED_voidINIT(5, 3);

    while (1) {
        In = BUTTON_charRead(5, 4);  // Read PF4 (SW1) into In using the driver function
        if (In == 0) {  // Zero means SW1 is pressed
            LED_voidON(5, 3); // Set PF3 (green LED)
            LED_voidOFF(5, 1); // Clear PF1 (red LED)
            LED_voidOFF(5, 2); // Clear PF2 (blue LED)
        } else {  // 0x10 means SW1 is not pressed
            LED_voidON(5, 1); // Set PF1 (red LED)
            LED_voidOFF(5, 3); // Clear PF3 (green LED)
            LED_voidOFF(5, 2); // Clear PF2 (blue LED)
        }
        Delay();  // Wait 0.1 sec
        LED_voidON(5, 2);  // Set PF2 (blue LED)
        LED_voidOFF(5, 1);  // Clear PF1 (red LED)
        LED_voidOFF(5, 3);  // Clear PF3 (green LED)
        Delay();  // Wait 0.1 sec
    }
}

// Subroutine to wait 0.1 sec
void Delay(void) {
    unsigned long volatile time;
    time = 727240 * 200 / 91;  // 0.1 sec
    while (time) {
        time--;
    }
}
