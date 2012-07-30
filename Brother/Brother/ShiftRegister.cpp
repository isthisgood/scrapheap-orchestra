#include "ShiftRegister.h"
#include <Arduino.h>
#include "constants.h"


unsigned char shiftByte1 = 0;
unsigned char shiftByte2 = 0;

void setupShiftRegister() {
  //Set SPI pins to output
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LE,OUTPUT);
	pinMode(LEDEN, OUTPUT);
	digitalWrite(LEDEN, LOW);
	
  digitalWrite(LE,HIGH);
  delay(30);
  
  // resets the shift register.
  shiftPin(0, 0);
}

void disableShifter() {
	digitalWrite(LEDEN, HIGH);
}

void shiftPin(int pos, int value) {
digitalWrite(CLK, LOW);
	
	
  digitalWrite(LEDEN, HIGH);
  if(pos<8) {
		bitWrite(shiftByte1, pos, value);
  } else {
	  bitWrite(shiftByte2, (pos-8), value);
  }

	digitalWrite(LE,LOW);
	shiftOut(SDI,CLK,MSBFIRST,shiftByte2);    //High byte first
	shiftOut(SDI,CLK,MSBFIRST,shiftByte1);           //Low byte second
	digitalWrite(LE,HIGH);
	digitalWrite(LEDEN, LOW);
}
