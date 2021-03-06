#include <Arduino.h>
#include "Device.h" 
#include "Connector.h"
#include "rtc.h"

HardwareSerial logser(PA3, PA2);

//HardwareSerial comser(PA10, PA9); //for awd
HardwareSerial comser(PC11, PC10);

uint32_t currentTime;

Device * charge_point;
OCPP_Client * client;

void setup() {

  pinMode(PA_4, OUTPUT);
  digitalWrite(PA_4, LOW);

  

  logser.begin(115200);
  comser.begin(115200);
  logser.println("Serial 2 up");

  charge_point = new Device();
  charge_point->AddConnector(new Connector(PB_0, 0));
  // charge_point->AddConnector(new Connector(PB_1, 1));

  init_rtc();
}

void loop() {
  charge_point->Update();
  
  if ((millis() - currentTime) > 3000) {
    currentTime = millis();
    update_rtc();
    //charge_point->ReportConnectors();
  }
}