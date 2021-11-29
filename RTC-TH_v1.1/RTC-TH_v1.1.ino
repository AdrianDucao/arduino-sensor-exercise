#include <dht.h>
#include <SPI.h> //sd
#include <SD.h> //sd 
#include <Wire.h> //sd
#include <ThreeWire.h> //rtc 
#include <RtcDS1302.h> //rtc

#define dht_apin A0 // Analog Pin sensor is connected to
dht DHT;

ThreeWire myWire(4, 5, 3); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

File myFile; //sd

String newTime;
String oldTime;

void save_temperature( String DT) {

  DHT.read11(dht_apin);

  Serial.print("humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");

  delay(1000);//Wait 2 seconds before accessing sensor again.

  myFile = SD.open("data.txt", FILE_WRITE);
  myFile.print(DT);
  myFile.print(" , ");
  myFile.print(DHT.humidity);
  myFile.print(" , ");
  myFile.println(DHT.temperature);
  myFile.close();
}

void save_prompt( String prompt) {
  myFile = SD.open("data.txt", FILE_WRITE);
  myFile.println(prompt);
  myFile.close();
}

void(* resetFunc) (void) = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();
  save_prompt(printDateTime(compiled));

  if (!Rtc.IsDateTimeValid())
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    save_prompt("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    save_prompt("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    save_prompt("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    save_prompt("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
    save_prompt("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    save_prompt("RTC is the same as compile time! (not expected but all is fine)");
  }

  delay(1000);//Delay to let system boot

  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  save_prompt("DHT11 Humidity & temperature Sensor");
  save_prompt("Outout Guide for data importation...");
  save_prompt("Date, Humidity, Temperature");
  delay(1000);//Wait before accessing Sensor
  
  Serial.print("Initializing SD card...");
  save_prompt("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    save_prompt("initialization failed!");
    save_prompt("computer reset...");
    resetFunc();
    while (1);
  }
  Serial.println("initialization done.");
  save_prompt("initialization done...");
  save_prompt("Note: Outout Guide for data importation...");
  save_prompt("Date, Humidity, Temperature");
}


void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime now = Rtc.GetDateTime();

  //  printDateTime(now);
  //  Serial.println();

  if (!now.IsValid())
  {
    // Common Causes:
    //    1) the battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!");
    save_prompt("RTC lost confidence in the DateTime!");
  }
  
  delay(1000); // five seconds
  
  newTime = printDateTime(now);
  Serial.println();
  save_temperature(newTime);
  
}




#define countof(a) (sizeof(a) / sizeof(a[0]))
String printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
  return datestring;
}
