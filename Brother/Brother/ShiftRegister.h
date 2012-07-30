//These are the pins that will talk to the shift register through SPI
#define SDI    2    //Data
#define CLK    3    //Clock
#define LE     4    //Latch


void setupShiftRegister();
void shiftPin(int pin, int val);
