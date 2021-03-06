#include "Osc.h"
//unsigned long uPeriod = 0;

unsigned long us;


bool noise = 0;

Osc osc1 = {0, 0, 0, 0};
Osc osc2 = {0, 0, 0, 0};
Osc osc3 = {0, 0, 0, 0};
Osc osc4 = {0, 0, 0, 0};
//Osc osc5 = {0, 0, 0, 0};
//Osc osc6 = {0, 0, 0, 0};


unsigned long stopOsc1Time = 0;

//int out = 0;
void initOsc(Osc &o, int pin) {
  pinMode(pin, OUTPUT);
  o.pin = pin;
  o.uPeriod = 0;
  o.halfPeriod = 0;
  o.out = 0;
}



int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}


void playOsc(Osc &o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o.uPeriod = u;
  o.halfPeriod = o.uPeriod/2;
}

void stopOsc(Osc &o) {
  o.uPeriod = 0;
  o.halfPeriod = 0;
}


void tickOsc(Osc &o) {
  if(o.uPeriod>0) {
    unsigned long pos = us % o.uPeriod;
    if(pos>o.halfPeriod != !o.out) {
      o.out ^= 1;
      if (noise == 0) digitalWrite(o.pin, o.out);
      else if ((int)random(0, 2) == 0) digitalWrite(o.pin, o.out);
    }
  }
}

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
  noise = 1;
  if(channel==1) {
    stopOsc1Time = 0;
    playOsc(osc1, note + 30);
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
  noise = 0;
  if(channel==1) {
    playOsc(osc1, note + 50);
    stopOsc1Time = us + random(20000, 200000);
    //stopOsc(osc1);
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
  us = micros();
  
  if (stopOsc1Time != 0 && us > stopOsc1Time)
  {
    stopOsc1Time = 0;
    stopOsc(osc1);
  }
  
  updateMidi();
  
  tickOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
  //tickOsc(osc5);
  //tickOsc(osc6);
}
