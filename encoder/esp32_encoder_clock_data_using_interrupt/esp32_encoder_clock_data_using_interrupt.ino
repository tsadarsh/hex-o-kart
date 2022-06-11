#define A 21
#define B 19
int counterA = 0;
int counterB = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A), incA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B), incB, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("A: ");
  Serial.println(counterA);
  Serial.print("B: ");
  Serial.println(counterB);
  delay(100);
}

void incA() {
  counterA++;
}

void incB() {
  counterB++;
}