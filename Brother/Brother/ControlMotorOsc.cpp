/**
 *  ControlMotorOsc.cpp
 *
 *  Created by Marek Bereza on 10/08/2012.
 */

#include "ControlMotorOsc.h"

#include "Arduino.h"
#include "OscUtils.h"
#include "Runner.h"
#include "ShiftRegister.h"
#include "constants.h"

void addControlMotorOsc(MidiMap midi, int motorOutPin, int relayDirPin)
{
	ControlMotorOsc *o = new ControlMotorOsc();
	initControlMotorOsc(o, motorOutPin, relayDirPin);
	addObject(midi, o, (tickFn)tickControlMotorOsc, (noteOnFn)playControlMotorOsc, (noteOffFn)stopControlMotorOsc, (ccFn)ccControlMotorOsc);
}

void initControlMotorOsc(ControlMotorOsc *o, int motorOutPin, int relayDirPin)
{
    pinMode(motorOutPin, OUTPUT);
    pinMode(relayDirPin, OUTPUT);
	
    o->motorOutPin = motorOutPin;
    o->relayDirPin = relayDirPin;
	
    o->uPeriod = 0;
    o->halfPeriod = 0;
    o->dir = 0;
    o->out = 0;
	
    digitalWrite(o->motorOutPin, o->out);
    digitalWrite(o->relayDirPin, o->dir);
}

void playControlMotorOsc(ControlMotorOsc *o, int note, int vel)
{   
    float f = mtof(note);
    float u = 1000000.f/f;
    o->uPeriod = u;
    o->halfPeriod = o->uPeriod/2;
	o->out = 0;
	digitalWrite(o->motorOutPin, o->out);
	digitalWrite(o->relayDirPin, o->dir);
}

void stopControlMotorOsc(ControlMotorOsc *o)
{
    o->uPeriod = 0; 
    o->halfPeriod = 0;
    o->out = 0;
	digitalWrite(o->motorOutPin, o->out);
}

void ccControlMotorOsc(ControlMotorOsc *o, int num, int val)
{
    if (num == 23)
    {
		if(val>63) {
			o->dir = 1;
		} else {
			o->dir = 0;
		}
        digitalWrite(o->relayDirPin, o->dir);
    }
}

void tickControlMotorOsc(ControlMotorOsc *o)
{
    if(o->uPeriod>0)
    {
        unsigned long pos = us % o->uPeriod;
        if(pos > o->halfPeriod != !o->out)
        {
            // tick
            o->out ^= 1;
			digitalWrite(o->motorOutPin, o->out);
			
        }
    }
}