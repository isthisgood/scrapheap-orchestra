
#include "MidiMap.h"

void addSimpleStepOsc(MidiMap midi, int dirPin, int stepPin, int enableShiftPin, int reversePin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

// 20000 micros = 1/50th second
const unsigned long LIMIT_CHECK = 20000;
const unsigned long HALF_LIMIT_CHECK = LIMIT_CHECK / 2;
const unsigned long DISABLED_PERIOD = 1e6;

struct SimpleStepOsc
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
};


// initializes an oscillator on a pin.
void initSimpleStepOsc(SimpleStepOsc *o, int dirPin, int stepPin, int enableShiftPin, int reversePin);

// this starts a midi note playing
void playSimpleStepOsc(SimpleStepOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopSimpleStepOsc(SimpleStepOsc *o);




// call this on every osc you want to play in your sound loop
void tickSimpleStepOsc(SimpleStepOsc *o);



