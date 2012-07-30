
#include "MidiMap.h"


void addVelOsc(MidiMap midi, int pin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

struct VelOsc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  int out;
  int pin;
  int pwmValue;
};


// initializes an oscillator on a pin.
void initVelOsc(VelOsc *o, int pin);

// this starts a midi note playing
void playVelOsc(VelOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopVelOsc(VelOsc *o);

void ccVelOsc(VelOsc *o, int num, int val);

// call this on every osc you want to play in your sound loop
void tickVelOsc(VelOsc *o);

