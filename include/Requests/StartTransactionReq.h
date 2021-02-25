#pragma once
#include <Arduino.h>


extern "C" {
  #include "mjson.h"
}
#include <string>
using std::string;

class StartTransactionReq {

    public:
        string Payload(int connector, string idTag, int meterStart, string timestamp);
        const string Action = "StartTransaction";

        /*
        * {"connectorId": 1, "idTag": "test_tag", "meterStart": 1234, "timestamp": "2021-02-25T13:01:23.684Z"}
        */
        const char * payload_format = "{%Q: %d, %Q: %Q, %Q: %d, %Q: %Q}";
        /*
        * {"connectorId": 1, "idTag": "test_tag", "meterStart": 1234, "reservationId": 1234, "timestamp": "2021-02-25T13:01:23.684Z"}
        */
        const char * payload_format_reservation = "{%Q: %d, %Q: %Q, %Q: %d, %Q: %d, %Q: %Q}";
        // string & Handle(string & msg);
};