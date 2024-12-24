#include "TM4C123GH6PM.h"
#include "LCD.h"
#include "GPIO.h"
#include "timer.h"

#define LCD_PORT 1       // Port B index in GPIO_PORTS array
#define RS 0             // RS 
#define RW 1             // RW 
#define EN 2             // EN 

// LCD Commands
#define FOUR_BIT_COM 0x28
#define CLRCOM 0x01
#define DISPLAYON_CURSOROFF_COM 0x0C
#define MOVE_2RIGHT_COM 0x06
#define FIRST_ROW_COM 0x80
#define SECOND_ROW_COM 0xC0
#define RETURN_HOME 0X02


int pin ;
int k;
// Function to enable the LCD (generate enable pulse)
static void Enable(void) {
    GPIO_WritePin(LCD_PORT, EN, 1);
    delayUs(10); // Short delay to latch data
    GPIO_WritePin(LCD_PORT, EN, 0);
    delayUs(10);
}

// Initialize LCD in 4-bit mode
void LCD4bits_Init(void) {
    // Initialize control pins (RS, RW, EN)
    GPIO_Init(LCD_PORT, RS, OUTPUT, DIGITAL);
    GPIO_Init(LCD_PORT, RW, OUTPUT, DIGITAL);
    GPIO_Init(LCD_PORT, EN, OUTPUT, DIGITAL);
    // Initialize data pins (D4-D7)
    for (pin = 4; pin <= 7; pin++) {
        GPIO_Init(LCD_PORT, pin, OUTPUT, DIGITAL);
    }

    delayMs(20); // Wait for the LCD to power up
    LCD4bits_Cmd(RETURN_HOME);
    LCD4bits_Cmd(FOUR_BIT_COM); // 4-bit mode, 2-line display, 5x7 font
    LCD4bits_Cmd(DISPLAYON_CURSOROFF_COM); // Display on, cursor off
    LCD4bits_Cmd(CLRCOM); // Clear display
    LCD4bits_Cmd(MOVE_2RIGHT_COM); // Entry mode set: shift cursor to right
}

// Send command to LCD in 4-bit mode
void LCD4bits_Cmd(unsigned char command) {
    GPIO_WritePin(LCD_PORT, RS, 0); // Command mode
    GPIO_WritePin(LCD_PORT, RW, 0); // Write mode

    // Send higher nibble
    for ( k = 0; k < 4; k++) {
        GPIO_WritePin(LCD_PORT, 4 + k, (command >> (4 + k)) & 0x01);
    }
    Enable();

    // Send lower nibble
    for (k = 0; k < 4; k++) {
        GPIO_WritePin(LCD_PORT, 4 + k, (command >> k) & 0x01);
    }
    Enable();

   
        delayMs(2); // Long delay for clear/home commands
   
}

// Send data (character) to LCD in 4-bit mode
void LCD4bits_Data(int data) {
    GPIO_WritePin(LCD_PORT, RS, 1); // Data mode
    GPIO_WritePin(LCD_PORT, RW, 0); // Write mode

    // Send higher nibble
   // Higher nibble
for (k = 0; k < 4; k++) {
    GPIO_WritePin(LCD_PORT, 4 + k, (data >> (4 + k )) & 0x01);
}


    Enable();

    // Send lower nibble
    // Lower nibble
for (k = 0; k < 4; k++) {
    GPIO_WritePin(LCD_PORT, 4 + k, (data >> k) & 0x01);
}

    Enable();

    delayMs(20); // Short delay for data execution
}

// Clear LCD display
void LCD_vCLR(void) {
    LCD4bits_Cmd(CLRCOM);
    delayMs(10); // Delay for clear command
}

// Move cursor to specified position and display string


// Move cursor to specified row and column
void LCD_vMoveCursor(char row, char column) {
    unsigned char address;

    if((row>2)||(row<1)||(column<1)||(column>16)){
		address=FIRST_ROW_COM;
	}
	else if(row==1){
		address=FIRST_ROW_COM+column-1;
	}
	else if(row==2){
		address=SECOND_ROW_COM+column-1;
	}
	else{
		
	}

    LCD4bits_Cmd(address);
}

// Write string to LCD
void LCD_WriteString(char *str) {
		
    while (*str!=0) {
        LCD4bits_Data(*str);
			str++;
    }
}

void delayMs(int n) {
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++);
}

void delayUs(int n) {
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++);
}
