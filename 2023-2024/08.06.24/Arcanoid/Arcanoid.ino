#include <GameBoy.h>
#include "Blocks.h"
GameBoy gb;

int paddleX = 3;
int paddleY = 14;
int directionX = 1;
int directionY = -1;
int ballX = 3;
int ballY = 14;
bool stateLevel = true;
int numLevel = 1;

void setup() {
  // put your setup code here, to run once:
  gb.begin(1);
  createLevel();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (loss()) {
    drawBricks(Block_level_1);
    paddleX = 3;
    paddleY = 14;
    directionX = 1;
    directionY = -1;
    ballX = 3;
    ballY = 14;
    gb.testMatrix(10);
    gb.sound(COLLISION);
  }
  ball();
  makePaddle();
  drawPaddle(paddle, paddleX, paddleY);
  //500
  delay(200);
  gb.drawDisplay();
}

void drawPaddle(byte arr[3], int x, int y) {
  for (int i = 0; i < 3; i++) {
    if (arr[i] == 1) {
      gb.drawPoint(x + i, y);
    }
  }
}


void makePaddle() {
  if (gb.getKey() == 4 && paddleX > 0) {
    paddleX--;
  } else if (gb.getKey() == 5 && paddleX < 5) {
    paddleX++;
  }
}

void checkCollision() {
  if (ballX <= 0 || ballX >= 7) directionX = -directionX;
  if (ballY <= 0 || ballY >= 15) directionY = -directionY;

  if (ballY == paddleY - 1 && ballX >= paddleX && ballX <= paddleX + 3) {
    directionY = -1;
  }

  if (gb.checkCollision(ballX, ballY)) {
    gb.wipePoint(ballX, ballY);
    directionY = 1;
    gb.sound(SCORE);
  }
}

void ball() {
  ballX += directionX;
  ballY += directionY;
  checkCollision();
  gb.drawPoint(ballX, ballY);
}

void drawBricks(byte arr[3][8]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      if (arr[i][j] == 1) {
        gb.memDisplay(j, i);
      }
    }
  }
}

bool loss() {
  if (ballY >= 15) {
    Serial.println(1233);
    return true;
  }
  return false;
}


void memClear() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      gb.display[j][i] = 0;
    }
  }
}
