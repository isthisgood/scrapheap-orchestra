
#include "MidiMap.h"

void addShiftSwitcher(MidiMap midiMap, int shiftablePin);


struct ShiftSwitcher {
  int pin;
  int value;
};


// initializes an oscillator on a pin.
void initShiftSwitcher(ShiftSwitcher *o, int pin);

// this starts a midi note playing
void playShiftSwitcher(ShiftSwitcher *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopShiftSwitcher(ShiftSwitcher *o);
