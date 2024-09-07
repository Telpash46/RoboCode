#include <GameBoy.h>
#include "Blocks.h"
#include <stdlib.h> // Для использования rand()
GameBoy gb;

int paddleX = 3;
int paddleY = 14;
int directionX = 1;
int directionY = -1;
int ballX = 3;
int ballY = 14;
bool stateLevel = true;
int numLevel = 1;
int countBricks = 0;
int score = 0;

void setup() {
  // put your setup code here, to run once:
  gb.begin(1);
  Serial.begin(9600);
  createLevel();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (win()) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
        gb.setLed(i, j, WIN[j][i]);
      }
    }
    delay(2000);
    restart();
  }
  if (loss()) {
    //drawBricks(Block_level_1);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
      }
    }
    restart();
    gb.testMatrix(10);
    //gb.sound(COLLISION);
  }
  ball();
  makePaddle();
  drawPaddle(paddle, paddleX, paddleY);
  //500
  if (gb.getKey() == 6) {
    delay(50);
  } else if (gb.getKey() == 3) {
    delay(500);
  } else {
    delay(200);
  }
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
  if (ballY <= 0) {
    directionY = -directionY;
    directionX = (rand() % 2 == 0) ? 1 : -1;
  }

  if (ballY >= 15) {
    directionY = -directionY;
  }

  if (ballY == paddleY - 1 && ballX >= paddleX && ballX <= paddleX + 2) {
    directionY = -1;
    if (ballX == paddleX) {
      directionX = -1;
    } else if (ballX == paddleX + 1) {
      directionX = 0;
    } else if (ballX == paddleX + 2) {
      directionX = 1;
    }
  }

  if (gb.checkCollision(ballX, ballY)) {
    gb.wipePoint(ballX, ballY);
    directionY = 1;
    //gb.sound(SCORE);
    score++;
    directionX = (rand() % 2 == 0) ? 1 : -1;
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
        countBricks++;
      }
    }
  }
}

bool loss() {
  if (ballY >= 15) {
    Serial.println("You loss the game");
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

void createLevel() {
  memClear();
  if (stateLevel) {
    gb.clearDisplay();
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 8; j++) {
        randomSeed(analogRead(0) + analogRead(5));
        int buffrand = random(1, 11);
        if (buffrand < 5) {
          buffLevel[i][j] = 0;
        } else {
          buffLevel[i][j] = 1;
        }

      }
    }
    drawBricks(buffLevel);
    stateLevel = false;
  }
}

void restart() {
  stateLevel = true;
  createLevel();
  paddleX = 3;
  paddleY = 14;
  directionX = 1;
  directionY = -1;
  ballX = 3;
  ballY = 14;
  score = 0;
}


bool win() {
  if (score >= countBricks) {
    return true;
  }
  return false;
}
