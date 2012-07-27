#include "StepOsc.h"
#include "OscUtils.h"
#include "Osc.h"
#include "Runner.h"


void setup() {
  
  addStepOsc(MidiMap(3, 12, 24), 8, 9, 10, 11);
  addOsc(2);
  addOsc(3);
  addOsc(4);

  
  startMidi();

}


void noteOn(int channel, int note, int vel) {
 /* if(channel==1) {
    playStepOsc(osc1, note);
  } else if(channel==2) {
    playOsc(osc2, note);
  } else if(channel==3) {
    playOsc(osc3, note);
  } else if(channel==4) {
    playOsc(osc4, note);
  }*/
}

void noteOff(int channel, int note) {
/*  if(channel==1) {
    stopStepOsc(osc1);
  } else if(channel==2) {
    stopOsc(osc2);
  } else if(channel==3) {
    stopOsc(osc3);
  } else if(channel==4) {
    stopOsc(osc4);
  }*/
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/




void loop() {
  updateMidi();
  
  oscClock();
  doAllTicks();
}
