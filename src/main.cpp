#include <Arduino.h>
#include "Device.h" 


#define F091
// #define F103



#ifdef F091
  HardwareSerial logser(PA3, PA2);
#endif
HardwareSerial comser(PA10, PA9);
// HardwareSerial Serial4(PC11, PC10);
uint32_t currentTime;

Device * device;
OCPP_Client * client;

void setup() {

  pinMode(PA_4, OUTPUT);
  digitalWrite(PA_4, LOW);

  logser.begin(115200);
  comser.begin(115200);
  logser.println("Serial 2 up");
  // Serial4.begin(9600);
  
  // device = new Device();
  // client = new OCPP_Client();
  // device->SetClient(client);
  // client->SetDevice(device);
  // client->SendBootNotification();
}

void loop() {
  // client->Update();
  
  if ((millis() - currentTime) > 10) {
    currentTime = millis();
    // client->SendBootNotification();
    logser.println(millis());
  }

}