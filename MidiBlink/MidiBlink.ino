
// set to zero if you want it to blink on all midi channels
int midiChannel = 0;


int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}



void setup() {
  startMidi();
  pinMode(13, OUTPUT);
}


void noteOn(int channel, int note, int vel) {
  if(channel==midiChannel || midiChannel==0) {
    digitalWrite(13, HIGH);
  }
}

void noteOff(int channel, int note) {
  if(channel==midiChannel || midiChannel==0) {
    digitalWrite(13, LOW);
  }
}


void loop() {
  updateMidi();
}
