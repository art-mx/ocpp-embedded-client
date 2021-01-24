#pragma once
#include <Arduino.h>
#include "Types/Types.h"
extern "C" {
  #include "mjson.h"
}
#include "Requests/AbstractHandler.h"
#include "OCPP_Client.h"

class ChangeAvailabilityConf : public AbstractHandler {
    public:
        ChangeAvailabilityConf(AvailabilityStatus status) {
          status_ = status;
        }
        /*
        * {"status": "Accepted"}
        */
        AvailabilityStatus status_;
        const char * payload_format = "{%Q: %Q}";
        void SetPayload(string & payload);
        Msg Handle(Msg & msg) override;
};