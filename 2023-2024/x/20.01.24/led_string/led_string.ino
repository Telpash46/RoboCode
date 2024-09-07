int leds[8] = {9, 5, 3, 2, 4, 6, 8, 7};
void setup() {
Serial.begin(9600);

for (int i=2; i<10; i++) {
   pinMode(i, OUTPUT);
   
}
}

void loop() {
  
  for (int c=1; c<9; c++) {
    digitalWrite(leds[c], HIGH);
    delay(500);  
    digitalWrite(leds[c], LOW);
    delay(500);  
  }




  }
