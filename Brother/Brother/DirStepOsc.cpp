/**
 *  DirStepOsc.cpp
 *
 *  Created by Marek Bereza on 30/07/2012.
 */

#include "DirStepOsc.h"

#include "StepOsc.h"
#include "Arduino.h"
#include "OscUtils.h"
#include "Runner.h"
#include "constants.h"

#include "constants.h"
#include "ShiftRegister.h"




void addDirStepOsc(MidiMap midi, int which, int stepDirCC) {
	//addDirStepOsc(midi, );
	/*if(which==STEPPER_1) {
		addDirStepOsc(midi, STEP1, DIR1, EN1, stepDirCC);
	} else if(which==STEPPER_2) {
		addDirStepOsc(midi, STEP2, DIR2, EN2, stepDirCC);
	} else if(which==STEPPER_3) {
		addDirStepOsc(midi, STEP3, DIR3, EN3, stepDirCC);
	} else if(which==STEPPER_4) {
		addDirStepOsc(midi, STEP4, DIR4, EN4, stepDirCC);
	}*/
}



void addDirStepOsc(MidiMap midi, int stepPin, int directionPin, int enableShiftPin, int stepDirCC) {
	DirStepOsc *o = new DirStepOsc();
	initDirStepOsc(o, stepPin, directionPin, enableShiftPin, stepDirCC);
	addObject(midi, o, (tickFn)tickDirStepOsc, (noteOnFn)playDirStepOsc, (noteOffFn)stopDirStepOsc, (ccFn)ccDirStepOsc);
}


void initDirStepOsc(DirStepOsc *o, int stepPin, int directionPin, int enableShiftPin, int stepDirCC) {
	pinMode(stepPin, OUTPUT);
	pinMode(directionPin, OUTPUT);
	
	// disable stepper 
	shiftPin(o->enableShiftPin, 0);
	
	o->stepPin = stepPin;
	o->directionPin = directionPin;
	o->enableShiftPin = enableShiftPin;
	o->stepDirCC = stepDirCC;
	
	digitalWrite(o->directionPin, 0);
	
	o->uPeriod = 0;
	o->halfPeriod = 0;
	o->dir = 0;
	digitalWrite(o->directionPin, o->dir);
	o->out = 0;

}


void ccDirStepOsc(DirStepOsc *o, int cc, int value) {
	if(o->stepDirCC==cc) {
		o->dir = value>63?1:0;
		digitalWrite(o->directionPin, o->dir);
	}
}


void playDirStepOsc(DirStepOsc *o, int note, int vel) {
	float f = mtof(note)*2;
	float u = 1000000.f/f;
	o->uPeriod = u;
	o->halfPeriod = o->uPeriod/2;
	o->out = 0;
	shiftPin(o->enableShiftPin, 1);
}

void stopDirStepOsc(DirStepOsc *o) {
	o->uPeriod = 0;
	o->halfPeriod = 0;
	
	shiftPin(o->enableShiftPin, 0);
	
	o->out = 0;
}



void tickDirStepOsc(DirStepOsc *o) {
	if(o->uPeriod>0) {
		unsigned long pos = us % o->uPeriod;
		if(pos>o->halfPeriod != !o->out) {
			// tick
			o->out ^= 1;
			digitalWrite(o->stepPin, o->out);
			// increment step appropriately
			// to go forward just mod plus, and backwards mod minus
			
			
			// then step
		//	stepStepOsc(o);
		}
	}
}

