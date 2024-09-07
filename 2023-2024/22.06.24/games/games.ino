#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;

const int DELAY = 300;
const int X_MIN = 0;
const int Y_MIN = 0;
const int X_MAX = 7;
const int Y_MAX = 15;
const int SnakeVictory_LENGTH = 127;
const int up = 1;
const int right = 2;
const int bottom = 3;
const int left = 4;
const int BOARD_BRIGHTNESS = 2;
int modeCount = 0;
int AppleX;
int AppleY;
int x = 1, y = 0;
int dirX, dirY;
int snakeX[128];
int snakeY[128];
int direction = right;
int lenSnake = 1;
bool state;
bool MenuActivated = true;
int car_speed = 100;
int enemy_x = 2;
int mycar_x = 2;
int mycar_y = 12;
bool pause = false;
bool menuloop = true;
bool soundpermission = true;
int x = 2, y = -1;
int rot = 0;
int acc = 1;
int speed = 200;
int score = 0;
int level = 0;

byte ARROWS[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

byte CAR[8][8] = {
  {0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 1, 0}
};

byte SNAKE[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};

byte TETRIS[8][8] = {
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

byte ARCANOID[8][8] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};


void setup() {
  // put your setup code here, to run once:

  gb.begin(BOARD_BRIGHTNESS);
  randomSeed(analogRead(2) + analogRead(5));
  Serial.begin(9600);
  SnakeGenerateApple();
  snakeX[0] = 4;
  snakeY[0] = 7;
}

void SnakeMakeSnakeMove() {
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

boolean SnakeisPartOfSnake (int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}

void SnakeGenerateApple() {
  gb.wipePoint(AppleX, AppleY);
  AppleX = random(X_MIN, X_MAX);
  AppleY = random(Y_MIN, Y_MAX);
  while (SnakeisPartOfSnake(AppleX, AppleY)) {
    AppleX = random(X_MIN, X_MAX);
    AppleY = random(Y_MIN, Y_MAX);
  }
}



void SnakeMove() {
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

void SnakeDrawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}


void SnakeDrawFruit() {
  state = !state;
  if (state == true) {
    gb.drawPoint(AppleX, AppleY);
  } else {
    gb.wipePoint(AppleX, AppleY);
  }
}

int modeSelector() {
  if (gb.getKey() == 4) {
    modeCount++;
    delay(250);
    if (modeCount > 3) {
      modeCount = 0;
    }
  }
  if (gb.getKey() == 5) {
    modeCount--;
    delay(250);
    if (modeCount < 0) {
      modeCount = 3;
    }
  }

  return modeCount;
}

void mainMenu() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[j][i]);
    }
  }

  switch (modeSelector()) {
    case 0:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, 8 + j);
          gb.setLed(i, 8 + j, CAR[j][i]);
        }
      }



      break;
    case 1:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, 8 + j);
          gb.setLed(i, 8 + j, SNAKE[j][i]);
        }
      }
      break;

    case 2:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, 8 + j);
          gb.setLed(i, 8 + j, TETRIS[j][i]);
        }
      }
      break;
    case 3:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, 8 + j);
          gb.setLed(i, 8 + j, ARCANOID[j][i]);
        }
      }
      break;
  }

  if (gb.getKey() == 1) {
    MenuActivated = false;
  }

  if (gb.getKey() == 2) {
    if (soundpermission) {
      gb.sound(SCORE);
      soundpermission = false;
    } else {
      gb.sound(COLLISION);
      soundpermission = true;
    }
  }
}

void loop() {
  if (MenuActivated) {
    menuloop = true;
    if (pause == true) {
      pause = false;
    }
    mainMenu();
  }
  else {
    if (modeCount == 1) {
      gameSnake();
    } else if (modeCount == 0) {
      gb.clearDisplay();
      car_speed = 100;
      playerCar(mycar_x, mycar_y);
      mainRacing();
    } else if (modeCount == 2) {
      randomSeed(analogRead(0) + analogRead(5));
      TetrisCreateBlock(random(0,  7));
    }
  }
}

void gameSnake() {
  if (lenSnake == SnakeVictory_LENGTH) {
    SnakeVictory();
  }

  for (int s = 1; s < lenSnake; s++) {
    if (snakeX[0] == snakeX[s] && snakeY[0] == snakeY[s]) {
      SnakeFail();
    }
  }
  SnakeMakeSnakeMove();

  gb.clearDisplay();

  if (pause == false) {
    SnakeMove();
  }
  SnakeDrawSnake();

  SnakeDrawFruit();

  if (snakeX[0] == AppleX && snakeY[0] == AppleY) {
    lenSnake += 1;
    if (soundpermission) {
      gb.sound(SCORE);
    }
    for (int a = 0; a < lenSnake; a++) {
      SnakeGenerateApple();

    }

    SnakeDrawFruit();
  }


  if (gb.getKey() == 2) {
    lenSnake = 1;
    MenuActivated = true;
  }

  if (gb.getKey() == 1 && !menuloop) {
    pause = !pause;
  }

  delay(DELAY);
  menuloop = false;
}


void SnakeFail() {
  gb.testMatrix(10);
  if (soundpermission) {
    gb.sound(COLLISION);
  }
  lenSnake = 1;
}

void SnakeVictory() {
  gb.testMatrix(5);
  delay(1);
  gb.testMatrix(5);
  if (soundpermission) {
    gb.sound(COLLISION);
  }
  lenSnake = 1;
}





bool Collision (int mycar_x, int mycar_y, int enemy_car_x, int enemy_car_y) {
  if (mycar_y == enemy_car_y and mycar_x == enemy_car_x) {
    return true;
  }
  if (mycar_x == enemy_car_x and enemy_car_y > 12) {
    return true;
  }
  return false;
}


int UpdateEnemyPos () {

  randomSeed(analogRead(A5));

  int buff = random(1, 10);

  if (buff <= 5) {
    buff = 2;
  } else {
    buff = 5;
  }
  return buff;
}

void PlayerCarController () {
  //  switch (gb.getKey()) {
  //    case 4:
  //      ClearPlayerCar(5, 12);
  //      playerCar(2, 12);
  //      break;
  //
  //    case 5:
  //      ClearPlayerCar(2, 12);
  //      playerCar(5, 12);
  //      break;
  //
  //    default:
  //      break;
  //  }

  return;
}

void mainRacing () {


  enemy_x = UpdateEnemyPos();
  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {





    //PlayerCarController();




    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);
    enemyCar(enemy_x, enemy_y);

    if (gb.getKey() == 4) {
      mycar_x = 2;
      ClearPlayerCar(5, 12);
    } else if (gb.getKey() == 5) {
      mycar_x = 5;
      ClearPlayerCar(2, 12);
    }
    playerCar(mycar_x, mycar_y);
    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y)) {
      if (soundpermission) {
        gb.sound(COLLISION);
      }
      gb.testMatrix(10);
      gb.clearDisplay();
      car_speed = 100;
      return;
    }

    if (enemy_y > 14) {
      if (soundpermission) {
        gb.sound(SCORE);
      }
    }


    delay(car_speed);





    clearLine(enemy_y);
    clearLine(enemy_y + 5);
    clearLine(enemy_y + 10);
    clearLine(enemy_y + 15);
    clearLine(enemy_y - 5);
    clearLine(enemy_y - 10);
    clearLine(enemy_y - 15);

    ClearEnemyCar(enemy_x, enemy_y);
    if (car_speed > 4) {
      car_speed = car_speed - 1;
    }


  }


  if (gb.getKey() == 2) {
    MenuActivated = true;
  }

  menuloop = false;

}


void createLine (int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine (int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}





void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
}

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
}

void ClearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
}

void ClearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
  /*2, 6*/
}



bool TetrisLoss() {
  if (gb.checkBlockCollision(gb.block[rot], x, 0)) {
    return true;
  }
  else {
    return false;
  }
}



bool TetrisWin() {
  if (score >= 2) {
    return true;
  }
  return false;
}


void TetrisMakeMove() {
  if (gb.getKey() == 4) {
    if (!gb.checkBlockCollision(gb.block[rot], x - 1, y)) {
      x--;
    }
  }
  if (gb.getKey() == 5) {
    if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
      x++;
    }
  }
  if (gb.getKey() == 1) {
    if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
      if (rot == 3) {
        rot = 0;
      } else {
        rot++;
      }
    }
  }

  if (gb.getKey() == 6) {
    acc = 4;
  } else {
    acc = 1;
  }

}
