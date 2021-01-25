#pragma once
#include <string>

#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"
#include "PendingCalls.h"
#include "Device.h"
#include "OCPP_Client.h"
#include "Requests/BootNotificationConf.h"
#include "Requests/StatusNotificationConf.h"

// class Device;
extern HardwareSerial logser;

class CallResult : public AbstractHandler {
  public:

    /*
    * [<MessageTypeId>, "<MessageId>", {<Payload>}]
    */
    const char * format = "[%d, %Q, %s]\n";
    const char * MessageTypeId_key = "$[0]";
    const char * UniqueId_key = "$[1]";
    const char * Payload_key = "$[2]";
    Msg Handle(Msg & msg) override;
};

