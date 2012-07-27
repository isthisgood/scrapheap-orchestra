#include <Arduino.h>
unsigned long us;

void oscClock() {
    us = micros();
}


int mtof(int midiNote) {
  float freq = 440.0 * exp( 0.057762265 * ( midiNote-69.0 ) );
  return freq;
}
