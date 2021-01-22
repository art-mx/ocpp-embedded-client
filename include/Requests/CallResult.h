#pragma once
#include "Arduino.h"
extern "C" {
  #include "mjson.h"
}
#include <string>
#include "Types/Types.h"
#include "Requests/Message.h"

class Device;
extern HardwareSerial logser;

class CallResult : public Message {
  public:

    /*
    * [<MessageTypeId>, "<MessageId>", {<Payload>}]
    */
    const char * format = "[%d, %Q, %s]\n";
    const char * Payload_key = "$[2]";
    void MessageHandler(const string & payload, Device * device);
};

