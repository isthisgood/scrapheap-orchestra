
#include "Flapper.h"
#include "Runner.h"
#include <Arduino.h>
#include "OscUtils.h"
#include "constants.h"

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
    
    o->counter = 0;
    
    o->relayOut = LOW;
    o->flapOut = LOW;
    
    pinMode(o->flapPin, OUTPUT);
    pinMode(o->relayPin, OUTPUT);
    
    digitalWrite(o->flapPin, LOW);
    digitalWrite(o->relayPin, LOW);
}

// this starts a midi note playing
void playFlapper(Flapper *o, int note, int vel)
{
    if (o->counter == 0)
    {
        o->counter = FLAP_COUNT;
        o->flapOut = HIGH;
        o->relayOut = LOW;
        digitalWrite(o->relayPin, o->relayOut);
        digitalWrite(o->flapPin, o->flapOut);
    }
}


// this stops the sound outputting from an oscillator
void stopFlapper(Flapper *o)
{
}

void tickFlapper(Flapper *o)
{
    if (o->flapOut != LOW)
    {
        o->counter--;
        if (o->counter <= 0)
        {
            o->flapOut = LOW;
            digitalWrite(o->flapPin, o->flapOut);
        }
        else if (o->counter < HALF_FLAP_COUNT && o->relayOut == LOW)
        {
            o->relayOut = HIGH;
            digitalWrite(o->relayPin, o->relayOut);
        }
    }
}