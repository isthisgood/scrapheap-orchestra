
#include "MidiMap.h"


void addRandOsc(MidiMap midi, int pin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

struct RandOsc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  int out;
  int pin;
  int randValue;
  unsigned int randPeriod;
};


// initializes an oscillator on a pin.
void initRandOsc(RandOsc *o, int pin);

// this starts a midi note playing
void playRandOsc(RandOsc *o, int note);

// this stops the sound outputting from an oscillator
void stopRandOsc(RandOsc *o);

void ccRandOsc(RandOsc *o, int num, int val);

// call this on every osc you want to play in your sound loop
void tickRandOsc(RandOsc *o);

