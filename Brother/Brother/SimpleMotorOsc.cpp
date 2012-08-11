
#include "SimpleMotorOsc.h"
#include "Arduino.h"
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addSimpleMotorOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin)
{
	SimpleMotorOsc *o = new SimpleMotorOsc();
	initSimpleMotorOsc(o, dirPin, stepPin, enableShiftPin);
	addObject(midi, o, (tickFn)tickSimpleMotorOsc, (noteOnFn)playSimpleMotorOsc, (noteOffFn)stopSimpleMotorOsc, NULL);
}

void initSimpleMotorOsc(SimpleMotorOsc *o, int dirPin, int stepPin, int enableShiftPin)
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
    
    o->checked = 0;
    o->disabledTime = 0;
    
    digitalWrite(stepPin, o->out);
    digitalWrite(dirPin, o->dir);
}

void playSimpleMotorOsc(SimpleMotorOsc *o, int note, int vel)
{   
    shiftPin(o->enableShiftPin, 1);
    
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
   // o->out = 0;
   // o->dir = 0;
	//digitalWrite(o->stepPin, o->out);
	digitalWrite(o->dirPin, o->dir);
    o->disabledTime = 0;
}

void stopSimpleMotorOsc(SimpleMotorOsc *o)
{
    shiftPin(o->enableShiftPin, 0);
    
    o->uPeriod = 0; 
    o->halfPeriod = 0;
 // o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
}


void tickSimpleMotorOsc(SimpleMotorOsc *o)
{
    if(o->uPeriod>0)
    {
        unsigned long pos = us % o->uPeriod;
        if(pos > o->halfPeriod != !o->out)
        {
            // tick
            o->out ^= 1;


			digitalWrite(o->stepPin, o->out);
			//delay(1);
			if(!o->out) {
				o->dir ^= 1;
				digitalWrite(o->dirPin, o->dir);
			}
			
        }
	}
}
