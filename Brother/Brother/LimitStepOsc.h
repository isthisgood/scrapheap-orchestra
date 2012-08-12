#pragma once

#include "MidiMap.h"

void addLimitStepOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int reversePin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line



struct LimitStepOsc
{
    unsigned int uPeriod;
    unsigned int halfPeriod;
    
    int dirPin;
    int stepPin;
    int reversePin;
    int enableShiftPin;
      
    int dir;
    int out;
    int checked;
    unsigned long disabledTime;
    
    bool analog;
};


// initializes an oscillator on a pin.
void initLimitStepOsc(LimitStepOsc *o, int dirPin, int stepPin, int enableShiftPin, int reversePin);

// this starts a midi note playing
void playLimitStepOsc(LimitStepOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopLimitStepOsc(LimitStepOsc *o);

// call this on every osc you want to play in your sound loop
void tickLimitStepOsc(LimitStepOsc *o);



