#include "GPIO.h"
#include "LCD.h"
#include "LED.h"
#include "switch.h"
#include "timer.h"
#include "ADC.h"
#include <stdio.h>
#include <stdlib.h>
#include "TExaS.h"
#define TIMER2_ICR_R            (*((volatile unsigned long *)0x40032024))
#define SWITCH1_PIN 2 //   pf2(led)
#define SWITCH2_PIN 5 //(pf1) lcd
#define LED1_PIN 3//pa6
#define LED2_PIN 4 //pa3
#define LED3_PIN 5 //pa4
#define LED4_PIN 6//pa5

unsigned int state1 =0, state2=0;
char flag1 =1 , flag2 =1 ;
			unsigned int reading=0;


void turn_off(void);
int readAudio() {
   
    return ADC0_Read();
}







void displayOnLCD(unsigned int audio_value) {
    char buffer[16]; 
    sprintf(buffer, "Audio: %d", audio_value); 
LCD_vCLR();	
    LCD_WriteString(buffer);  
}


void displayOnLED(int audio_value) {
 
    
    if (audio_value < 155) {
        LED_voidON(0,LED1_PIN); 
        LED_voidOFF(0, LED2_PIN);
        LED_voidOFF(0, LED3_PIN);
         LED_voidOFF(0, LED4_PIN);			
    } else if (audio_value < 160) {
        LED_voidON(0,LED2_PIN);
        LED_voidON(0,LED1_PIN);  
         LED_voidOFF(0, LED3_PIN);
         LED_voidOFF(0, LED4_PIN);			
    } else if (audio_value < 4089) {
        LED_voidON(0,LED3_PIN); 
        LED_voidON(0,LED2_PIN);
        LED_voidON(0,LED1_PIN);
			  LED_voidOFF(0, LED4_PIN);
    } else {
        LED_voidON(0,LED4_PIN);
        LED_voidON(0,LED3_PIN); 
        LED_voidON(0,LED2_PIN);
        LED_voidON(0,LED1_PIN);
    }

}





















void turn_off(void)
{
	   LED_voidOFF(0,LED1_PIN); 
        LED_voidOFF(0, LED2_PIN);
        LED_voidOFF(0, LED3_PIN);
         LED_voidOFF(0, LED4_PIN);
}
 
void setup() {
   
   BUTTON_voidINIT(2,SWITCH1_PIN);//switch 1 port 5 pin 0
   BUTTON_voidINIT(2,SWITCH2_PIN);//switch 2 port 5 pin 1
    LED_voidINIT(0,LED1_PIN);
	  LED_voidINIT(0,LED2_PIN);
	  LED_voidINIT(0,LED3_PIN);
		LED_voidINIT(0,LED4_PIN);
	   ADC0_Init_Ch0();
	 // UART0_inti(9600, low, 8, 1, 0, 0);
	 
	 // LCD4bits_Init();
   // LCD_vCLR();
	//Timer2_Init(16000000*16);
	



	
 
  

	
  

	

	
    
}

int main() {
	TExaS_Init();
	LCD4bits_Init();
	LCD_vCLR();
   BUTTON_voidINIT(0,SWITCH1_PIN);//switch 1 port 5 pin 0
   BUTTON_voidINIT(2,SWITCH2_PIN);//switch 2 port 5 pin 1*/
    LED_voidINIT(0,LED1_PIN);
	  LED_voidINIT(0,LED2_PIN);
	  LED_voidINIT(0,LED3_PIN);
		LED_voidINIT(0,LED4_PIN);
	   ADC0_Init_Ch0();
	Timer2_Init(80000000);
   
	    LCD_WriteString("HELLO");  
				Timer2_Delay(1);

    while (1) {
			reading=ADC0_Read();
			if((!BUTTON_charRead(0,SWITCH1_PIN)&& flag1)){
				flag1=0;
				if(state1==1){
					state1=0;
				}
				else{
					state1=1;
				}
			}
			flag1=1;
			if((!BUTTON_charRead(2,SWITCH2_PIN))&& flag2){
				flag2=0;
				if(state2==1){
					state2=0;
				}
				else{
					state2=1;
				}
			}
			flag2=1;
			//////////////////////////////////
			if(state1 == 1 && state2 ==1){
				displayOnLCD(reading);
				displayOnLED(reading);
				
			}
			else if(state1 == 0 && state2 ==0){
				LCD_vCLR();
				turn_off();
			}
			
			else if(state1==1){
			displayOnLCD(reading);
				turn_off();
			}
			else if(state2==1){
				displayOnLED(reading);
							LCD_vCLR();

			}
			
			
			Timer2_Delay(1);
		

    }
}
