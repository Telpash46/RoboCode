#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 1);

const int BTN_UP = 2;
const int BTN_DOWN = 3;
const int BTN_RIGHT = 4;
const int BTN_LEFT = 5;
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

int LEFT_KEY() {
  if (digitalRead(BTN_LEFT)) {
    return 1;
  }
  return 0;
}

int RIGHT_KEY() {
  if (digitalRead(BTN_RIGHT)) {
    return 1;
  }
  return 0;
}

int DOWN_KEY() {
  if (digitalRead(BTN_DOWN)) {
    return 1;
  }
  return 0;
}

int UP_KEY() {
  if (digitalRead(BTN_UP)) {
    return 1;
  }
  return 0;
}


void right() {
  if (RIGHT_KEY() == 1) {
    x += 1;
    delay(250);
    lc.setLed(0, x - 1, y, 0);
    Serial.print(x);
    Serial.println(y);
    if (x > 7) {
      x = 0;
      
    }
  }
}

void left() {
  if (LEFT_KEY() == 1) {
    x -= 1;
    delay(250);
    lc.setLed(0, x + 1, y, 0);
    Serial.print(x);
    Serial.println(y);
    if (x < 0) {
      x = 7;
      
    }
  }
}

void up() {
  if (UP_KEY() == 1) {
    y -= 1;
    delay(250);
    lc.setLed(0, x, y + 1, 0);
    Serial.print(x);
    Serial.println(y);
      if (y < 0) {
        y = 7;
      }
  }
}

void down() {
  if (DOWN_KEY() == 1) {
    y += 1;
    delay(250);
    lc.setLed(0, x, y - 1, 0);
    Serial.print(x);
    Serial.println(y);
      if (y > 7) {
        y = 0;
      }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  right();
  left();
  up();
  down();
  lc.setLed(0, x, y, 1);
}
