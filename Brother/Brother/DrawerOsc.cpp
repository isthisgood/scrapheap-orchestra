
#include "DrawerOsc.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addDrawerOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int reversePin)
{
  DrawerOsc *o = new DrawerOsc();
  initDrawerOsc(o, dirPin, stepPin, enableShiftPin, reversePin);
  addObject(midi, o, (tickFn)tickDrawerOsc, (noteOnFn)playDrawerOsc, (noteOffFn)stopDrawerOsc, NULL);
}

void initDrawerOsc(DrawerOsc *o, int dirPin, int stepPin, int enableShiftPin, int reversePin)
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
    
    o->analog = reversePin == ANA1 || reversePin == ANA2;
    
    digitalWrite(stepPin, o->out);
    digitalWrite(dirPin, o->dir);
}

void playDrawerOsc(DrawerOsc *o, int note, int vel)
{   
    shiftPin(o->enableShiftPin, 1);
    
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
    o->out = 0;
    o->dir = 1;
    digitalWrite(o->dirPin, o->dir);
    o->checked = 0;
    o->disabledTime = 0;
}

void stopDrawerOsc(DrawerOsc *o)
{
    shiftPin(o->enableShiftPin, 0);
    
    o->uPeriod = 0; 
    o->halfPeriod = 0;
    o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
}

void checkLimits(DrawerOsc *o);

void tickDrawerOsc(DrawerOsc *o)
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

void checkLimits(DrawerOsc *o)
{
    if (us > o->disabledTime && ((!o->analog && digitalRead(o->reversePin) == LOW) || (o->analog && analogRead(o->reversePin) == 0)))
    {
        o->dir ^= 1;
        o->disabledTime = us + DISABLED_PERIOD;
        digitalWrite(o->dirPin, o->dir);
    }
}