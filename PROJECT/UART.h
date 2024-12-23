
#include "UART_cfg.h"
void UART_MODE(MODE); //enable & diable UART
void UART0_inti(int baud_rate,SPEED s,Datalength l,STOP_BIT stop_bit,MODE,MODE);
void EnableUART0Clock(void);
void UART0_Interrupt_INTI(LEVEL,RX_TX);
void UART0_DATA_Length(Datalength);
void _UART0_PARITY(int);
void UART0_FEFO_MODE(MODE);
void UART0_PARITY_MODE(MODE);
void UART0_STOP_BIT(STOP_BIT);
void UART0_BUAD_RATE(int,SPEED);
void UART0_FIFO_Level_Select(LEVEL);
void UART0_Interrupt_Mask(RX_TX);
RX_TX UART0_Interrupt_Status(void);
void UART0_Interrupt_clear(RX_TX);
void UART0_Interrupt_acknowledge(RX_TX);
unsigned char UART_InChar(void);
unsigned char UART_InChar(void);
void UART_OutString(char *pt);
void EnableInterrupts(void);
void UART0_Handler(void);
