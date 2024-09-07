#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;
int x = 1, y = 0;
int dirX, dirY;
const int DELAY = 300;
const int X_MIN = 0;
const int Y_MIN = 0;
const int X_MAX = 7;
const int Y_MAX = 15;
int AppleX;
int AppleY;
//int snakeX[10];
//int snakeY[10];
int snakeX[8];
int snakeY[16];
const int up = 1;
const int right = 2;
const int bottom = 3;
const int left = 4;
int direction = right;
int lenSnake = 1;
bool state;


void setup() {
  // put your setup code here, to run once:
  gb.begin(2);  
  randomSeed(analogRead(2));
  Serial.begin(9600);
  generateApple();
  snakeX[0] = 4;
  snakeY[0] = 7;

}

void makeMove() {
  switch (gb.getKey()) {
    case 4:
      if (direction != right) {
        direction = left;
      }
      break;
    case 5:
      if (direction != left) {
        direction = right;
      }
      break;
    case 6:
      if (direction != up) {
        direction = bottom;
      }
      break;
    case 3:
      if (direction != bottom) {
        direction = up;
      }
      break;
    default:
      break;
  }
}

boolean isPartOfSnake (int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}

void generateApple() {
  gb.wipePoint(AppleX, AppleY);
  AppleX = random(X_MIN, X_MAX);
  AppleY = random(Y_MIN, Y_MAX);
  while (isPartOfSnake(AppleX, AppleY)) {
    AppleX = random(X_MIN, X_MAX);
    AppleY = random(Y_MIN, Y_MAX);
  }
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
      if (direction != bottom) {
        if (snakeY[0] == 0) {
          snakeY[0] = Y_MAX;
        } else {
          snakeY[0]--;
        }
      }
      break;
    case bottom:
      if (direction != up) {
        if (snakeY[0] == Y_MAX) {
          snakeY[0] = Y_MIN;
        } else {
          snakeY[0]++;
        }
      }
      break;
    case left:
      if (direction != right) {
        if (snakeX[0] == 0) {
          snakeX[0] = X_MAX;
        } else {
          snakeX[0]--;
        }
      }
      break;
    case right:
      if (direction != left) {
        if (snakeX[0] == X_MAX) {
          snakeX[0] = X_MIN;
        } else {
          snakeX[0]++;
        }
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


void drawFruit() {
  state = !state;
  if (state == true) {
    gb.drawPoint(AppleX, AppleY);
  } else {
    gb.wipePoint(AppleX, AppleY);
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:
//  if (lenSnake >= 10) {
//    fail();
//  }
  for (int s = 1; s < lenSnake; s++) {
    if (snakeX[0] == snakeX[s] && snakeY[0] == snakeY[s]) {
      fail();
    }
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
  drawFruit();
  
  if (snakeX[0] == AppleX && snakeY[0] == AppleY) {
    lenSnake += 1;
    gb.sound(SCORE);
    for (int a = 0; a < lenSnake; a++) {
      generateApple();
      
    }
    
    drawFruit();
  }
  delay(DELAY);
}

void fail() {
  gb.testMatrix(10);
  gb.sound(COLLISION);
  lenSnake = 1;
}

void victory() {
  gb.testMatrix(5);
  delay(1);
  gb.testMatrix(5);
  gb.sound(COLLISION);
  lenSnake = 1;
}
