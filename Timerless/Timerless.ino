#include "Osc.h"
//unsigned long uPeriod = 0;

unsigned long us;




Osc osc1 = {0, 0, 0, 0};
Osc osc2 = {0, 0, 0, 0};
Osc osc3 = {0, 0, 0, 0};
Osc osc4 = {0, 0, 0, 0};




//int out = 0;
void initOsc(Osc &o, int pin) {
  pinMode(pin, OUTPUT);
  o.pin = pin;
  o.uPeriod = 0;
  o.halfPeriod = 0;
  o.out = 0;
}



int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}


void playOsc(Osc &o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o.uPeriod = u;
  o.halfPeriod = o.uPeriod/4;
}

void stopOsc(Osc &o) {
  o.uPeriod = 0;
  o.halfPeriod = 0;
}


void tickOsc(Osc &o) {
  if(o.uPeriod>0) {
    unsigned long pos = us % o.uPeriod;
    if(pos>o.halfPeriod != !o.out) {
      o.out ^= 1;
      digitalWrite(o.pin, o.out);
    }
  }
}

void setup() {
  initOsc(osc1, 12); 
  initOsc(osc2, 13); 
  initOsc(osc3, 9);
  initOsc(osc4, 10);
  
  // we need an earth pin here
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
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
  }
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/


void loop() {
  updateMidi();
  
  us = micros();
  tickOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
}
