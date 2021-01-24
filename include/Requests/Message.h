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


class Message : public AbstractHandler {
    public:
        const char * MessageTypeId_key = "$[0]";
        const char * UniqueId_key = "$[1]";

        Msg Handle(Msg & msg) override;
};