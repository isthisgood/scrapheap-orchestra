
#include "Osc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"





void addOsc(MidiMap midi, int pin) {
  Osc *osc = new Osc;
  initOsc(osc, pin);
  addObject(midi, osc, (tickFn)tickOsc, (noteOnFn) playOsc, (noteOffFn)stopOsc, (ccFn)ccOsc);
}



/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line




void initOsc(Osc *o, int pin) {
  pinMode(pin, OUTPUT);
  o->pin = pin;
  o->uPeriod = 0;
  o->halfPeriod = 0;
  o->out = 0;
}



void playOsc(Osc *o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o->uPeriod = u;
  o->halfPeriod = o->uPeriod/2;
  o->note = note;
}

void stopOsc(Osc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pin, 0);
  o->out = 0;
}

void ccOsc(Osc *o, int ctrlId, int val) {
    //if(ctrlId==-1) {
      float f = mtof(o->note);
      float power = val - 63;
      power /= 63;
      f *= pow(2, power);
      float u = 1000000.f/f;
      o->uPeriod = u;
      o->halfPeriod = o->uPeriod/2;
   //}
}


void tickOsc(Osc *o) {
  if(o->uPeriod>0) {
    unsigned long pos = us % o->uPeriod;
    if(pos>o->halfPeriod != !o->out) {
      o->out ^= 1;
      digitalWrite(o->pin, o->out);
    }
  }
}

