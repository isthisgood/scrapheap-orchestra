
int steps = 0;
int stepDir = LOW;
int currentState = LOW;

const int DIR_PIN = 6;
const int STEP_PIN = 9;

void setup()
{
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(STEP_PIN, LOW);
}

void loop()
{
  doStep();
  delay(50);
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
