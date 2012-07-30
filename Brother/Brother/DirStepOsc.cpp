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





void addDirStepOsc(MidiMap midi, int which, int stepDirCC) {
	//addDirStepOsc(midi, );
	if(which==1) {
		addDirStepOsc(midi, STEP1, DIR1, EN1, stepDirCC);
	} else if(which==2) {
		addDirStepOsc(midi, STEP2, DIR2, EN2, stepDirCC);
	} else if(which==3) {
		addDirStepOsc(midi, STEP3, DIR3, EN3, stepDirCC);
	} else if(which==4) {
		addDirStepOsc(midi, STEP4, DIR4, EN4, stepDirCC);
	}
}



void addDirStepOsc(MidiMap midi, int stepPin, int directionPin, int enableShiftPin, int stepDirCC) {
	DirStepOsc *o = new DirStepOsc();
	initDirStepOsc(o, stepPin, directionPin, enableShiftPin);
	addObject(midi, o, (tickFn)tickDirStepOsc, (noteOnFn)playDirStepOsc, (noteOffFn)stopDirStepOsc, (ccFn)ccDirStepOsc);
}





//int out = 0;
void initDirStepOsc(DirStepOsc *o, int stepPin, int directionPin, int enableShiftPin) {
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


void ccDirStepOsc(DirStepOsc *o) {

}


void playDirStepOsc(DirStepOsc *o, int note, int vel) {
	float f = mtof(note);
	float u = 1000000.f/f;
	o->uPeriod = u;
	o->halfPeriod = o->uPeriod/2;
	o->out = 0;
}

void stopDirStepOsc(DirStepOsc *o) {
	o->uPeriod = 0;
	o->halfPeriod = 0;
	/*digitalWrite(o->pinA, 0);
	digitalWrite(o->pinB, 0);
	digitalWrite(o->pinC, 0);
	digitalWrite(o->pinD, 0);*/
	
	o->pos = 0;
	o->out = 0;
}



void tickDirStepOsc(DirStepOsc *o) {
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

