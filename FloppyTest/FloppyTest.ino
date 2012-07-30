
int steps = 0;
int stepDir = LOW;
int currentState = LOW;

const int DIR_PIN = A7;
const int STEP_PIN = A6;

void setup()
{
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  digitalWrite(DIR_PIN, stepDir);
  digitalWrite(STEP_PIN, currentState);
}

void loop()
{
  doStep();
  delay(10);
}

void doStep()
{
  //Switch directions if end has been reached
  if (steps > 157)
  {
    stepDir = HIGH;
    digitalWrite(DIR_PIN, stepDir);
  }
  else if (steps <= 0)
  {
    stepDir = LOW;
    digitalWrite(DIR_PIN, stepDir);
  }
  
  if (stepDir == HIGH) steps--;
  else steps++;
  
  //Pulse the control pin
  digitalWrite(STEP_PIN, currentState);
  currentState = ~currentState;
}
