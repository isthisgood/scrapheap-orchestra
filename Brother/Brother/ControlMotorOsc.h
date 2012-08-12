// this is for direction controllable dc motors
// the motors should be plugged into the fets
#pragma once
#include "MidiMap.h"

void addControlMotorOsc(MidiMap midi, int motorOutPin, int relayDirPin);

/////////////////////////////////////////////////////////////////////////
// You don't need to touch anything below this line

// 20000 micros = 1/50th second
//const unsigned long LIMIT_CHECK = 20000;
//const unsigned long HALF_LIMIT_CHECK = LIMIT_CHECK / 2;
//const unsigned long DISABLED_PERIOD = 1e6;

struct ControlMotorOsc
{
    unsigned int uPeriod;
    unsigned int halfPeriod;
    
    int motorOutPin;
    int relayDirPin;
    int dir;
    int out;
};


// initializes an oscillator on a pin.
void initControlMotorOsc(ControlMotorOsc *o, int motorOutPin, int relayDirPin);

// this starts a midi note playing
void playControlMotorOsc(ControlMotorOsc *o, int note, int vel);

// this stops the sound outputting from an oscillator
void stopControlMotorOsc(ControlMotorOsc *o);

void ccControlMotorOsc(ControlMotorOsc *o, int num, int val);

// call this on every osc you want to play in your sound loop
void tickControlMotorOsc(ControlMotorOsc *o);



