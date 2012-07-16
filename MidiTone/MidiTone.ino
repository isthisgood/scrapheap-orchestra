
#include "Tone.h"

Tone tone1;
Tone tone2;

int c0 = -1;
int c1 = -1;
int c2 = -1;

void setup() {
  tone1.begin(13); 
  tone2.begin(12);
  Serial.begin(31250);
}

int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}

void loop() {
  int b = Serial.read();
  if(b!=-1) {
    c2 = c1;
    c1 = c0;
    c0 = b;

    // we have a midi note
    
    
    
    
    // this is for midi channel 1
    if(c2==0x90) {
      if(c0==0) {
        // note off
        tone1.stop();
      } else {
        tone1.play(mtof(c1));
      }
    }
    if(c2==0x80) {
      tone1.stop();
    }
    
    
    // midi channel 2
    if(c2==0x91) {
      if(c0==0) {
        // note off
        tone2.stop();
      } else {
        tone2.play(mtof(c1));
      }
    }
    if(c2==0x81) {
      tone2.stop();
    }
    
    
  }
  
}


