#include "Osc.h"
#include <Stepper.h>

// Constants for the Motor Shield R3:
const int DirA = 12;
const int DirB = 13;
const int pwmA = 4;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, DirA, DirB);

int stepDir = 1;

// oscillator stuff
Osc osc1 = {0, 0, 0, 0};
unsigned long us;

int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}

void initOsc(Osc &o, int pin) {
  o.pin = pin;
  o.uPeriod = 0;
  o.halfPeriod = 0;
  o.out = 0;
}

void playOsc(Osc &o, int note) {
  float f = mtof(note);
  float u = 1000000.f/f;
  o.uPeriod = u;
  o.halfPeriod = o.uPeriod/4;
}

void stopOsc(Osc &o) {
  o.uPeriod = 0;
  o.halfPeriod = 0;
}

void tickOsc(Osc &o) {
  if(o.uPeriod>0) {
    unsigned long pos = us % o.uPeriod;
    if(pos>o.halfPeriod != !o.out) {
      o.out ^= 1;
      //digitalWrite(o.pin, o.out);
      if (o.out == 1) myStepper.step(stepDir);
    }
  }
}

void setup() {
  
  startMidi();
  
  // setup stepper control
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);

  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  // setup microswitches  
  attachInterrupt(0, goForward, RISING);
  attachInterrupt(1, goBackward, RISING);
  
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  
  pinMode(10, OUTPUT);
  
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  playOsc(osc1, 64);
}


void noteOn(int channel, int note, int vel) {
  if (channel == 2)
  {
    digitalWrite(pwmA, HIGH);
    digitalWrite(pwmB, HIGH);
    digitalWrite(10, HIGH);
    playOsc(osc1, note);
  }
}

void noteOff(int channel, int note) {
  if (channel == 2)
  {
    digitalWrite(pwmA, LOW);
    digitalWrite(pwmB, LOW);
    digitalWrite(10, LOW);
    stopOsc(osc1);
  }
}

void goForward()
{
  stepDir = 1;
  //myStepper.reverseSteps(1);
  //Serial.println("forward");
}

void goBackward()
{
  stepDir = -1;
  //myStepper.reverseSteps(0);
  //Serial.println("backward");
}

void loop() {
  updateMidi();
  us = micros();
  tickOsc(osc1);
}
