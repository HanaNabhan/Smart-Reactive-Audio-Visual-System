#include "../tm4c123gh6pm.h"
#include "interrupt.h"
#include "GPIO.h"
	int stateSwitch1 =0;
		int stateSwitch2=0;
void INTERRUPT_Init(void){
	
/*GPIO_PORTF_IS_R=0<<4 | 0<<0; //level or edge
GPIO_PORTF_IBE_R = 0<<4 | 0<<0; //Both or not
GPIO_PORTF_IEV_R =0<<4 | 0<<0;  //rising or falling 
GPIO_PORTF_ICR_R =0<<4|0<<0; //unaffected
GPIO_PORTF_IM_R =1<<4|1<<0; //non masked
NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
NVIC_PRI7_R =(NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
EnableInterrupts();*/
	GPIO_EnableClock(2); // (a) activate clock for port F

	//GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0 
	GPIO_PORTC_DIR_R &= ~((1 << 4) | (1 << 5));;    // (c) make PF4 in (built-in button)
	
  GPIO_PORTC_AFSEL_R = 0x00;
  GPIO_PORTC_DEN_R = ((1 << 4) | (1 << 5));          // 7) enable digital pins PF4-PF0        
        // 5) PF4,PF0 input, PF3,PF2,PF1 output   

  GPIO_PORTC_PCTL_R &= ~0x000000F0; // configure PF4 as 
	GPIO_PORTC_PCTL_R &= ~0x00000F00; // configure PF4 as GPIO

  GPIO_PORTC_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTC_PUR_R = (1 << 4) | (1 << 5);

  GPIO_PORTC_IS_R &= ~(1 << 4) | (1 << 5);     // (d) PF4 is edge-sensitive
	//GPIO_PORTF_IS_R &= ~0x00000100;     // (d) PF4 is edge-sensitive

  GPIO_PORTC_IBE_R &= ~(1 << 4) | (1 << 5);    //     PF4 is not both edges
  GPIO_PORTC_IEV_R &= ~(1 << 4) | (1 << 5);    //     PF4 falling edge event
	//GPIO_PORTF_IBE_R &= ~0x00000100;    //     PF4 is not both edges
 // GPIO_PORTF_IEV_R &= ~0x00000100;    //     PF4 falling edge event
  GPIO_PORTC_ICR_R = (1 << 4) | (1 << 5);      // (e) clear flag4
	//GPIO_PORTF_ICR_R = 0x00000100; 
  //GPIO_PORTF_IM_R |= 0x00000010;      // (f) arm interrupt on PF4
	GPIO_PORTC_IM_R |= (1 << 4) | (1 << 5);      // (f) arm interrupt on PF4

   NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFF1FFF) | 0x0000A000; // ?????? 5
    NVIC_EN0_R |= (1 << 2); // ????? ?????? Port C    // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPortF_Handler(void){

 
		
		
		
      if(GPIO_PORTC_RIS_R & (1<<2)){  
       GPIO_PORTC_ICR_R |= 0x02;      // acknowledge flag4
				// just SW1 pressed
				stateSwitch1^=stateSwitch1;
      } 
		else if(GPIO_PORTC_RIS_R & (1<<1)){
     GPIO_PORTC_ICR_R |= 0x01;      // acknowledge flag4
				// just SW2 pressed
         	stateSwitch2=!stateSwitch2;
        }
	
				
}
int readState1()
{return 	 stateSwitch1 ;
}
int readState2()
{return 	 stateSwitch2 ;
}
