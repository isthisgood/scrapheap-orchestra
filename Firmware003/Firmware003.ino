#include "StepOsc.h"
#include "OscUtils.h"
#include "Osc.h"
#include "Runner.h"
#include "MidiMap.h"
#include "PWMOsc.h"
#include "RandOsc.h"
#include "Midi.h"
#include "VelOsc.h"
#include "Switcher.h"


void setup() {
  
 // addStepOsc(midimap(CHANNEL_1), 8, 9, 10, 11);
  addVelOsc(midimap(CHANNEL_1), 12);
  addSwitcher(midimap(CHANNEL_2), 13);
  //addOsc(midimap(CHANNEL_4), 4);

  
  initRunner();
}





void loop() {
  runRunner();
}
