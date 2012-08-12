
#include "MidiMap.h"

void addControlStepOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line



struct ControlStepOsc
{
    unsigned int uPeriod;
    unsigned int halfPeriod;
    
    int dirPin;
    int stepPin;
    int enableShiftPin;
	
    int dir;
    int out;
};


// initializes an oscillator on a pin.
void initControlStepOsc(ControlStepOsc *o, int dirPin, int stepPin, int enableShiftPin);

// this starts a midi note playing
void playControlStepOsc(ControlStepOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopControlStepOsc(ControlStepOsc *o);

void ccControlStepOsc(ControlStepOsc *o, int num, int val);

// call this on every osc you want to play in your sound loop
void tickControlStepOsc(ControlStepOsc *o);
