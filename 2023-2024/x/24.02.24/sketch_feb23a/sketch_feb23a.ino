#include <Blocks.h>
#include <GameBoy.h>
GameBoy gb;

int car_speed = 100;
int enemy_x = 2;

int mycar_x = 2;
int mycar_y = 12;


void setup() {
  // put your setup code here, to run once:

  gb.begin(15);
  playerCar(mycar_x, mycar_y);
}


void loop() {

  // put your main code here, to run repeatedly:

  mainRacing();



  //GameOver();
}
// bool Collision (int mycar_x, int, mycar_y, int enemy_car_x, int enemy_car_y) {
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



    createLine(enemy_y);
    createLine(enemy_y + 5);
    createLine(enemy_y + 10);
    createLine(enemy_y + 15);
    createLine(enemy_y - 5);
    createLine(enemy_y - 10);
    createLine(enemy_y - 15);

    enemyCar(enemy_x, enemy_y);

    //PlayerCarController();
    if (gb.getKey() == 4) {
      mycar_x = 2;
      ClearPlayerCar(5, 12);
    } else if (gb.getKey() == 5) {
      mycar_x = 5;
      ClearPlayerCar(2, 12);
    }
    playerCar(mycar_x, mycar_y);
    if (Collision(mycar_x, mycar_y, enemy_x, enemy_y)) {
      gb.sound(COLLISION);
      gb.testMatrix(10);
      gb.clearDisplay();
      car_speed = 100;
      return;
    }

    if (enemy_y > 14) {
      gb.sound(SCORE);
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
