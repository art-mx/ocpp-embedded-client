#pragma once
#include "Arduino.h"
extern "C" {
  #include "mjson.h"
}
#include <string>
#include "Types/Types.h"
#include "Requests/AbstractHandler.h"
#include "JSONParser.h"

using std::string;
extern HardwareSerial logser;

class Call;
class CallResult;
class CallError;

class Message : public AbstractHandler {
    public:
        Message();
        const char * MessageTypeId_key = "$[0]";
        const char * UniqueId_key = "$[1]";
        Msg Handle(Msg & msg) override;
    private:
      Call * call_;
      CallResult * callResult_;
      CallError * callerror_;
};