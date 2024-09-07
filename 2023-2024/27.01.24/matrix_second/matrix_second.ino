#include <LedControl.h>

int matr[8][8];
LedControl lc = LedControl(12, 11, 10, 1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8); // максимум яркость 16
  lc.clearDisplay(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, 1);
      delay(100);
    }
  }
}
