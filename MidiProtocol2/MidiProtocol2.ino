#include <Tone.h>
Tone tone1;
Tone tone2;


int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}



void setup() {
  startMidi();
  tone1.begin(12);
  tone2.begin(13);
}


void noteOn(int channel, int note, int vel) {
  if(channel==1) {
    tone1.play(mtof(note));
  } else if(channel==2) {
    tone2.play(mtof(note));
  }
}

void noteOff(int channel, int note) {
  if(channel==1) {
    tone1.stop();
  } else if(channel==2) {
    tone2.stop();
  }
}

/*
void cc(int channel, int ctrlId, int value) {
}
*/

void loop() {
  updateMidi();
}
