
#include "../tm4c123gh6pm.h"
#include "GPIO.h"
#include "TExaS.h"
#include "timer.h"

int Timer2_Ticks=0;
   unsigned long volatile delay;
void Timer2_Init(unsigned long period) { 
		GPIO_EnableClock(3);

	GPIO_MODE_SELECT(3,2,Alternate_Function_MODE);//D2
	GPIO_MODE_SELECT(3,3,Alternate_Function_MODE);//D3
	 
	 GPIO_PORTS[3]->PCTL=(GPIO_PORTS[3]->PCTL&0xFFFFFF00)+0x00000011;
 
    SYSCTL_RCGCTIMER_R |= 0x04;   // Activate timer2
    delay = SYSCTL_RCGCTIMER_R;
    
    TIMER2_CTL_R = 0x00000000;    // Disable timer2A during setup
    TIMER2_CFG_R = 0x00000000;    // Configure for 32-bit mode
    TIMER2_TAMR_R = 0x00000002;   // Configure for periodic mode
    TIMER2_TAILR_R = period - 1;  // Reload value
    TIMER2_TAPR_R = 0;            // Bus clock resolution
    TIMER2_ICR_R = 0x00000001;    // Clear timer2A timeout flag
    TIMER2_IMR_R = 0x00000001;    // Arm timeout interrupt
    NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; // Set priority
    NVIC_EN0_R = 1 << 23;         // Enable IRQ 23 in NVIC
    TIMER2_CTL_R = 0x00000001;    // Enable timer2A

}
// Timer2A interrupt handler

// Timer2A interrupt handler
void Timer2A_Handler(void) { 
  TIMER2_ICR_R = 0x00000001;   // Acknowledge timer2A timeout

 Timer2_Ticks++;

}



// Timer2A interrupt handler



// Delay function using Timer2
void Timer2_Delay(unsigned long milliseconds) {
    unsigned long targetTicks = milliseconds;  // Each tick = 1ms if period is set accordingly
    Timer2_Ticks = 0;                          // Reset the global tick counter

    while (Timer2_Ticks < targetTicks) {
        // Wait for the required number of ticks
    }
}