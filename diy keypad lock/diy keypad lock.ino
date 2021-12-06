#include <Keypad.h>
#include <Servo.h>

Servo TP;

const int button1Pin = 10;
const int LEDPin = 11;
const int servoPin = 12;
int button1State = 0;
int button2State = 0;
const int buzzerPin = 13;

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
 
const char password= '1234';
char input;

void verify(char input){
  if(input == password){
    Serial.println("Password is correct");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(LEDPin, HIGH);
    delay(500); 
    digitalWrite(buzzerPin, LOW);
    digitalWrite(LEDPin, LOW);
    TP.write(180);
    delay(5000);
    TP.write(0);
    Serial.println("Locking");
  }else{
    TP.write(0);          
  }
}

void setup(){
  Serial.begin(9600);
  TP.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
}
 
void loop(){
    button1State = digitalRead(button1Pin);
    char customKey = customKeypad.getKey();

    if(customKey){
      input = customKey;
      Serial.print(customKey);
      Serial.println("");
      verify(input);
    }else{
      TP.write(0);
    }
    
}