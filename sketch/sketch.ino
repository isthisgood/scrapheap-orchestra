
/* 
 Stepper Motor Control - one step at a time
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.
 
 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.
 
 Created 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                                     // for your motor

// Constants for the Motor Shield R3:
const int DirA = 12;
const int DirB = 13;
const int pwmA = 4;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int SenseA = 0;
const int SenseB = 1;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, DirA, DirB);            

// Set this based on your stepper motor
// And whatever its attached to
const int MaxStepperSpeed = 500;
const int MinStepperPos = 0;
const int MaxStepperPos = 255;

int CurStep = 0;

float fs1 = 1000.0 / 46.25;
float g1 = 1000.0 / 49.00;
float gs1 = 1000.0 / 51.91;
float as1 = 1000.0 / 58.27;
float b1 = 1000.0 / 61.74;
float c2 = 1000.0 / 65.41;
float cs2 = 1000.0 / 69.30;
//f1 1000 / 46.65 22.90957 
//g1 1000 / 49.00
//c2

const int NUM_NOTES = 120;

int notes[NUM_NOTES] = {fs1, fs1, fs1, fs1, fs1, fs1, fs1, fs1, gs1, fs1, gs1, as1, cs2, cs2, cs2, cs2, cs2, cs2, b1, 
  as1, gs1, gs1, gs1, gs1, fs1, fs1, fs1, fs1, fs1, fs1, fs1, fs1, gs1, fs1, gs1, as1, cs2, cs2, cs2, cs2, cs2, b1, as1, gs1, gs1, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, cs2, as1, b1, cs2, cs2, b1, as1, gs1, fs1};
int lengths[NUM_NOTES] = {2, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 11, 1, 1, 2, 2, 2, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 2, 4, 1, 1, 10, 1, 1, 4, 2, 2, 2, 2, 2, 8, 1, 1, 1, 3, 2, 1, 1, 2, 2, 2, 2, 2, 4, 1, 1, 6, 2, 2, 2, 12, 8};

int currentNote = 0;

float test = 1;

int reverse = 1;

void setup()
{
  Serial.begin(9600);

  // PWM to High to disable use
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);


  // Brakes off to disable use
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  
  attachInterrupt(0, goForward, RISING);
  attachInterrupt(1, goBackward, RISING);
  
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  
  //myStepper.step(-1000);
  // Stepper motor speed
  //myStepper.setSpeed(MaxStepperSpeed);

  //Force stepper home, max, home then to center
  //myStepper.step(0);
  /*myStepper.step(MaxStepperPos);
  myStepper.step(-MaxStepperPos);
  CurStep = (MaxStepperPos-MinStepperPos)/2;
  myStepper.step(CurStep);*/
}

void loop()
{

  if (currentNote < NUM_NOTES)
  {
    //myStepper.setStepDelay(notes[currentNote] * 1e2 * 1);
    myStepper.setStepDelay(notes[currentNote] * 3e2 * 1);
    myStepper.step(reverse * lengths[currentNote] * 1730 / notes[currentNote]);    
  }
  currentNote++;// = (currentNote + 1) % NUM_NOTES; 
  delay(10);
  
  //reverse = -reverse;

}

void goForward()
{
  reverse = 1;
  myStepper.reverseSteps(1);
  //Serial.println("forward");
}

void goBackward()
{
  reverse = -1;
  myStepper.reverseSteps(0);
  //Serial.println("backward");
}

/*
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    reverse = -reverse; 
    Serial.read();
  }
}
*/

