#include "MidiMap.h"




MidiMap midimap(int channel) {
  MidiMap m;
  m.channel = channel;
  m.from = 0;
  m.to = 127;
  m.transpose = 0;
  return m;
}
MidiMap midimap(int channel, int from, int to)  {
  MidiMap m;
  m.channel = channel;
  m.from = from;
  m.to = to;
  m.transpose = 0;
  return m;
}
MidiMap midimap(int channel, int from, int to, int transpose) {
  MidiMap m;
  m.channel = channel;
  m.from = from;
  m.to = to;
  m.transpose = transpose;
  return m;
}


