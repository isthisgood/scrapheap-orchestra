struct Osc {
  unsigned int uPeriod;
  unsigned int halfPeriod;
  int out;
  int pin;
  
};

// converts a midi note to 
int mtof(int midiNote);

// initializes an oscillator on a pin.
void initOsc(Osc &o, int pin);

// this starts a midi note playing
void playOsc(Osc &o, int note);

// this stops the sound outputting from an oscillator
void stopOsc(Osc &o);



// call this at the beginning of your sound loop
void oscClock();

// call this on every osc you want to play in your sound loop
void tickOsc(Osc &o);

