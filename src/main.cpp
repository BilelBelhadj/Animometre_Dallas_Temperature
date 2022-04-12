#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h" 


//declaration des constantes
const int   TEST_PIN = 0;
const float WIND_RAPPORT = 2.25;
const float T = 5;
const float MILE_TO_KILO = 1.60934;


//declaration des variables
int pulseSeconds = 0;
float windSpeed = 0.0;
unsigned long millisDelay = 5000 ;
unsigned long lastMillis  = 0 ;
unsigned long presentMillis = 0 ;


void count() {
  pulseSeconds ++ ;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();  
  pinMode(TEST_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(TEST_PIN), count, RISING );
}


void loop() {


  presentMillis = millis();
  if (presentMillis - lastMillis >= millisDelay)
  {
    lastMillis = presentMillis ;
  // put your main code here, to run repeatedly:

  //vitesse du vent en kilometre/h
  windSpeed = (pulseSeconds * (WIND_RAPPORT / T)) * MILE_TO_KILO;

  //afficher le vitesse du vent sur le moniteur serie
  Serial.print("Vitesse du vent : ");
  Serial.print(windSpeed);
  Serial.print(" Kph");
  Serial.println();

  //initialiser le nbr de pulsion en 0
  pulseSeconds = 0;

  }

  //envoi su ThingsBoard
  appendPayload("Vitesse du vent ", windSpeed);  
  sendPayload();                                  


}