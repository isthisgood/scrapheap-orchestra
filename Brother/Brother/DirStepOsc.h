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
 *  DirStepOsc.h, created by Marek Bereza on 30/07/2012.
 */

#pragma once

#include "MidiMap.h"



void addDirStepOsc(MidiMap midi, int which, int stepDirCC);

void addDirStepOsc(MidiMap midi, int stepPin, int directionPin, int enableShiftPin, int stepDirCC);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line




struct DirStepOsc {
	unsigned int uPeriod;
	unsigned int halfPeriod;
	
	
	int stepPin;
	int directionPin;
	int enableShiftPin;
	
	int pos;
	int out;
	
};


// initializes an oscillator on a pin.
void initDirStepOsc(DirStepOsc *o, int stepPin, int directionPin, int enableShiftPin);

// this starts a midi note playing
void playDirStepOsc(DirStepOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopDirStepOsc(DirStepOsc *o);

// this stops the sound outputting from an oscillator
void ccDirStepOsc(DirStepOsc *o);



// call this on every osc you want to play in your sound loop
void tickDirStepOsc(DirStepOsc *o);



