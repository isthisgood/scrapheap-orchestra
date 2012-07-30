
#include "VelOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"





void addVelOsc(MidiMap midi, int pin) {
  VelOsc *osc = new VelOsc;
  initVelOsc(osc, pin);
  addObject(midi, osc, (tickFn)tickVelOsc, (noteOnFn) playVelOsc, (noteOffFn)stopVelOsc, NULL);
}



/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line





void initVelOsc(VelOsc *o, int pin) {
  pinMode(pin, OUTPUT);
  o->pin = pin;
  o->uPeriod = 0;
  o->halfPeriod = 0;
  o->out = 0;
}


void applyVel(VelOsc *o) {
  float hp = o->uPeriod/2;
  float p = (float)o->pwmValue/127.f;
  hp *= 1.f - p;
  o->halfPeriod = hp;
}


void playVelOsc(VelOsc *o, int note, int vel) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o->uPeriod = u;
  o->pwmValue = 127-vel;
  applyVel(o);
  
}

void stopVelOsc(VelOsc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pin, 0);
  o->out = 0;
}



void tickVelOsc(VelOsc *o) {
  if(o->uPeriod>0) {
    unsigned long pos = us % o->uPeriod;
    if(pos>o->halfPeriod != !o->out) {
      o->out ^= 1;
      digitalWrite(o->pin, o->out);
    }
  }
}

