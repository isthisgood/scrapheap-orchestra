
#include "MidiMap.h"


void addPWMOsc(MidiMap midi, int pin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

struct PWMOsc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  int out;
  int pin;
  int pwmValue;
};


// initializes an oscillator on a pin.
void initPWMOsc(PWMOsc *o, int pin);

// this starts a midi note playing
void playPWMOsc(PWMOsc *o, int note);

// this stops the sound outputting from an oscillator
void stopPWMOsc(PWMOsc *o);

void ccPWMOsc(PWMOsc *o, int num, int val);

// call this on every osc you want to play in your sound loop
void tickPWMOsc(PWMOsc *o);

