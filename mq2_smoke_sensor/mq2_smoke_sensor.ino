#define MQ2pin 0
#define LED 8

float sensorValue;

void setup()
{
  Serial.begin(9600); 
  pinMode(LED, OUTPUT);
  Serial.println("Warming up fo 20 seconds...");
  delay(20000); 
}

void loop()
{
  sensorValue = analogRead(MQ2pin);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  if(sensorValue > 300)
  {
    Serial.print(" | Combustible/Smoke is Detected");
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
  }
  
  Serial.println("");
  delay(2000); 
}
