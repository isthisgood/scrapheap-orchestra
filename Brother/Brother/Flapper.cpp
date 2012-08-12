
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
    o->flapUpTime = 0;
    o->flapDownTime = 0;
    o->flapPin = flapPin;
    o->relayPin = relayPin;
    o->relayOut = 0;
    
    pinMode(o->flapPin, OUTPUT);
    pinMode(o->relayPin, OUTPUT);
    
    digitalWrite(o->flapPin, LOW);
    digitalWrite(o->relayPin, LOW);
}

// this starts a midi note playing
void playFlapper(Flapper *o, int note, int vel)
{
    if (o->flapUpTime == 0)
    {
        unsigned long mod = us % 5000000;
        o->flapUpTime = mod + FLAP_TIME;
        o->flapDownTime = mod + 2 * FLAP_TIME;
        
        o->relayOut = LOW;
        digitalWrite(o->relayPin, o->relayOut);
        digitalWrite(o->flapPin, HIGH);
    }
}


// this stops the sound outputting from an oscillator
void stopFlapper(Flapper *o)
{
}

void tickFlapper(Flapper *o)
{
    if (o->flapUpTime != 0)
    {
        unsigned long mod = us % 5000000;
        if (mod > o->flapDownTime)
        {
            digitalWrite(o->flapPin, LOW);
            o->flapUpTime = 0;
            o->flapDownTime = 0;
        }
        else if (mod > o->flapUpTime && o->relayOut == LOW)
        {
            o->relayOut = HIGH;
            digitalWrite(o->relayPin, o->relayOut);
        }
    }
}