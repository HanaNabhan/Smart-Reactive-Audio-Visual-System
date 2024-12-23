#include "tm4c123gh6pm_11.h"
#include "ADC.h"
volatile unsigned int ADCvalue; // Digital representation of voltage on PE3

void ADC0_Init_Ch0(void)
{
 
   
  
    SYSCTL_RCGCGPIO_R |= (1 << 4);    // Enable Clock to GPIOE or PE3/AN0
    SYSCTL_RCGCADC_R |= (1 << 0);     // ADC0 clock enable

    // Initialize PE3 for AIN0 input
    GPIO_PORTE_AFSEL_R |= (1 << 3);   // Enable alternate function
    GPIO_PORTE_DEN_R &= ~(1 << 3);    // Disable digital function
    GPIO_PORTE_AMSEL_R |= (1 << 3);   // Enable analog function

    // Initialize sample sequencer 3
    ADC0_ACTSS_R &= ~(1 << 3);        // Disable SS3 during configuration
    ADC0_EMUX_R &= ~0xF000;           // Software trigger conversion
    ADC0_SSMUX3_R = 0;                // Input from channel 0
    ADC0_SSCTL3_R |= (1 << 1) | (1 << 2); // One sample, set flag at first sample

    // Enable ADC interrupt
    ADC0_IM_R |= (1 << 3);            // Unmask ADC0 sequence 3 interrupt
    NVIC_EN0_R |= 0x00020000;         // Enable IRQ17 for ADC0SS3
    ADC0_ACTSS_R |= (1 << 3);         // Enable ADC0 sequencer 3
    ADC0_PSSI_R |= (1 << 3);          // Start sampling data from AN0
}

void ADC0Seq3_Handler(void)
{
     ADCvalue = ADC0_SSFIFO3_R;    // Read ADC conversion result from SS3 FIFO
    
    ADC0_ISC_R |= 0x08;               // Clear conversion complete flag
    ADC0_PSSI_R |= 0x08;              // Start next sampling data from AN0
}


unsigned int ADC0_Read(void){
	return ADCvalue;
}