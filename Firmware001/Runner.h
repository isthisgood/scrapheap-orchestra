

#ifndef RUNNER_H
#define RUNNER_H
#include "MidiMap.h"

#define MAX_NUM_OSCS 8
#ifndef NULL
#    define NULL (0)
#endif

// these are the function pointers that point to the various parts of an oscillator

typedef void(*noteOnFn)(void *, int note);
typedef void(*noteOffFn)(void *);
typedef void(*ccFn)(void *, int cid, int value);
typedef void*  Object;

// this needs to be called every frame
typedef void(*tickFn)(void *);




/**
 * Add an oscillator of any type, by providing the struct, the tick function, noteon, noteoff and cc function.
 * All functions are optional, just pass null in to a function if your object doesn't use it.
 */
void addObject(MidiMap midi, Object osc, tickFn tickFunction, noteOnFn noteon, noteOffFn noteoff, ccFn ccFunction);

void doAllTicks();



// callbacks for midi
void noteOn(int channel, int note, int vel);
void noteOff(int channel, int note);

/*
void cc(int channel, int ctrlId, int value);
*/


#endif // RUNNER_H
