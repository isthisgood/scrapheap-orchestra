
#include "Switcher.h"
#include "Runner.h"
#include <Arduino.h>

void addSwitcher(MidiMap midi, int pin) {
  Switcher *osc = new Switcher;
  initSwitcher(osc, pin);
  addObject(midi, osc, NULL, (noteOnFn) playSwitcher, (noteOffFn)stopSwitcher, NULL);

}


// initializes an oscillator on a pin.
void initSwitcher(Switcher *o, int pin) {
  o->pin = pin;
    pinMode(o->pin, OUTPUT);
    digitalWrite(o->pin, 0);
  o->value = 0;
}

// this starts a midi note playing
void playSwitcher(Switcher *o, int note, int vel) {
  o->value = 1;
  digitalWrite(o->pin, 1);
  
}


// this stops the sound outputting from an oscillator
void stopSwitcher(Switcher *o) {
   o->value = 0;
  digitalWrite(o->pin, 0);
}

