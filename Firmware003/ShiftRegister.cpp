#include "ShiftRegister.h"
#include <Arduino.h>


unsigned char shiftByte1 = 0;
unsigned char shiftByte2 = 0;

void setupShiftRegister() {
  //Set SPI pins to output
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LE,OUTPUT);
  digitalWrite(LE,HIGH);
  delay(30);
  
  // resets the shift register.
  shiftPin(0, 0);
}



void shiftPin(int pos, int value) {
  if(pos<8) {
      bitWrite(shiftByte1, pos, value);
  } else {
    bitWrite(shiftByte2, pos-8, value);
  }
  digitalWrite(LE,LOW);
  shiftOut(SDI,CLK,MSBFIRST,shiftByte2);    //High byte first
  shiftOut(SDI,CLK,MSBFIRST,shiftByte1);           //Low byte second
  digitalWrite(LE,HIGH);
}
