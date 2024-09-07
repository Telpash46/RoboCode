#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 1);

int right = 3;
int x, y = 0;

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);
  Serial.begin(9600);
  
}

void X() {
  lc.setRow(0, 0, B10000001);
  lc.setRow(0, 1, B01000010);
  lc.setRow(0, 2, B00100100);
  lc.setRow(0, 3, B00011000);
  lc.setRow(0, 4, B00011000);
  lc.setRow(0, 5, B00100100);
  lc.setRow(0, 6, B01000010);
  lc.setRow(0, 7, B10000001);
}

int keys() {
  if (digitalRead(right)) {
    return 1;
  }
  return 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (keys() == 1) {
    x += 1;
    delay(250);
    lc.setLed(0, x - 1, y, 0);
    if (x > 7) {
      x = 0;
      y += 1;
      if (y > 7) {
        y = 0;
        x = 0;
      }
    }
  }
  
  lc.setLed(0, x, y, 1);
}
