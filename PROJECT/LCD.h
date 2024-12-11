#ifndef LCD_H
#define LCD_H

// Function Prototypes
void LCD_init(void);
void LCD_command(unsigned char cmd);
void LCD_data(char data);
void LCD_writeString(char* str);
void delayMs(int delay);

#endif // LCD_H
