
#include "ShiftSwitcher.h"
#include "Runner.h"
#include "ShiftRegister.h"

void addShiftSwitcher(MidiMap midi, int shiftablePin) {
  ShiftSwitcher *osc = new ShiftSwitcher;
  initShiftSwitcher(osc, shiftablePin);
  addObject(midi, osc, NULL, (noteOnFn) playShiftSwitcher, (noteOffFn)stopShiftSwitcher, NULL);

}


// initializes an oscillator on a pin.
void initShiftSwitcher(ShiftSwitcher *o, int pin) {
  o->pin = pin;
  o->value = 0;
}

// this starts a midi note playing
void playShiftSwitcher(ShiftSwitcher *o, int note, int vel) {
  o->value = 1;
  shiftPin(o->pin, 1);
  
}


// this stops the sound outputting from an oscillator
void stopShiftSwitcher(ShiftSwitcher *o) {
    o->value = 0;
  shiftPin(o->pin, 0);
}

