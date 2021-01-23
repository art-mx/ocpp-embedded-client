#pragma once
#include <string>

#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"
#include "PendingCalls.h"
#include "Device.h"

// class Device;
extern HardwareSerial logser;
extern Device * device;

class CallResult : public AbstractHandler {
  public:

    /*
    * [<MessageTypeId>, "<MessageId>", {<Payload>}]
    */
    const char * format = "[%d, %Q, %s]\n";
    const char * MessageTypeId_key = "$[0]";
    const char * UniqueId_key = "$[1]";
    const char * Payload_key = "$[2]";
    // void MessageHandler(const string & payload, Device * device);
    string & Handle(string & msg) override;
};

