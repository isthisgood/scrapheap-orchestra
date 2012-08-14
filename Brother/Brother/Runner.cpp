
#include "Arduino.h"
#include "Runner.h"

#include "Midi.h"
#include "ShiftRegister.h"
#include "OscUtils.h"
#include "constants.h"




void initRunner() {
	startMidi();
	setupShiftRegister();
}


void runRunner() {
	updateMidi();
  
	oscClock();
	doAllTicks();
}

int numOscs = 0;


tickFn     tickFunctions[MAX_NUM_OSCS];

void *oscs[MAX_NUM_OSCS];

struct MidiListener {
  int channel; // copy of midi channel in MidiMap for speed
  MidiMap midiMap;
  
  Object object;
  
  noteOnFn noteOnFunc;
  noteOffFn noteOffFunc;
  ccFn ccFunc;

};

int numMidiListeners = 0;
MidiListener midiListeners[MAX_NUM_OSCS];


/**
 * Add an oscillator of any type, by providing the struct, the tick function, noteon, noteoff and cc function.
 * All functions are optional, just pass null in to a function if your object doesn't use it.
 */
void addObject(MidiMap midi, Object osc, tickFn tickFunction, noteOnFn noteonFunction, noteOffFn noteoffFunction, ccFn ccFunction) {
  
  // only add tick functions if they exist (no nulls please)
  if(tickFunction!=NULL) {
    // this is annoying but it will stop it crashing
    if(numOscs>=MAX_NUM_OSCS) {
      numOscs = 0;
    }
  
    tickFunctions[numOscs] = tickFunction;
    oscs[numOscs] = osc;
    numOscs++;
  }
  
  // only add midi if it exists (almost entirely likely
  if(noteonFunction!=NULL || noteoffFunction!=NULL || ccFunction!=NULL) {
    if(numMidiListeners>=MAX_NUM_OSCS) numMidiListeners = 0;
    
    midiListeners[numMidiListeners].channel = midi.channel;
    midiListeners[numMidiListeners].midiMap = midi;
    midiListeners[numMidiListeners].object = osc;
    midiListeners[numMidiListeners].noteOnFunc = noteonFunction;
    midiListeners[numMidiListeners].noteOffFunc = noteoffFunction;
    midiListeners[numMidiListeners].ccFunc = ccFunction;
    
    numMidiListeners++;
  }
  
}

void noteOn(int channel, int note, int vel) {
  for(int i = 0; i < numMidiListeners; i++) { // loop through all midi listeners
    if(midiListeners[i].channel == channel) { // if we're on the right midichannel
      if(midiListeners[i].noteOnFunc!=NULL) { // and there is a midi note on for that channel
        if(note>=midiListeners[i].midiMap.from && note<=midiListeners[i].midiMap.to) { // and the note is in range
          (*midiListeners[i].noteOnFunc)(midiListeners[i].object, note+midiListeners[i].midiMap.transpose, vel); // play it, offset by its transpose
        }
      }
    }
  }
	
}



void noteOff(int channel, int note) {
  for(int i = 0; i < numMidiListeners; i++) { // loop through all midi listeners
    if(midiListeners[i].channel == channel) { // if we're on the right midichannel
      if(midiListeners[i].noteOffFunc!=NULL) { // and there is a midi note on for that channel
        if(note>=midiListeners[i].midiMap.from && note<=midiListeners[i].midiMap.to) { // and the note is in range
          (*midiListeners[i].noteOffFunc)(midiListeners[i].object); // play it, offset by its transpose
        }
      }
    }
  }
}



void cc(int channel, int ctrlId, int value) {
  for(int i = 0; i < numMidiListeners; i++) { // loop through all midi listeners
    if(midiListeners[i].channel == channel) { // if we're on the right midichannel
      if(midiListeners[i].ccFunc!=NULL) { // and there is a midi note on for that channel
        (*midiListeners[i].ccFunc)(midiListeners[i].object, ctrlId, value); // play it, offset by its transpose  
      }
    }
  }
}





void doAllTicks() {
  for(int i = 0; i < numOscs; i++) {
    if(tickFunctions[i]!=NULL) {
      (*tickFunctions[i])(oscs[i]);
    }
  }
}

