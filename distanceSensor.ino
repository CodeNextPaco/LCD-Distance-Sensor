
//LCD + HC-SR04 sonar logs distance in inches
//LED 'alarm' when distance falls below threshold value


#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

int trigPin = 5;    // Trigger
int echoPin = 13;    // Echo
long duration, cm, inches;
int led = 4;
const int limit = 40;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.write("Distance: ");

  digitalWrite(led, LOW);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  lcd.setCursor(0,1);
  lcd.print(inches);
  lcd.setCursor(5,1);
  lcd.write("inches");

  
   
  
  delay(250);

  if(inches < limit){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  
}
