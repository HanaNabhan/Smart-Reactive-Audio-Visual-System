#include "tm4c123gh6pm_11.h"  // Register definitions for TM4C123GH6PM microcontroller
#include "GPIO.h"             // GPIO configurations and helper functions
#include "TExaS.h"            // Debugging and testing library
#include "timer.h"            // Timer-specific definitions and declarations

// Global Variables
int Timer2_Ticks = 0;          // Counter to track the number of timer ticks
unsigned long volatile delay;  // Variable for introducing delays, volatile prevents optimization

// Function to initialize Timer2 for periodic interrupts
void Timer2_Init(unsigned long period) {
    GPIO_EnableClock(3);  // Enable the clock for GPIO Port D (index 3)

    // Configure pins D2 and D3 as alternate function (used for timer functionality)
    GPIO_MODE_SELECT(3, 2, Alternate_Function_MODE); // Set D2 to alternate function mode
    GPIO_MODE_SELECT(3, 3, Alternate_Function_MODE); // Set D3 to alternate function mode

    // Configure the Port Control Register (PCTL) to set the alternate function for pins D2 and D3
    GPIO_PORTS[3]->PCTL = (GPIO_PORTS[3]->PCTL & 0xFFFFFF00) + 0x00000011;

    SYSCTL_RCGCTIMER_R |= 0x04;   // Activate Timer2 by enabling its clock
    delay = SYSCTL_RCGCTIMER_R;  // Short delay to ensure the clock is stable

    TIMER2_CTL_R = 0x00000000;    // Disable Timer2 during configuration
    TIMER2_CFG_R = 0x00000000;    // Configure Timer2 for 32-bit mode
    TIMER2_TAMR_R = 0x00000002;   // Set Timer2 to periodic mode
    TIMER2_TAILR_R = period - 1;  // Set the reload value for the timer (determines the interval)
    TIMER2_TAPR_R = 0;            // Set the timer's clock resolution (no prescaling)
    TIMER2_ICR_R = 0x00000001;    // Clear the Timer2 timeout flag
    TIMER2_IMR_R = 0x00000001;    // Enable timeout interrupt for Timer2
    NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; // Set interrupt priority (highest bits)
    NVIC_EN0_R = 1 << 23;         // Enable Timer2 interrupt in the NVIC (IRQ 23)
    TIMER2_CTL_R = 0x00000001;    // Enable Timer2 after configuration
}

// Timer2 interrupt handler
void Timer2A_Handler(void) {
    TIMER2_ICR_R = 0x00000001;   // Clear the Timer2 timeout interrupt flag
    Timer2_Ticks++;              // Increment the global tick counter
}

// Delay function using Timer2
void Timer2_Delay(unsigned long milliseconds) {
    unsigned long targetTicks = milliseconds;  // Calculate the target ticks (1 ms per tick)
    Timer2_Ticks = 0;                          // Reset the global tick counter

    while (Timer2_Ticks < targetTicks) {
        // Wait until the required number of ticks has elapsed
    }
}
