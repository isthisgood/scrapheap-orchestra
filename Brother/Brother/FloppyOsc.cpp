#include "FloppyOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"

void addFloppyOsc(MidiMap midi, int dirPin, int stepPin)
{
    FloppyOsc *osc = new FloppyOsc;
    initFloppyOsc(osc, dirPin, stepPin);
    addObject(midi, osc, (tickFn)tickFloppyOsc, (noteOnFn) playFloppyOsc, (noteOffFn)stopFloppyOsc, NULL);
}

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

void initFloppyOsc(FloppyOsc *o, int dirPin, int stepPin)
{
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    
    o->dirPin = dirPin;
    o->stepPin = stepPin;
    o->steps = 0;
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->out = 0;
    o->dir = 0;
    
    digitalWrite(dirPin, o->dir);
    digitalWrite(stepPin, o->out);
}

void playFloppyOsc(FloppyOsc *o, int note, int vel)
{
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
}

void stopFloppyFloppyOsc(FloppyOsc *o)
{
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->out = 0;
}

void tickFloppyOsc(FloppyOsc *o)
{
    if(o->uPeriod>0)
    {
        unsigned long pos = us % o->uPeriod;
        if(pos>o->halfPeriod != !o->out)
        {
            o->out ^= 1;
            digitalWrite(o->stepPin, o->out);
            o->steps++;
            unsigned long steps = o->steps % 314;
            if ((steps > 157) != o->dir)
            {
                o->dir = steps > 157;
                digitalWrite(o->dirPin, o->dir);
            }
        }
    }
}

