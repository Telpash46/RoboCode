#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;
int x = 1, y = 0;
int dirX, dirY;
const int DELAY = 300;
int AppleX, AppleY;
int snakeX[10];
int snakeY[10];
const int up = 1;
const int right = 2;
const int bottom = 3;
const int left = 4;
int direction = right;
int lenSnake = 1;

void setup() {
  // put your setup code here, to run once:
  gb.begin(2);
  Serial.begin(9600);
  generateApple();
  snakeX[0] = 4;
  snakeY[0] = 7;
}

void makeMove() {
  switch (gb.getKey()) {
    case 4:
      direction = left;
      break;
    case 5:
      direction = right;
      break;
    case 6:
      direction = bottom;
      break;
    case 3:
      direction = up;
      break;
    default:
      break;
  }
}

void generateApple() {
  gb.wipePoint(AppleX, AppleY);
  randomSeed(analogRead(A0));
  AppleX = random(0, 7);
  randomSeed(analogRead(A0));
  AppleY = random(0, 15);
}

//void DrawBlocks() {
//  if (x == 1 && y == 0) {
//    for (int i = 0; i < blocks; i++) {
//      gb.drawPoint(dirX - i, dirY);
//    }
//  }
//
//  if (x == -1 && y == 0) {
//    for (int i = 0; i <= blocks; i++) {
//      gb.drawPoint(dirX + i, dirY);
//      gb.wipePoint(dirX + i, dirY);
//    }
//  }
//
//  if (x == 0 && y == 1) {
//    for (int i = 0; i < blocks; i++) {
//      gb.drawPoint(dirX, dirY - i);
//    }
//  }
//
//  if (x == 0 && y == -1) {
//    for (int i = 0; i < blocks; i++) {
//      gb.drawPoint(dirX, dirY + i);
//    }
//  }
//}


void move() {
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  switch (direction) {
    case up:
      if (snakeY[0] == 0) {
        snakeY[0] = 15;
      } else {
        snakeY[0]--;
      }
      break;
    case bottom:
      if (snakeY[0] == 15) {
        snakeY[0] = 0;
      } else {
        snakeY[0]++;
      }
      break;
    case left:
      if (snakeX[0] == 0) {
        snakeX[0] = 7;
      } else {
        snakeX[0]--;
      }
      break;
    case right:
      if (snakeX[0] == 7) {
        snakeX[0] = 0;
      } else {
        snakeX[0]++;
      }
      break;
    default:
      break;
  }
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(snakeX[9]);
  if (lenSnake >= 10) {
    fail();
  }
  makeMove();
  //  dirX = dirX + x;
  //  dirY = dirY + y;
  //  if (dirX > 7) dirX = 0;
  //  if (dirX < 0) dirX = 7;
  //  if (dirY > 15) dirY = 0;
  //  if (dirY < 0) dirY = 15;
  gb.clearDisplay();
  //  gb.drawPoint(dirX, dirY);
  move();
  drawSnake();
  //DrawBlocks();
  gb.drawPoint(AppleX, AppleY);
  if (snakeX[0] == AppleX && snakeY[0] == AppleY) {
    lenSnake += 1;
    gb.sound(SCORE);
    generateApple();
    gb.drawPoint(AppleX, AppleY);
  }
  delay(DELAY);
}

void fail() {
  gb.testMatrix(10);
  gb.sound(COLLISION);
  lenSnake = 1;
}
