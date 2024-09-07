
int arr[3][2] = {};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0) + analogRead(A1) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead(A5));
  for (int i = 0; i < 3; i++) {
    for (int c = 0; c < 2; c++) {
      arr[i][c] = random();
    }
  }

Serial.println("Your generated matrix");
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 2; y++) {
      Serial.print(arr[x][y]);
      Serial.print("        ");
    }
    Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
