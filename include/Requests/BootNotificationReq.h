#pragma once
#include <Arduino.h>
#include "Call.h"
extern "C" {
  #include "mjson.h"
}
using namespace std;

class BootNotificationReq {
    private:
        string chargePointModel_;
        string chargePointVendor_;
        string chargePointSerialNumber_;
        string firmwareVersion_;
        string iccid_;
        string imsi_;
        string meterSerialNumber_;
        string meterType_;

    public:
        BootNotificationReq();
        // ~BootNotificationReq();
        string GetPayload();
        const string Action = "BootNotification";

        /*
        * {"chargePointModel": "modelX", "chargePointVendor": "vendorX"}
        */
        const char * payload_format = "{%Q: %Q, %Q: %Q}";
};