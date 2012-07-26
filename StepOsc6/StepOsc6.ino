#include "StepOsc.h"
#include "OscUtils.h"
#include "Osc.h"





StepOsc osc1 = {0, 0, 0, 0};
Osc osc2 = {0,0,0,0};
Osc osc3 = {0,0,0,0};
Osc osc4 = {0,0,0,0};

void setup() {
  initStepOsc(osc1, 8, 9, 10, 11); 
  initOsc(osc2, 2);
  initOsc(osc3, 3);
  initOsc(osc4, 4);
  
  startMidi();

}


void noteOn(int channel, int note, int vel) {
  if(channel==1) {
    playStepOsc(osc1, note);
  } else if(channel==2) {
    playOsc(osc2, note);
  } else if(channel==3) {
    playOsc(osc3, note);
  } else if(channel==4) {
    playOsc(osc4, note);
  }
}

void noteOff(int channel, int note) {
  if(channel==1) {
    stopStepOsc(osc1);
  } else if(channel==2) {
    stopOsc(osc2);
  } else if(channel==3) {
    stopOsc(osc3);
  } else if(channel==4) {
    stopOsc(osc4);
  }
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/




void loop() {
  updateMidi();
  
  oscClock();
  tickStepOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
}
