#include "Osc.h"
//unsigned long uPeriod = 0;






Osc osc1 = {0, 0, 0, 0};
Osc osc2 = {0, 0, 0, 0};
Osc osc3 = {0, 0, 0, 0};
Osc osc4 = {0, 0, 0, 0};
//Osc osc5 = {0, 0, 0, 0};
//Osc osc6 = {0, 0, 0, 0};



void setup() {
  initOsc(osc1, 8); 
  initOsc(osc2, 9); 
  initOsc(osc3, 10);
  initOsc(osc4, 11);
 // initOsc(osc5, 12);
 // initOsc(osc6, 13);
  
  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  
  
  startMidi();

}


void noteOn(int channel, int note, int vel) {
  if(channel==2) {
    playOsc(osc1, note);
  } else if(channel==1) {
    playOsc(osc2, note);
  } else if(channel==3) {
    playOsc(osc3, note);
  } else if(channel==4) {
    playOsc(osc4, note);
 // } else if(channel==5) {
  //  playOsc(osc5, note);
 // } else if(channel==6) {
  //  playOsc(osc6, note);
  }
}

void noteOff(int channel, int note) {
  if(channel==2) {
    stopOsc(osc1);
  } else if(channel==1) {
    stopOsc(osc2);
  } else if(channel==3) {
    stopOsc(osc3);
  } else if(channel==4) {
    stopOsc(osc4);
 // } else if(channel==5) {
  //  stopOsc(osc5);
  //} else if(channel==6) {
 //   stopOsc(osc6);
  }
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  oscClock();
  tickOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
  //tickOsc(osc5);
  //tickOsc(osc6);
}


void loop() {
  updateMidi();
  
  
}
