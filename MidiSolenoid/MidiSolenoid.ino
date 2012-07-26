#include "Osc.h"
#include <Stepper.h>

// oscillator stuff
Osc osc1 = {0, 0, 0, 0};
unsigned long us;

int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) ) * 5e-3;
  return freq;
}

void initOsc(Osc &o, int pin) {
  pinMode(pin, OUTPUT);
  o.pin = pin;
  o.uPeriod = 0;
  o.halfPeriod = 0;
  o.out = 0;
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
      //if (o.out == 1) myStepper.step(stepDir);
    }
  }
}

void setup() {
  initOsc(osc1, 2);
  
  startMidi();
}


void noteOn(int channel, int note, int vel) {
  if (channel == 3)
  {
    playOsc(osc1, note);
  }
}

void noteOff(int channel, int note) {
  if (channel == 3)
  {
    digitalWrite(2, LOW);
    stopOsc(osc1);
  }
}

void loop() {
  updateMidi();
  us = micros();
  tickOsc(osc1);
}
