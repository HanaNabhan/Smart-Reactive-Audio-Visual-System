#ifndef LCD_H
#define LCD_H

// Function Prototypes
void delayUs(int);   														   //Delay in Micro Seconds
void delayMs(int);   														   //Delay in Milli Seconds
void LCD4bits_Init(void);													 //Initialization of LCD Dispaly
void LCD_Write4bits(unsigned char, unsigned char); //Write data as (4 bits) on LCD
void LCD_WriteString(char*);											 //Write a string on LCD 
void LCD4bits_Cmd(unsigned char);									 //Write command 
void LCD4bits_Data(unsigned char);								 //Write a character
void LCD_vCLR(void);
void LCD_vDisplayAtPosition(char row, char column, char *str);
void LCD_vMoveCursor(char row, char column);
#endif // LCD_H
