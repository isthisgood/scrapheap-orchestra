
#include "ControlStepOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addControlStepOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin)
{
	ControlStepOsc *o = new ControlStepOsc();
	initControlStepOsc(o, dirPin, stepPin, enableShiftPin);
	addObject(midi, o, (tickFn)tickControlStepOsc, (noteOnFn)playControlStepOsc, (noteOffFn)stopControlStepOsc, (ccFn)ccControlStepOsc);
}

void initControlStepOsc(ControlStepOsc *o, int dirPin, int stepPin, int enableShiftPin)
{
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    
    o->dirPin = dirPin;
    o->stepPin = stepPin;
    o->enableShiftPin = enableShiftPin;
	
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->dir = 0;
    o->out = 0;
    
    digitalWrite(stepPin, o->out);
    digitalWrite(dirPin, o->dir);
}

void ccControlStepOsc(ControlStepOsc *o, int num, int val)
{
    if (num == 23)
    {
        o->dir = ~o->dir;
        digitalWrite(o->dirPin, o->dir);
    }
}

void playControlStepOsc(ControlStepOsc *o, int note, int vel)
{   
    shiftPin(o->enableShiftPin, 1);
    
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
    o->out = 0;
}

void stopControlStepOsc(ControlStepOsc *o)
{
    shiftPin(o->enableShiftPin, 0);
    
    o->uPeriod = 0; 
    o->halfPeriod = 0;
    o->out = 0;
}

void tickControlStepOsc(ControlStepOsc *o)
{
    if(o->uPeriod>0)
    {
        unsigned long pos = us % o->uPeriod;
        if(pos > o->halfPeriod != !o->out)
        {
            // tick
            o->out ^= 1;
			
            // then step
            digitalWrite(o->stepPin, o->out);
        }
    }
}
