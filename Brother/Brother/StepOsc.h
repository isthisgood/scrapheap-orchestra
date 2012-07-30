
#include "MidiMap.h"

void addStepOsc(MidiMap midi, int pinA, int pinB, int pinC, int pinD);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line




struct StepOsc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  
  
  int pinA;
  int pinB;
  int pinC;
  int pinD;
  
  int pos;
  int out;
  
};


// initializes an oscillator on a pin.
void initStepOsc(StepOsc *o, int pinA, int pinB, int pinC, int pinD);

// this starts a midi note playing
void playStepOsc(StepOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopStepOsc(StepOsc *o);




// call this on every osc you want to play in your sound loop
void tickStepOsc(StepOsc *o);



