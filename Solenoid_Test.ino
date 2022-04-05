int sig = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(sig, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(sig, HIGH);
  delay(500);
  digitalWrite(sig, LOW);
  delay(500);
}
