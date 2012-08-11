/**
 *  DirMotorOsc.cpp
 *
 *  Created by Marek Bereza on 10/08/2012.
 */

#include "DirMotorOsc.h"

#include "Arduino.h"
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addDirMotorOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int limitPin, int relayPin)
{
	DirMotorOsc *o = new DirMotorOsc();
	initDirMotorOsc(o, dirPin, stepPin, enableShiftPin, limitPin, relayPin);
	addObject(midi, o, (tickFn)tickDirMotorOsc, (noteOnFn)playDirMotorOsc, (noteOffFn)stopDirMotorOsc, NULL);
}

void initDirMotorOsc(DirMotorOsc *o, int dirPin, int stepPin, int enableShiftPin, int limitPin, int relayPin)
{
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(limitPin, INPUT);
	pinMode(relayPin, OUTPUT);
	
    o->dirPin = dirPin;
    o->stepPin = stepPin;
    o->limitPin = limitPin;
    o->enableShiftPin = enableShiftPin;
	o->relayPin = relayPin;
	
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->dir = 0;
    o->out = 0;
    o->relayDir = 0;
	
    o->checked = 0;
    o->disabledTime = 0;
    
    digitalWrite(stepPin, o->out);
    digitalWrite(dirPin, o->dir);
	digitalWrite(relayPin, o->relayDir);
}

void playDirMotorOsc(DirMotorOsc *o, int note, int vel)
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

void stopDirMotorOsc(DirMotorOsc *o)
{
    shiftPin(o->enableShiftPin, 0);
    
    o->uPeriod = 0; 
    o->halfPeriod = 0;
    //o->out = 0;
    
    o->checked = 0;
    o->disabledTime = 0;
}

void check__Limits(DirMotorOsc *o);

void tickDirMotorOsc(DirMotorOsc *o)
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
        
        unsigned long checkPos = us % LIMIT_CHECK;
        if (checkPos > HALF_LIMIT_CHECK != !o->checked)
        {
            o->checked ^= 1;
            if (o->checked) check__Limits(o);
        }
    }
}

void check__Limits(DirMotorOsc *o)
{
    if (us > o->disabledTime && digitalRead(o->limitPin) == LOW)
    {
     //   o->out ^= 1;
	//	o->dir ^= 1;
		o->relayDir ^= 1;
        o->disabledTime = us + DISABLED_PERIOD;
		digitalWrite(o->relayPin, o->relayDir);
    }
}