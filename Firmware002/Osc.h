
#include "MidiMap.h"


void addOsc(MidiMap midi, int pin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

struct Osc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  int out;
  int pin;
  int note;
};


// initializes an oscillator on a pin.
void initOsc(Osc *o, int pin);

// this starts a midi note playing
void playOsc(Osc *o, int note);

// this stops the sound outputting from an oscillator
void stopOsc(Osc *o);

void ccOsc(Osc *o, int ctrlId, int val);


// call this on every osc you want to play in your sound loop
void tickOsc(Osc *o);

