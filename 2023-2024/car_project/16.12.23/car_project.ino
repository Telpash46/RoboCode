#include <SoftwareSerial.h>

const int BIN2 = 5;
const int BIN1 = 6;
const int AIN1 = 9;
const int AIN2 = 10;
const int SENSOR_LEFT = 12;
const int SENSOR_RIGHT = 11;

int carSpeed = 255;

bool lineStatus = false;

SoftwareSerial bt(2, 3);

void forward();
void stp();
void left();
void right();

void setup() {
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);
  bt.begin(9600);
  Serial.begin(9600);

}

void loop() {
    if (bt.available()) {
      int value = bt.read();
      Serial.println(String(value));
      if (value == 70) {
        forward();
      } 
      if (value == 83) {
        stp();
      }
      if (value == 66) {
        backward();
      }
      if (value == 76) {
        left();
      }
      if (value == 82) {
        right();
      }
      if (value == 88) {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      if (value == 120) {
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (value == 119) {
        lineStatus = false;
      }
if (value == 87) {
  lineStatus = true;
}
    }


 if (lineStatus) {
   if (digitalRead(SENSOR_RIGHT) == HIGH && digitalRead(SENSOR_LEFT) == HIGH) {
    forward();
    Serial.println(1);
    
  }
  if (digitalRead(SENSOR_LEFT) == HIGH) {
    left();
    Serial.println(2);
  }
  if (digitalRead(SENSOR_RIGHT) == HIGH) {
    
    right();
    Serial.println(3);
  }
  if (digitalRead(SENSOR_RIGHT) == LOW && digitalRead(SENSOR_LEFT) == LOW) {
    forward();
    Serial.println(4);
  }
 }




//  digitalWrite(BIN2, LOW);
//  analogWrite(BIN1, carSpeed);
//  analogWrite(AIN1, carSpeed);
//  digitalWrite(AIN2, LOW);
  
 // Serial.print("Left: " + String(digitalRead(SENSOR_LEFT)));
 // Serial.println(", Right: " + String(digitalRead(SENSOR_RIGHT)));
}

void forward() {
  analogWrite(BIN2, carSpeed);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, carSpeed);
}





void backward() {

  digitalWrite(5, LOW);
  analogWrite(6, carSpeed);
  analogWrite(9, carSpeed);
  digitalWrite(10, LOW);
}
void stp() {
  digitalWrite(BIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
}

void right() {
  digitalWrite(BIN2, LOW);
  analogWrite(BIN1, carSpeed);
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, carSpeed);
}

void left() {
  analogWrite(BIN2, carSpeed);
  digitalWrite(BIN1, LOW);
  analogWrite(AIN1, carSpeed);
  digitalWrite(AIN2, LOW);
}
