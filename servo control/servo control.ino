#include <Servo.h>

Servo TowerPro;
int rotate;

void setup() {
  // put your setup code here, to run once:
  TowerPro.attach(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(rotate = 0; rotate < 180; rotate++ ){
    TowerPro.write(rotate);
    delay(15);
  }

  for(rotate = 180; rotate > 0; rotate-- ){
    TowerPro.write(rotate);
    delay(15);
  }
}
