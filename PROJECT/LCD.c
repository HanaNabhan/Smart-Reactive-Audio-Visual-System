#include "TM4C123GH6PM.h"

#include "LCD.h"
#include "GPIO.h"

#define RS_PIN  2 // PA2
#define EN_PIN  3 // PA3
#define D4_PIN  4 // PA4
#define D5_PIN  5 // PA5
#define D6_PIN  6 // PA6
#define D7_PIN  7 // PA7

#define PORT_A  0

// Send a command to the LCD
void LCD_command(unsigned char cmd) {
    // Send upper nibble
    GPIO_WritePin(PORT_A, RS_PIN, 0);               // RS = 0 (command mode)
    GPIO_WritePin(PORT_A, D4_PIN, (cmd >> 4) & 0x1);
    GPIO_WritePin(PORT_A, D5_PIN, (cmd >> 5) & 0x1);
    GPIO_WritePin(PORT_A, D6_PIN, (cmd >> 6) & 0x1);
    GPIO_WritePin(PORT_A, D7_PIN, (cmd >> 7) & 0x1);
    GPIO_WritePin(PORT_A, EN_PIN, 1);               // Pulse EN
    delayMs(1);
    GPIO_WritePin(PORT_A, EN_PIN, 0);

    // Send lower nibble
    GPIO_WritePin(PORT_A, D4_PIN, cmd & 0x1);
    GPIO_WritePin(PORT_A, D5_PIN, (cmd >> 1) & 0x1);
    GPIO_WritePin(PORT_A, D6_PIN, (cmd >> 2) & 0x1);
    GPIO_WritePin(PORT_A, D7_PIN, (cmd >> 3) & 0x1);
    GPIO_WritePin(PORT_A, EN_PIN, 1);               // Pulse EN
    delayMs(1);
    GPIO_WritePin(PORT_A, EN_PIN, 0);

    delayMs(2); // Command execution time
}

// Send data to the LCD
void LCD_data(char data) {
    // Send upper nibble
    GPIO_WritePin(PORT_A, RS_PIN, 1);               // RS = 1 (data mode)
    GPIO_WritePin(PORT_A, D4_PIN, (data >> 4) & 0x1);
    GPIO_WritePin(PORT_A, D5_PIN, (data >> 5) & 0x1);
    GPIO_WritePin(PORT_A, D6_PIN, (data >> 6) & 0x1);
    GPIO_WritePin(PORT_A, D7_PIN, (data >> 7) & 0x1);
    GPIO_WritePin(PORT_A, EN_PIN, 1);               // Pulse EN
    delayMs(1);
    GPIO_WritePin(PORT_A, EN_PIN, 0);

    // Send lower nibble
    GPIO_WritePin(PORT_A, D4_PIN, data & 0x1);
    GPIO_WritePin(PORT_A, D5_PIN, (data >> 1) & 0x1);
    GPIO_WritePin(PORT_A, D6_PIN, (data >> 2) & 0x1);
    GPIO_WritePin(PORT_A, D7_PIN, (data >> 3) & 0x1);
    GPIO_WritePin(PORT_A, EN_PIN, 1);               // Pulse EN
    delayMs(1);
    GPIO_WritePin(PORT_A, EN_PIN, 0);

    delayMs(2); // Data write time
}

// Initialize the LCD
void LCD_init(void) {
    // Configure GPIO pins as outputs
    GPIO_Init(PORT_A, RS_PIN, OUTPUT, DIGITAL);
    GPIO_Init(PORT_A, EN_PIN, OUTPUT, DIGITAL);
    GPIO_Init(PORT_A, D4_PIN, OUTPUT, DIGITAL);
    GPIO_Init(PORT_A, D5_PIN, OUTPUT, DIGITAL);
    GPIO_Init(PORT_A, D6_PIN, OUTPUT, DIGITAL);
    GPIO_Init(PORT_A, D7_PIN, OUTPUT, DIGITAL);

    delayMs(20); // Wait for LCD to power up
    LCD_command(0x02);  // Initialize in 4-bit mode
    LCD_command(0x28);  // 4-bit mode, 2 lines, 5x7 font
    LCD_command(0x06);  // Auto-increment cursor
    LCD_command(0x0C);  // Display on, cursor off
    LCD_command(0x01);  // Clear display
    delayMs(2);
}

// Write a string to the LCD
void LCD_writeString(char* str) {
    while (*str) {
        LCD_data(*str++);
    }
}

// Simple delay in milliseconds
void delayMs(int delay) {
    volatile int i, j;
    for (i = 0; i < delay; i++) {
        for (j = 0; j < 3180; j++) {
            // Do nothing
        }
    }
}


