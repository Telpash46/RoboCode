void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i=2; i<10; i++) {
    pinMode(i, OUTPUT);
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int r;
  randomSeed(analogRead(0) + analogRead(1));
  for (int x=2; x<10; x++) {
    digitalWrite(x, HIGH);
  }

  for (int c=2; c<10; c++) {
    r = random(2,9);
    Serial.println(r);
    digitalWrite(r, LOW);
    delay(500);
    digitalWrite(r, HIGH);
    delay(500);
  }
}
