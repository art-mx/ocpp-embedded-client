#include <Arduino.h>
#include "OCPP_Client.h"

#define F091
// #define F103

OCPP_Client * client;
#ifdef F091
  HardwareSerial logser(PA3, PA2);
#endif
HardwareSerial comser(PA10, PA9);
// HardwareSerial Serial4(PC11, PC10);
uint32_t currentTime;

void setup() {

  pinMode(PA_4, OUTPUT);
  digitalWrite(PA_4, LOW);

  logser.begin(115200);
  comser.begin(115200);
  logser.println("Serial 2 up");
  // Serial4.begin(9600);
  jsonrpc_init(NULL, NULL);
  
  client = new OCPP_Client();
  client->SendBootNotification();
}

void loop() {
  client->Update();
  
  if ((millis() - currentTime) > 100) {
    currentTime = millis();
    client->SendBootNotification();
    logser.println(millis());
  }

}