//#include <MIDI.h>
#include <SoftwareSerial.h>


int LED = 13;
int rxPin = 10;
int txPin = 11;
//SoftwareSerial mySerial(rxPin, txPin); // RX, TX


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  //mySerial.begin(31250);
  Serial.begin(31250);
}

void loop() {
 int b = Serial.read();
 if(b!=-1) {
    Serial.print(b, HEX);
    Serial.println();
    if(b==0x90) {
      digitalWrite(LED, HIGH);
    } else if(b==0) {
      digitalWrite(LED, LOW);
    }
 }
 delay(3);
}
