
#include "MidiMap.h"

void addSwitcher(MidiMap midiMap, int pin);


struct Switcher {
  int pin;
  int value;
};


// initializes an oscillator on a pin.
void initSwitcher(Switcher *o, int pin);

// this starts a midi note playing
void playSwitcher(Switcher *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopSwitcher(Switcher *o);
