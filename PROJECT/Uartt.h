#ifndef UART
#define UART
void UART_Init(void);
unsigned char UART_InChar(void);
void UART_OutChar(unsigned char data);
void UART_OutString(char *pt);
#endif