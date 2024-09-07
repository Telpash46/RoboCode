#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bt(3, 2); //rx, tx
int data = 0;
Servo servo_pin_8;

void setup()
{
  bt.begin(9600);
  servo_pin_8.attach(8);

}

void loop()
{
  if (bt.available())
  {
    data = bt.available();
  }
  if (data == 49)
  {
    servo_pin_8.write( 180 );
  }
  if (data == 50)
  {
    servo_pin_8.write( 0 );
  }
}
