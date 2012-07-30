
#include "MidiMap.h"


void addFloppyOsc(MidiMap midi, int dirPin, int stepPin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

struct FloppyOsc {
    unsigned int uPeriod;
    unsigned int halfPeriod;
    
    int dir;
    int steps;
    int out;
    
    
    int dirPin;
    int stepPin;
};


// initializes an oscillator on a pin.
void initFloppyOsc(FloppyOsc *o, int dirPin, int stepPin);

// this starts a midi note playing
void playFloppyOsc(FloppyOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopFloppyOsc(FloppyOsc *o);


// call this on every osc you want to play in your sound loop
void tickFloppyOsc(FloppyOsc *o);

