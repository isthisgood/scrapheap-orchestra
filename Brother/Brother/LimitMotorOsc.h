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
 *  LimitMotorOsc.h, created by Marek Bereza on 10/08/2012.
 */
// this is for print head motors that have limit switches
// it drives the motors from the stepper drivers
#pragma once
#include "MidiMap.h"

void addLimitMotorOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int limitPin, int relayPin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

// 20000 micros = 1/50th second
//const unsigned long LIMIT_CHECK = 20000;
//const unsigned long HALF_LIMIT_CHECK = LIMIT_CHECK / 2;
//const unsigned long DISABLED_PERIOD = 1e6;

struct LimitMotorOsc
{
    unsigned int uPeriod;
    unsigned int halfPeriod;
    
    int dirPin;
    int stepPin;
    int limitPin;
    int enableShiftPin;
	int relayPin;
	int relayDir;
    int dir;
    int out;
    int checked;
    unsigned long disabledTime;
    bool analog;
};


// initializes an oscillator on a pin.
void initLimitMotorOsc(LimitMotorOsc *o, int dirPin, int stepPin, int enableShiftPin, int limitPin, int relayPin);

// this starts a midi note playing
void playLimitMotorOsc(LimitMotorOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopLimitMotorOsc(LimitMotorOsc *o);




// call this on every osc you want to play in your sound loop
void tickLimitMotorOsc(LimitMotorOsc *o);



