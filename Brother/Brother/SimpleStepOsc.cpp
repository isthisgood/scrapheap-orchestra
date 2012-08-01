
#include "SimpleStepOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addSimpleStepOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int reversePin)
{
  SimpleStepOsc *o = new SimpleStepOsc();
  initSimpleStepOsc(o, dirPin, stepPin, enableShiftPin, reversePin);
  addObject(midi, o, (tickFn)tickSimpleStepOsc, (noteOnFn)playSimpleStepOsc, (noteOffFn)stopSimpleStepOsc, NULL);
}

void initSimpleStepOsc(SimpleStepOsc *o, int dirPin, int stepPin, int enableShiftPin, int reversePin)
{
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(reversePin, INPUT);
      
    o->dirPin = dirPin;
    o->stepPin = stepPin;
    o->reversePin = reversePin;
    o->enableShiftPin = enableShiftPin;
      
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->dir = 0;
    o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
    
    digitalWrite(stepPin, o->out);
    digitalWrite(dirPin, o->dir);
}

void playSimpleStepOsc(SimpleStepOsc *o, int note, int vel)
{   
    shiftPin(o->enableShiftPin, 1);
    
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
    o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
}

void stopSimpleStepOsc(SimpleStepOsc *o)
{
    shiftPin(o->enableShiftPin, 0);
    
    o->uPeriod = 0; 
    o->halfPeriod = 0;
    o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
}

void checkLimits(SimpleStepOsc *o);

void tickSimpleStepOsc(SimpleStepOsc *o)
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
        
        unsigned long checkPos = us % LIMIT_CHECK;
        if (checkPos > HALF_LIMIT_CHECK != !o->checked)
        {
            o->checked ^= 1;
            if (o->checked) checkLimits(o);
        }
    }
}

void checkLimits(SimpleStepOsc *o)
{
    if (us > o->disabledTime && digitalRead(o->reversePin) == LOW)
    {
        o->dir ^= 1;
        o->disabledTime = us + DISABLED_PERIOD;
        digitalWrite(o->dirPin, o->dir);
    }
}