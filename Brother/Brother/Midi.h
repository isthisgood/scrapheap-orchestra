
#define MIDI_BAUD_RATE 31250
#include "Runner.h"


void startMidi();

void updateMidi();








// to enable midi status
#define USING_CC

// define these yourself

// callbacks for midi
void noteOn(int channel, int note, int vel);
void noteOff(int channel, int note);

#ifdef USING_CC
void cc(int channel, int ctrlId, int value);
#endif
