
#ifndef MIDIMAP_H
#define MIDIMAP_H
struct MidiMap {
  int channel;
  int from;
  int to;
  int transpose;
};

// use this to choose where to listen to midi from
MidiMap midimap(int channel);
MidiMap midimap(int channel, int from, int to);
MidiMap midimap(int channel, int from, int to, int transpose);


// below are channel and note defines so we can be a bit more descriptive in our declarations

#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3
#define CHANNEL_5 4
#define CHANNEL_6 5
#define CHANNEL_7 6
#define CHANNEL_8 7
#define CHANNEL_9 8
#define CHANNEL_10 9
#define CHANNEL_11 10
#define CHANNEL_12 11
#define CHANNEL_13 12
#define CHANNEL_14 13
#define CHANNEL_15 14
#define CHANNEL_16 15


#define mC0  12
#define mCx0 13
#define mD0  14
#define mDx0 15
#define mE0  16
#define mF0  17
#define mFx0 18
#define mG0  19
#define mGx0 20
#define mA0  21
#define mAx0 22
#define mB0  23

#define mC1  24
#define mCx1 25
#define mD1  26
#define mDx1 27
#define mE1  28
#define mF1  29
#define mFx1 30
#define mG1  31
#define mGx1 32
#define mA1  33
#define mAx1 34
#define mB1  35

#define mC2  36
#define mCx2 37
#define mD2  38
#define mDx2 39
#define mE2  40
#define mF2  41
#define mFx2 42
#define mG2  43
#define mGx2 44
#define mA2  45
#define mAx2 46
#define mB2  47


#define mC3  48
#define mCx3 49
#define mD3  50
#define mDx3 51
#define mE3  52
#define mF3  53
#define mFx3 54
#define mG3  55
#define mGx3 56
#define mA3  57
#define mAx3 58
#define mB3  59


#define mC4  60
#define mCx4 61
#define mD4  62
#define mDx4 63
#define mE4  64
#define mF4  65
#define mFx4 66
#define mG4  67
#define mGx4 68
#define mA4  69
#define mAx4 70
#define mB4   71



#define mC5  72
#define mCx5 73
#define mD5  74
#define mDx5 75
#define mE5  76
#define mF5  77
#define mFx5 78
#define mG5  79
#define mGx5 80
#define mA5  81
#define mAx5 82
#define mB5  83


#define mC6  84
#define mCx6 85
#define mD6  86
#define mDx6 87
#define mE6  88
#define mF6  89
#define mFx6 90
#define mG6  91
#define mGx6 92
#define mA6  93
#define mAx6 94
#define mB6  95


#define mC7  96
#define mCx7 97
#define mD7  98
#define mDx7 99
#define mE7  100
#define mF7  101
#define mFx7 102
#define mG7  103
#define mGx7 104
#define mA7  105
#define mAx7 106
#define mB7  107


#define mC8  108
#define mCx8 109
#define mD8  110
#define mDx8 111
#define mE8  112
#define mF8  113
#define mFx8 114
#define mG8  115
#define mGx8 116
#define mA8  117
#define mAx8 118
#define mB8  119


#endif // MIDIMAP_H









