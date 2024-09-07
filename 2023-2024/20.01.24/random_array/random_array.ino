int arr[6];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
  randomSeed(analogRead(0) + analogRead(1));
  for (int i=0; i<6; i++) {
    arr[i] = random(0, 10);
  }

  for (int c=0; c<6; c++) {
    Serial.print(arr[c]);
  }
  
  Serial.println();
  delay(200);
}
