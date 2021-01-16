#include <Arduino.h>
#include "Pins.h"
#include "OCPP_Client.h"


OCPP_Client * client;

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);
  pinMode(ERROR_LED, OUTPUT);
  
  Serial1.begin(9600);
  Serial1.println("SPLC-T1 ready");
  client = new OCPP_Client();
}



void loop() {
  client->Update();
}