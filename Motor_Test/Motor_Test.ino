int reverseSwitch = 2;

int CLOCK1 = 10;
int DIR1 = 9;
int CLOCK2 = 7;
int DIR2 = 6;

int stepCount = 0;
int cycleCount = 0;
int stepsPerRev = 2000;

int angleIndex = 15;
int stepsIndex = 360/angleIndex;

int anglePoly = 1;
int stepsPoly = stepsPerRev/anglePoly;

int rpm = 60;

float delay_time = 60L * 1000L * 1000L / stepsPerRev / rpm;

boolean setdir = LOW; // Set Direction


// Interrupt Handler
//void revmotor () {
//  setdir = !setdir;
//}

void setup() {
  pinMode(CLOCK1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(CLOCK2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(reverseSwitch), revmotor, FALLING);

  Serial.begin(9600);
}

int i = 0;
unsigned long start = 0;
unsigned long endTime = 0;
void loop() {
  start = micros();
//  p = analogRead(A0);
//  delay_time = map(p, 0, 1023, 100, 1500);

  for (; i < stepsIndex; i++)
  {
    StepForward(delay_time);
    StepForward180(delay_time);
    
    stepCount += 1;
    cycleCount += 1;

    Serial.println(stepCount);
    Serial.println(cycleCount);
  }

  endTime = micros() - start;

  Serial.println(endTime);
  delay(stepsPerRev);
}



void StepForward(float delay_time)
{
  digitalWrite(DIR1, LOW);
  for (int i = 0; i < 1; i++)
  {
    for (int x = 0; x < stepsPerRev / stepsIndex; x++)
    {
      digitalWrite(CLOCK1, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK1, LOW);
      delayMicroseconds(delay_time);
      stepCount+1;
    }
    delay(delay_time);
  }
}

void StepForward180(float delay_time)
{
  digitalWrite(DIR2, LOW);
  for (int i = 0; i < 1; i++)
  {
    for (int x = 0; x < stepsPoly; x++)
    {
      digitalWrite(CLOCK2, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK2, LOW);
      delayMicroseconds(delay_time);
    }
    delay(delay_time);
  }
  digitalWrite(DIR2, HIGH);
  for (int i = 1; i < 2; i++)
  {
    for (int x = 0; x < stepsPoly; x++)
    {
      digitalWrite(CLOCK2, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(CLOCK2, LOW);
      delayMicroseconds(delay_time);
      cycleCount+1;
    }
    delay(delay_time);
  }
}
