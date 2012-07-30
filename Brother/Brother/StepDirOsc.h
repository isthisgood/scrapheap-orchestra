/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  StepDirOsc.h, created by Marek Bereza on 30/07/2012.
 */

#pragma once

#include "MidiMap.h"



void addStepDirOsc(MidiMap midi, int which);

void addStepDirOsc(MidiMap midi, int stepPin, int directionPin, int enableShiftPin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line




struct StepDirOsc {
	unsigned int uPeriod;
	unsigned int halfPeriod;
	
	
	int stepPin;
	int directionPin;
	int enableShiftPin;
	
	int pos;
	int out;
	
};


// initializes an oscillator on a pin.
void initStepDirOsc(StepDirOsc *o, int stepPin, int directionPin, int enableShiftPin);

// this starts a midi note playing
void playStepDirOsc(StepDirOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopStepDirOsc(StepDirOsc *o);

// this stops the sound outputting from an oscillator
void ccStepDirOsc(StepDirOsc *o);



// call this on every osc you want to play in your sound loop
void tickStepDirOsc(StepDirOsc *o);



