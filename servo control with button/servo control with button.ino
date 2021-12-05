#include <Servo.h>

Servo TP;

const int buttonPin = 2;
const int servoPin = 3;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  TP.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH){
    TP.write(180);
  }else{
    TP.write(0);
  }
}
