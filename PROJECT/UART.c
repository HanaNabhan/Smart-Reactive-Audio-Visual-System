#include "UART.h"
#include "GPIO.h"
#include "TM4C123GH6PM.h"

#define UART_NVIC_EN0    (*(volatile unsigned long *)0xE000E100)

void EnableUART0Clock() {
   int i=0;
    SYSCTL->RCGCUART |= (1 << 0); 
    
   /* while ((SYSCTL->PRUART & (1 << 0)) == 0) {
        
    }*/
	
	for(i=0;i<50000;i++){}
}


void UART_MODE(MODE mode){
	if(mode== Enable)
 UART0->CTL|=(1<<0);
	else UART0->CTL&=~(1<<0);
}

void UART0_FEFO_MODE(MODE mode){
	 if(mode== Enable)
 UART0->LCRH|=(1<<4);
	else UART0->LCRH&=~(1<<4);
}

void UART0_PARITY_MODE(MODE mode){
  if(mode== Enable)
 UART0->LCRH|=(1<<1);
	else UART0->LCRH&=~(1<<1);
}
void UART0_DATA_Length(Datalength l){
	
	UART0->LCRH=l ; 
	 
}

void UART0_STOP_BIT(STOP_BIT n){
 if(n== bits_2)
 UART0->LCRH|=(1<<3);
	else UART0->LCRH&=~(1<<3);
}

  void UART0_BUAD_RATE(int baud_rate,SPEED ClkDiv){
		int BRD;
		if(ClkDiv==low) UART0->CTL=(0<<5);
		else UART0->CTL=(1<<5);
	// BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
	//FBRD = int(1/12 * 64 + 0.5) = int(27.166)  64 resolution
   BRD=16000000 / (ClkDiv * baud_rate);  // no taxes inti
   UART0->IBRD = BRD;       // 
   UART0->FBRD = ((SYSCLK * 4 / (ClkDiv * baud_rate)) % 4); 
	}

	void UART0_FIFO_Level_Select(LEVEL l) {
    switch (l) {
        case FEFO_DIS: {
            UART0_FEFO_MODE(disable);
            break;
        }
        case RXlevel0: 
					  UART0->IFLS&=0x07;
            UART0->IFLS |= (0 << 3) | (0 << 4) | (0 << 5);
            break;
        case RXlevel1: 
					  UART0->IFLS&=0x07;
            UART0->IFLS |= (1 << 3) | (0 << 4) | (0 << 5);
            break;
        case RXlevel2: 
					 UART0->IFLS&=0x07;
            UART0->IFLS |= (0 << 3) | (1 << 4) | (0 << 5);  // default
            break;
        case RXlevel3: 
					 UART0->IFLS&=0x07;
            UART0->IFLS |= (1 << 3) | (1 << 4) | (0 << 5);
            break;
        case RXlevel4:
            UART0->IFLS&=0x07;					
            UART0->IFLS |= (0 << 3) | (0 << 4) | (1 << 5);
            break;
        case TXlevel0: 
					 UART0->IFLS&=0x38;
            UART0->IFLS |= (0 << 0) | (0 << 1) | (0 << 2);
            break;
        case TXlevel1: 
					 UART0->IFLS&=0x38;//3-5bit
            UART0->IFLS |= (1 << 0) | (0 << 1) | (0 << 2);
            break;
        case TXlevel2: 
					 UART0->IFLS&=0x37;
            UART0->IFLS |= (0 << 0) | (1 << 1) | (0 << 2);  // default
            break;
        case TXlevel3: 
					 UART0->IFLS&=0x38;
            UART0->IFLS |= (1 << 0) | (1 << 1) | (0 << 2);
            break;
        case TXlevel4: 
					 UART0->IFLS&=0x38;
            UART0->IFLS |= (0 << 0) | (0 << 1) | (1 << 2);
            break;
        case EOT: {
            UART0->CTL |= (1 << 4);
            break;
        }
    }
}

void UART0_Interrupt_Mask(RX_TX x){
	switch(x){
		case RX:UART0->IM|=(1<<4) ;break;
		case TX:UART0->IM|=(1<<5) ;break;
		default:UART0->IM|=(1<<4)|(1<<5) ;break;
	}	
}

void UART0_Interrupt_clear(RX_TX x){
    switch(x){
        case RX: UART0->ICR &= ~(1<<4); break;
        case TX: UART0->ICR &= ~(1<<5); break;
        default: {
            UART0->ICR &= ~(1<<4);
            UART0->ICR &= ~(1<<5);
            break;
        }
    }   
}

void UART0_Interrupt_acknowledge(RX_TX x){
	switch(x){
		case RX:UART0->ICR|=(1<<4) ;break;
		case TX:UART0->ICR|=(1<<5) ;break;
		default:UART0->ICR|=(1<<4)|(0<<5) ;break;
	}	
}

RX_TX UART0_Interrupt_Status(){
  if(UART0->RIS|(1<<4)) return RX;
	else if(UART0->RIS|(1<<5)) return TX;
  else return no;
 }

  void UART0_inti(int baud_rate,SPEED s ,Datalength l,STOP_BIT stop_bit,MODE p,MODE f){
	  EnableUART0Clock();
	 GPIO_Init(0 ,0, INPUT,DIGITAL);
	 GPIO_Init(0 ,1, OUTPUT, DIGITAL );
	 UART_MODE(disable);
	 GPIO_MODE_SELECT(2,0,Alternate_Function_MODE);
	 GPIO_MODE_SELECT(2,1,Alternate_Function_MODE);
	 GPIO_PORTS[0]->PCTL=(GPIO_PORTS[0]->PCTL&0xFFFFFF00)+0x00000011;
		UART0_DATA_Length(l);
		UART0_FEFO_MODE(f);
		UART0_PARITY_MODE(p);
		UART0_STOP_BIT(stop_bit);
		UART0_BUAD_RATE(baud_rate,s);
		UART_MODE(Enable);
 }
	

 void UART0_Interrupt_INTI(LEVEL l,RX_TX x){
	 EnableInterrupts();
   UART0_FIFO_Level_Select(l);
   UART0_Interrupt_Mask(x);
	 UART0_Interrupt_clear(x);
	 UART_NVIC_EN0|=(1<<UART0_IRQn);
 }

 unsigned char UART_InChar(void){
  while((UART0->FR&(1<<4))!= 0);
  return((unsigned char)(UART0->DR&0xFF));
}
void UART_OutChar(unsigned char data){
  while((UART0->FR&(1<<5)) != 0);
  UART0->DR = data;
}

void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}
