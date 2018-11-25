// Created by: David Boon 
// Written for ESP8266 NodeMCU chip, analog soil moisture sensor and 3v water pump
// power for pump and soil moisture sensor will require an npn transistor
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// These are the definitions for the ESP nodemcu's pin mappings 
// in the Arduino compiler.  Just makes it easier to look at.
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)
//On pin D2 we have the trigger for the pump
#define PUMPPIN D2
//On pin D1 we have the trigger for powering the sensor
#define SENSORPOWER D1
//this is a delay after the water is finished pouring before
//it checks the sensor again
#define WATERPOSTDELAY 5000
//the analog pin for the sensor, this code only knows how 
//to work with an analog input
#define SENSORPIN A0

//threshold is the point at which we consider the soil to be dry 
// and needing water. 
// For Reference, Sensor in water= 300ish, sensor out of water = 1000ish
int thresholdValue = 800;
//this is the amount of time
int POURINGDELAY =8000;
//interval checks the sensor every X ms, this is calculated for minutes
//on for the blynk app.  Even if you live in a desert every 30 mins should be enough.
unsigned long interval = 600000; 

//Blynk app token
char auth[] = "";

// will store last time sensor was checked, I'm back
// dating it so it checks on boot
unsigned long previousMillis = -600000;       


//These two variables are for the updating of the countdown timer.
unsigned long previousTimerMillis=0;
// we only check this timer minute
const long checkTimerInterval=60000;
int timeToCheckup=0,minutes,hours;
unsigned long currentMillis;
//This is a function called from the blynk app
BLYNK_WRITE(V1) // Terminal Widget
{
  thresholdValue=param.asInt(); //sets the threshold from the app
  Serial.print("Threshold:");
  Serial.println(thresholdValue);
  
}
BLYNK_WRITE(V2) // Terminal Widget
{
  interval=param.asInt()*60000;//sets the sensor check interval from the app
  Serial.print("Interval:");
  Serial.println(interval);
  //since we just changed the interval, update our timer.
  updateTimer();
}
BLYNK_WRITE(V3) // Terminal Widget
{
  POURINGDELAY=param.asInt()*1000;//sets the duration of the water pump
  Serial.print("POURINGDELAY:");
  Serial.println(POURINGDELAY);
  
}
BLYNK_WRITE(V8) // Terminal Widget
{
  checkOnPlants();
}
void setup()
{
  //ESP chips generally only go at 9600
  Serial.begin(9600);
  //Blynk handles our authentication and wifi router at the same time
  Blynk.begin(auth, "your wifi name", "your wifi password");
  //Set the sensor pin to input
  pinMode(SENSORPIN, INPUT);
  //set the pump pin to output
  pinMode(PUMPPIN, OUTPUT);
  //set the sensorpower pin to output
  pinMode(SENSORPOWER, OUTPUT);
  //set the threshold value on the blynk app (
  Blynk.virtualWrite(V1,thresholdValue);
}
int SensorValue(){ 
    //Time to check the sensor, power up the sensor
    digitalWrite(SENSORPOWER,HIGH);
    //delay half a sec so the sensor can power up
    delay(500);
    // read the input on analog pin 0:
    int sensorValue = analogRead(SENSORPIN);
    Serial.print(sensorValue);
    //update the blynk app
    Blynk.virtualWrite(V5,sensorValue);
    digitalWrite(SENSORPOWER,LOW);
    //power down the sensor cause we don't need it now
    return sensorValue;
}
void PumpWater(){
    // time to water the plant
    Serial.println(" - Time to water your plant");
    digitalWrite(PUMPPIN, HIGH);
    //depending on the pump, a high delay might be necessary to
    //push the water to the plant.
    delay(POURINGDELAY);
    digitalWrite(PUMPPIN, LOW);
    //notify blynk that the plant has been watered
    Blynk.notify("Your plant has been watered.");
    //give the water a chance to settle in the soil so it can 
    //effect the next sensor check
    delay(WATERPOSTDELAY); 
    
}
void checkOnPlants(){
   
    if(SensorValue() < thresholdValue){
      //Sensor has returned wet value
      Serial.println(" - Doesn't need watering");
      //reset previousMillis so we wait till next interval
      previousMillis = currentMillis;
    }
    else 
    {        
      //sensor has returned a value too dry.  pump some water 
      //(previousMillis is not reset so we will check again right after)
      PumpWater();
    }
}

void loop()
{ 
  //supports all blynk app code throughout the sketch
  Blynk.run();
  //update current millis (millis is the milliseconds since boot)
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    //we have passed the interval time for checking on the sensor.
    checkOnPlants();
  }
  if(currentMillis-previousTimerMillis>=checkTimerInterval){
    updateTimer();
    //reset previousTimerMillis as we only check this every minute
    previousTimerMillis=currentMillis;
  }
  
}
void updateTimer(){
    //if you add previousMillis and interval, you have the time for when
    //we next do a checkup
    timeToCheckup=((interval+previousMillis)-currentMillis)/60000; //convert to minutes
    minutes = timeToCheckup % 60; //minutes after hours
    hours = (timeToCheckup - minutes) / 60; 
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.println(" to next checkup");
    Blynk.virtualWrite(V6,hours);
    Blynk.virtualWrite(V7,minutes);
    
}
