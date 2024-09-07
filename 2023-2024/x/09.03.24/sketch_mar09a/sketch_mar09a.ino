#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;
int x = 1, y = 0;
int dirX, dirY;
const int DELAY = 300;
int AppleX, AppleY;
int blocks = 1;

void setup() {
  // put your setup code here, to run once:
  gb.begin(2);
  Serial.begin(9600);
  generateApple();
}

void makeMove() {
  switch (gb.getKey()) {
    case 4:
      x = -1;
      y = 0;
      break;
    case 5:
      x = 1;
      y = 0;
      break;
    case 6:
      y = 1;
      x = 0;
      break;
    case 3:
      y = -1;
      x = 0;
      break;
    default:
      break;
  }
}

void generateApple() {
  randomSeed(analogRead(A0));
  gb.wipePoint(AppleX, AppleY);
  AppleX = random(0, 7);
  AppleY = random(0, 15);
}

void DrawBlocks() {
  if (x == 1 && y == 0) {
    for (int i = 0; i < blocks; i++) {
      gb.drawPoint(dirX - i, dirY); 
    }
  }

  if (x == -1 && y == 0) {
    for (int i = 0; i <= blocks; i++) {
      gb.drawPoint(dirX + i, dirY);
      gb.wipePoint(dirX + i, dirY); 
    }
  }

  if (x == 0 && y == 1) {
    for (int i = 0; i < blocks; i++) {
      gb.drawPoint(dirX, dirY - i); 
    }
  }

  if (x == 0 && y == -1) {
    for (int i = 0; i < blocks; i++) {
      gb.drawPoint(dirX, dirY + i); 
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  makeMove();
  dirX = dirX + x;
  dirY = dirY + y;
  if (dirX > 7) dirX = 0;
  if (dirX < 0) dirX = 7;
  if (dirY > 15) dirY = 0;
  if (dirY < 0) dirY = 15;
  gb.clearDisplay();
  // gb.drawPoint(dirX, dirY);
  DrawBlocks();
  gb.drawPoint(AppleX, AppleY);
  if (dirX == AppleX && dirY == AppleY) {   
    generateApple();
    gb.drawPoint(AppleX, AppleY);
    blocks += 1;
  }
  delay(DELAY);  
}
