#pragma once
#include "Arduino.h"
extern "C" {
  #include "mjson.h"
}
#include <string>
#include "Types/Types.h"
#include "Requests/AbstractHandler.h"
#include "Requests/CallResult.h"
#include "Requests/Call.h" 
#include "Requests/CallError.h"
#include "JSONParser.h"

using std::string;
extern HardwareSerial logser;
// class CallResult;

class Message : public AbstractHandler {
    public:
        // ~Message() = default;
      // Message(Device * device): AbstractHandler(device) {} 
        // these two have the same position in any message
        const char * MessageTypeId_key = "$[0]";
        const char * UniqueId_key = "$[1]";

        const char * Payload_key;
        const char * Action_key;

        string & Handle(string & msg) override;
};