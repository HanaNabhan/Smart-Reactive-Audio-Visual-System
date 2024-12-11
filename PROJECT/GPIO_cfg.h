#define OUTPUT 1
#define INPUT 0
#define DIGITAL 1
#define ANALOG 0
#define PULLUP_EN 1
#define PULLDOWN_EN 0

// Base addresses for GPIO ports
#define GPIO_PORTA_BASE 0x40004000
#define GPIO_PORTB_BASE 0x40005000
#define GPIO_PORTC_BASE 0x40006000
#define GPIO_PORTD_BASE 0x40007000
#define GPIO_PORTE_BASE 0x40024000
#define GPIO_PORTF_BASE 0x40025000

// GPIO Register Offsets
#define GPIO_DIR_OFFSET    0x400
#define GPIO_DEN_OFFSET    0x51C
#define GPIO_DATA_OFFSET   0x3FC

void GPIO_Init(char port ,char pin ,char dir );
void GPIO_SetDirection(char port , char pin , char dir);
void GPIO_analog_digital(char port , char pin , char digt_ana);
