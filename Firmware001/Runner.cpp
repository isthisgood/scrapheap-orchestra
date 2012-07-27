

#include "Runner.h"



int numOscs = 0;


tickFn     tickFunctions[MAX_NUM_OSCS];
noteOnFn   noteOnFunctions[MAX_NUM_OSCS];
noteOffFn  noteOffFunctions[MAX_NUM_OSCS];
ccFn       ccFunctions[MAX_NUM_OSCS];

void *oscs[MAX_NUM_OSCS];


/**
 * Add an oscillator of any type, by providing the struct, the tick function, noteon, noteoff and cc function.
 * All functions are optional, just pass null in to a function if your object doesn't use it.
 */
void addObject(void *osc, tickFn tickFunction, tickFn, noteOnFn noteonFunction, noteOffFn noteoffFunction, ccFn ccFunction) {
  // this is annoying but it will stop it crashing
  if(numOscs>=MAX_NUM_OSCS) {
    numOscs = 0;
  }
  tickFunctions[numOscs] = tickFunction;
  oscs[numOscs] = osc;
  noteOnFunctions[numOscs] = noteonFunction;
  noteOffFunctions[numOscs] = noteoffFunction;
  ccFunctions[numOscs] = ccFunction;
  numOscs++;
}



void doAllTicks() {
  for(int i = 0; i < numOscs; i++) {
    if(tickFunctions[i]!=NULL) {
      (*tickFunctions[i])(oscs[i]);
    }
  }
}

