
#include "Flapper.h"
#include "Runner.h"
#include <Arduino.h>
#include "OscUtils.h"

void addFlapper(MidiMap midi, int flapPin, int relayPin)
{
    Flapper *osc = new Flapper;
    initFlapper(osc, flapPin, relayPin);
    addObject(midi, osc, (tickFn)tickFlapper, (noteOnFn)playFlapper, (noteOffFn)stopFlapper, NULL);
}

// initializes an oscillator on a pin.
void initFlapper(Flapper *o, int flapPin, int relayPin)
{
    o->flapPin = flapPin;
    o->relayPin = relayPin;
    
    pinMode(o->flapPin, OUTPUT);
    pinMode(o->relayPin, OUTPUT);
    
    digitalWrite(o->flapPin, LOW);
    digitalWrite(o->relayPin, LOW);
}

// this starts a midi note playing
void playFlapper(Flapper *o, int note, int vel)
{
    o->flapEnd = us + FLAP_TIME;
    digitalWrite(o->relayPin, LOW);
    digitalWrite(o->flapPin, HIGH);
}


// this stops the sound outputting from an oscillator
void stopFlapper(Flapper *o)
{
    o->flapEnd = us + FLAP_TIME;
    digitalWrite(o->relayPin, HIGH);
    digitalWrite(o->flapPin, HIGH);
}

void tickFlapper(Flapper *o)
{
    if (us > o->flapEnd) digitalWrite(o->flapPin, LOW);
}