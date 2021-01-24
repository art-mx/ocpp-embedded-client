#pragma once
#include <string>
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"

extern HardwareSerial logser;

class CallError : public AbstractHandler {
  public:

    /*
    * [<MessageTypeId>, "<UniqueId>", "<errorCode>", "<errorDescription>", {<errorDetails>}]
    */
    const char * format = "[%d, %Q, %Q, %Q, %s]\n";
    const char * errorCode_key = "$[2]";
    const char * errorDescription_key = "$[3]";
    const char * errorDetails_key = "$[4]";
    // void MessageHandler(const string & payload, Device * device);
    Msg Handle(Msg & msg) override;
};