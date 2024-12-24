#include "GPIO.h"

// Enables the clock for the specified GPIO port
void GPIO_EnableClock(char port) {
    volatile int delay = 0; // A delay to allow the clock to stabilize
    SYSCTL->RCGC2 |= (1 << port); // Enable clock for the specified port
    for (delay = 0; delay < 500000; delay++); // Wait for the clock to stabilize
}

// Initializes a GPIO pin with the specified configuration
void GPIO_Init(char port, char pin, char dir, char mode) {
    GPIO_EnableClock(port); // Ensure the port clock is enabled

    // Set the direction of the pin: INPUT or OUTPUT
    if (dir == INPUT) {
        GPIO_PORTS[port]->DIR &= ~(1 << pin); // Set pin as input
    } else {
        GPIO_PORTS[port]->DIR |= (1 << pin);  // Set pin as output
    }

    // Set the mode of the pin: DIGITAL or ANALOG
    if (mode == DIGITAL) { 
        GPIO_PORTS[port]->AMSEL &= ~(1 << pin); // Disable analog functionality
        GPIO_PORTS[port]->DEN |= (1 << pin);    // Enable digital functionality
    } else {         
        GPIO_PORTS[port]->DEN &= ~(1 << pin);   // Disable digital functionality
        GPIO_PORTS[port]->AMSEL |= (1 << pin); // Enable analog functionality
    }
}

// Changes the direction of a GPIO pin dynamically
void GPIO_SetDirection(char port, char pin, char dir) {
    if (dir == INPUT) {
        GPIO_PORTS[port]->DIR &= ~(1 << pin); // Set pin as input
    } else {
        GPIO_PORTS[port]->DIR |= (1 << pin);  // Set pin as output
    }
}

// Configures a GPIO pin for digital or analog functionality dynamically
void GPIO_analog_digital(char port, char pin, char digt_ana) {
    if (digt_ana == DIGITAL) { 
        GPIO_PORTS[port]->AMSEL &= ~(1 << pin); // Disable analog functionality
        GPIO_PORTS[port]->DEN |= (1 << pin);    // Enable digital functionality
    } else {         
        GPIO_PORTS[port]->DEN &= ~(1 << pin);   // Disable digital functionality
        GPIO_PORTS[port]->AMSEL |= (1 << pin); // Enable analog functionality
    }
}

// Reads the current state of a GPIO pin (HIGH or LOW)
int GPIO_ReadPin(char port, char pin) {
    return (GPIO_PORTS[port]->DATA & (1 << pin)) ? 1 : 0; // Return 1 if HIGH, 0 if LOW
}

// Writes a value to a GPIO pin (HIGH or LOW)
void GPIO_WritePin(char port, char pin, int value) {
    if (value) {
        GPIO_PORTS[port]->DATA |= (1 << pin);  // Set the pin HIGH
    } else {
        GPIO_PORTS[port]->DATA &= ~(1 << pin); // Set the pin LOW
    }
}

// Enables the pull-up resistor for a GPIO pin
void GPIO_EnablePullUp(char port, char pin) {
    GPIO_PORTS[port]->PUR |= (1 << pin); // Activate the pull-up resistor for the pin
}

// Selects the mode for a GPIO pin (e.g., alternate function)
void GPIO_MODE_SELECT(char port, char pin, char mode) {
    GPIO_PORTS[port]->AFSEL |= (mode << pin); // Enable the specified alternate function
}
