
#include "RandOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"





void addRandOsc(MidiMap midi, int pin) {
  RandOsc *osc = new RandOsc;
  initRandOsc(osc, pin);
  addObject(midi, osc, (tickFn)tickRandOsc, (noteOnFn) playRandOsc, (noteOffFn)stopRandOsc, (ccFn)ccRandOsc);
}



/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line





void initRandOsc(RandOsc *o, int pin) {
  pinMode(pin, OUTPUT);
  o->pin = pin;
  o->uPeriod = 0;
  o->halfPeriod = 0;
  o->randValue = 0;
  o->out = 0;
}


void playRandOsc(RandOsc *o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o->uPeriod = u;
  
  o->halfPeriod = u/2;
}

void stopRandOsc(RandOsc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pin, 0);
  o->out = 0;
}


void ccRandOsc(RandOsc *o, int num, int val) {
  float r = val;
  val *= o->uPeriod;
 
  val /= 127.f;
  val -= o->uPeriod/2;
  o->randValue = val;
 
}


void tickRandOsc(RandOsc *o) {
  if(o->uPeriod>0) {
    unsigned long pos = us % o->uPeriod;
    pos += random(o->randValue);
    if(pos>o->halfPeriod != !o->out) {
      o->out ^= 1;
     
      digitalWrite(o->pin, o->out);
      //applyRandPeriod(o);
    }
  }
}

