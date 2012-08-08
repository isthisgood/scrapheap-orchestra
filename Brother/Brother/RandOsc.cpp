 
#include "RandOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"

//#define _RAND1

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

void scaleRandVal(RandOsc* o)
{
    o->scaledRandValue = 2.f * o->uPeriod * o->randValue / 127.f;
}

void playRandOsc(RandOsc *o, int note, int vel)
{
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;	
    o->halfPeriod = u/2;
    
    scaleRandVal(o);
}

void stopRandOsc(RandOsc *o) {
  o->uPeriod = 0;
  o->halfPeriod = 0;
  digitalWrite(o->pin, 0);
  o->out = 0;
}

void ccRandOsc(RandOsc *o, int num, int val)
{
    if (num == 22)
    {
#ifdef _RAND1
        o->randValue = val;
#else
        o->randValue = val;
        scaleRandVal(o);
#endif
    }
}


void tickRandOsc(RandOsc *o)
{
    if(o->uPeriod>0)
    {
        unsigned long pos = us % o->uPeriod;
        //pos += random(o->randValue);
        if(pos > o->halfPeriod + random(-o->scaledRandValue, o->scaledRandValue) != !o->out)
        {
            o->out ^= 1;
#ifdef _RAND1     
            if (random(127) > o->randValue) digitalWrite(o->pin, o->out);
#else
            digitalWrite(o->pin, o->out);
#endif
    }
  }
}

