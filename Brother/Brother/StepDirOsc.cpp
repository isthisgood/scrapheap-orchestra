/**
 *  StepDirOsc.cpp
 *
 *  Created by Marek Bereza on 30/07/2012.
 */

#include "StepDirOsc.h"

#include "StepOsc.h"
#include "Arduino.h"
#include "OscUtils.h"
#include "Runner.h"





void addStepDirOsc(MidiMap midi, int which) {
	//addStepDirOsc(midi, );
}



void addStepDirOsc(MidiMap midi, int stepPin, int directionPin, int enableShiftPin) {
	StepDirOsc *o = new StepDirOsc();
	initStepDirOsc(o, stepPin, directionPin, enableShiftPin);
	addObject(midi, o, (tickFn)tickStepDirOsc, (noteOnFn)playStepDirOsc, (noteOffFn)stopStepDirOsc, (ccFn)ccStepDirOsc);
}





//int out = 0;
void initStepDirOsc(StepDirOsc *o, int stepPin, int directionPin, int enableShiftPin) {
	pinMode(stepPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	
	o->stepPin = stepPin;
	o->directionPin = directionPin;
	o->enableShiftPin = enableShiftPin;
	
	o->uPeriod = 0;
	o->halfPeriod = 0;
	o->pos = 0;
	o->out = 0;
	
}





void playStepDirOsc(StepDirOsc *o, int note, int vel) {
	float f = mtof(note);
	float u = 1000000.f/f;
	o->uPeriod = u;
	o->halfPeriod = o->uPeriod/2;
	o->out = 0;
}

void stopStepDirOsc(StepDirOsc *o) {
	o->uPeriod = 0;
	o->halfPeriod = 0;
	/*digitalWrite(o->pinA, 0);
	digitalWrite(o->pinB, 0);
	digitalWrite(o->pinC, 0);
	digitalWrite(o->pinD, 0);*/
	
	o->pos = 0;
	o->out = 0;
}



void tickStepDirOsc(StepDirOsc *o) {
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
		//	stepStepOsc(o);
		}
	}
}

