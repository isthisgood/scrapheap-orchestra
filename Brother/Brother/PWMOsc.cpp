
#include "PWMOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"





void addPWMOsc(MidiMap midi, int pin) {
  PWMOsc *osc = new PWMOsc;
  initPWMOsc(osc, pin);
  addObject(midi, osc, (tickFn)tickPWMOsc, (noteOnFn) playPWMOsc, (noteOffFn)stopPWMOsc, (ccFn)ccPWMOsc);
}



/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line





void initPWMOsc(PWMOsc *o, int pin) {
  pinMode(pin, OUTPUT);
  o->pin = pin;
  o->uPeriod = 0;
  o->halfPeriod = 0;
  o->out = 0;
}


void applyPWM(PWMOsc *o) {
  float hp = o->uPeriod/2;
  float p = (float)o->pwmValue/127.f;
  hp *= 1.f - p;
  o->halfPeriod = hp;
}


void playPWMOsc(PWMOsc *o, int note, int vel) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o->uPeriod = u;
  applyPWM(o);
  
}

void stopPWMOsc(PWMOsc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pin, 0);
  o->out = 0;
}


void ccPWMOsc(PWMOsc *o, int num, int val) {
  o->pwmValue = val;
  applyPWM(o);
}


void tickPWMOsc(PWMOsc *o) {
  if(o->uPeriod>0) {
    unsigned long pos = us % o->uPeriod;
    if(pos>o->halfPeriod != !o->out) {
      o->out ^= 1;
      digitalWrite(o->pin, o->out);
    }
  }
}

