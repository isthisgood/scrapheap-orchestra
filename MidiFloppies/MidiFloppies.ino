#include "Osc.h"
//unsigned long uPeriod = 0;

unsigned long us;




Osc osc1 = {0, 0, 0, 0, 0, 0, 0};
Osc osc2 = {0, 0, 0, 0, 0, 0, 0};
Osc osc3 = {0, 0, 0, 0, 0, 0, 0};
Osc osc4 = {0, 0, 0, 0, 0, 0, 0};
//Osc osc5 = {0, 0, 0, 0};
//Osc osc6 = {0, 0, 0, 0};




//int out = 0;
void initOsc(Osc &o, int dirPin, int stepPin) {
  o.dirPin = dirPin;
  o.stepPin = stepPin;
  o.dirOut = LOW;
  o.stepOut = LOW;
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, o.stepOut);
  digitalWrite(dirPin, o.dirOut);
  //o.uPeriod = 0;
  //o.halfPeriod = 0;
  //o.out = 0;
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
    if(pos>o.halfPeriod != !o.stepOut) {
        //Switch directions if end has been reached
        if (o.steps > 157)
        {
          o.dirOut = HIGH;
          digitalWrite(o.dirPin, o.dirOut);
        }
        else if (o.steps <= 0)
        {
          o.dirOut = LOW;
          digitalWrite(o.dirPin, o.dirOut);
        }
        
        if (o.dirOut == HIGH) o.steps--;
        else o.steps++;
      
        o.stepOut ^= 1;
        digitalWrite(o.stepPin, o.stepOut);
    }
  }
}

void setup() {
  initOsc(osc1, 6, 7); 
  //initOsc(osc2, 9); 
  //initOsc(osc3, 10);
  //initOsc(osc4, 11);
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
  
  us = micros();
  tickOsc(osc1);
  tickOsc(osc2);
  tickOsc(osc3);
  tickOsc(osc4);
  //tickOsc(osc5);
  //tickOsc(osc6);
}
