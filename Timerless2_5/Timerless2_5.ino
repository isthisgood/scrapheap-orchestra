#include "Osc.h"
//unsigned long uPeriod = 0;






Osc osc1 = {0, 0, 0, 0};
Osc osc2 = {0, 0, 0, 0};
Osc osc3 = {0, 0, 0, 0};
Osc osc4 = {0, 0, 0, 0};
//Osc osc5 = {0, 0, 0, 0};
//Osc osc6 = {0, 0, 0, 0};



void setup() {
  initOsc(osc1, 8); 
  initOsc(osc2, 9); 
  initOsc(osc3, 10);
  initOsc(osc4, 11);
 // initOsc(osc5, 12);
 // initOsc(osc6, 13);
  
 
  
  startMidi();

}


void noteOn(int channel, int note, int vel) {
  if(channel==1) {
    playOsc(osc1, note);
  } else if(channel==2) {
    playOsc(osc2, note);
  } else if(channel==3) {
    playOsc(osc3, note);
  } else if(channel==4) {
    playOsc(osc4, note);
 // } else if(channel==5) {
  //  playOsc(osc5, note);
 // } else if(channel==6) {
  //  playOsc(osc6, note);
  }
}

void noteOff(int channel, int note) {
  if(channel==1) {
    stopOsc(osc1);
  } else if(channel==2) {
    stopOsc(osc2);
  } else if(channel==3) {
    stopOsc(osc3);
  } else if(channel==4) {
    stopOsc(osc4);
 // } else if(channel==5) {
  //  stopOsc(osc5);
  //} else if(channel==6) {
 //   stopOsc(osc6);
  }
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/




void loop() {
  updateMidi();
  
  oscClock();
  tickOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
  //tickOsc(osc5);
  //tickOsc(osc6);
}
