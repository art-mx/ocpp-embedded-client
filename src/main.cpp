#include <Arduino.h>
#include "Device.h" 
#include "Connector.h"

HardwareSerial logser(PA3, PA2);
HardwareSerial comser(PA10, PA9);

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
  // client = new OCPP_Client();
  // charge_point->SetClient(client);
  // client->SetDevice(device);
  // charge_point->client_->SendBootNotification();
  

}

void loop() {
  charge_point->Update();
  
  if ((millis() - currentTime) > 5000) {
    logser.printf("\r\n\r\nruntime: %i\r\n", millis());
    currentTime = millis();
    // charge_point->client_->SendBootNotification();
  }
}