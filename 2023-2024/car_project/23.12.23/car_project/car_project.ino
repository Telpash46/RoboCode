#include <SoftwareSerial.h>


const int BIN2 = 5;
const int BIN1 = 6;
const int AIN1 = 9;
const int AIN2 = 10;
const int SENSOR_LEFT = 12;
const int SENSOR_RIGHT = 11;
int carSpeed = 255;
char value;
bool lineMode = false;

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

  if (lineMode) {
    lineFollowing();
  } else {
    if (bt.available()) {
      
      
      String ModeValue = String(bt.read());
    
      if (ModeValue == -1) {
        Serial.println("true");
      }
      Serial.println("!" + ModeValue);
      if (ModeValue == 70) {
        forward();
      }
      if (ModeValue == 83) {
        stp();
      }
      if (ModeValue == 66) {
        backward();
      }
      if (ModeValue == 76) {
        left();
      }
      if (ModeValue == 82) {
        right();
      }
      if (ModeValue == 65) { // A
        lineMode = true;
      }

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

int lineFollowing() {
  Serial.println("line following working");
  if (bt.available()) {
    char value = bt.read();
    Serial.println(value);
    if (value == 'M' or value == -1 or value == 'S') {
      Serial.println("TRUE");
      lineMode = false;
      stp();
      return 0;
    }
  }
  int leftLineTracker = digitalRead(SENSOR_LEFT);
  int rightLineTracker = digitalRead(SENSOR_RIGHT);

  if (leftLineTracker == HIGH && rightLineTracker == LOW) {
    //    forwardSmoothLeft();
    left();
    delay(50);
  }
  else if (leftLineTracker == LOW && rightLineTracker == HIGH) {
    //    forwardSmoothRight();
    right();
    delay(50);
  }
  else if (rightLineTracker == HIGH && leftLineTracker == HIGH) forward();
  else if (rightLineTracker == LOW && leftLineTracker == LOW) forward();
}
