#include <Keypad.h>
#include <Servo.h>

Servo TP;

const int button1Pin = 10;
const int button2Pin = 11;
const int servoPin = 12;
int button1State = 0;
int button2State = 0;

const byte ROWS = 4;
const byte COLS = 4; 
 
char hexaKeys[ROWS][COLS] = {
  {'D','#','7','3'},
  {'C','*','6','2'},
  {'B','9','5','1'},
  {'A','8','4','0'}
};
 
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
const char password= "1234";
char input;

void password(){
  Serial.println("Enter Password:");
    char customKey = customKeypad.getKey();
    if(customKey){
        
        Serial.println(customKey);
        input = customKey;
        if(input == password){
          TP.write(180);
        }else{
          TP.write(0);          
        }
    }
}

void setup(){
  Serial.begin(9600);
  TP.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  pinMode(button1Pin, INPUT);
}
 
void loop(){
  button1State = digitalRead(button1Pin);

  if(button1State == HIGH){
    
  }else{
    TP.write(0);
  }
}