
#include "StepOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"



void addStepOsc(MidiMap midi, int pinA, int pinB, int pinC, int pinD) {
  StepOsc *o = new StepOsc();
  initStepOsc(o, pinA, pinB, pinC, pinD);
  addObject(midi, o, (tickFn)tickStepOsc, (noteOnFn)playStepOsc, (noteOffFn)stopStepOsc, NULL);
}





//int out = 0;
void initStepOsc(StepOsc *o, int pinA, int pinB, int pinC, int pinD) {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  
  o->pinA = pinA;
  o->pinB = pinB;
  o->pinC = pinC;
  o->pinD = pinD;
  
  o->uPeriod = 0;
  o->halfPeriod = 0;
  o->pos = 0;
  o->out = 0;
  
}





void playStepOsc(StepOsc *o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o->uPeriod = u;
  o->halfPeriod = o->uPeriod/2;
  o->out = 0;
}

void stopStepOsc(StepOsc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pinA, 0);
  digitalWrite(o->pinB, 0);
  digitalWrite(o->pinC, 0);
  digitalWrite(o->pinD, 0);
  
  o->pos = 0;
  o->out = 0;
}



void stepStepOsc(StepOsc *o);

void tickStepOsc(StepOsc *o) {
  if(o->uPeriod>0) {
    unsigned long pos = us % o->uPeriod;
    if(pos>o->halfPeriod != !o->out) {
      // tick
      o->out ^= 1;
      
      // increment step appropriately
      // to go forward just mod plus, and backwards mod minus
      o->pos++;
      o->pos %= 4;
      
      
      // then step
      stepStepOsc(o);
    }
  }
}


void stepStepOsc(StepOsc *o) {
  switch(o->pos) {
  
    case 0:    // 1010
      digitalWrite(o->pinA, HIGH);
      digitalWrite(o->pinB, LOW);
      digitalWrite(o->pinC, HIGH);
      digitalWrite(o->pinD, LOW);
      break;
    case 1:    // 0110
      digitalWrite(o->pinA, LOW);
      digitalWrite(o->pinB, HIGH);
      digitalWrite(o->pinC, HIGH);
      digitalWrite(o->pinD, LOW);
      break;
    case 2:    //0101
      digitalWrite(o->pinA, LOW);
      digitalWrite(o->pinB, HIGH);
      digitalWrite(o->pinC, LOW);
      digitalWrite(o->pinD, HIGH);
      break;
    case 3:    //1001
      digitalWrite(o->pinA, HIGH);
      digitalWrite(o->pinB, LOW);
      digitalWrite(o->pinC, LOW);
      digitalWrite(o->pinD, HIGH);
      break;
  }
}

