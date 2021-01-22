#pragma once
#include "Arduino.h"
extern "C" {
  #include "mjson.h"
}
#include <string>
#include "Types/Types.h"
// #include "Requests/Call.h"
// #include "Requests/CallResult.h"
// #include "Requests/CallError.h"


using std::string;
extern HardwareSerial logser;
class Device;
// class CallResult;

class Message {
    public:
        const char * format;

        // these two have the same position in any message
        const char * MessageTypeId_key = "$[0]";
        const char * UniqueId_key = "$[1]";

        const char * Payload_key;
        const char * Action_key;

        void MessageHandler(string & msg);
        // void PayloadHandler(const string payload) {}

        bool GetPayload(string & msg, string & Payload);
        bool GetMessageTypeId(string & msg, string & MessageTypeId);
        bool GetUniqueId(string & msg, string & UniqueId);
        bool GetAction(string & msg, string & action);
        bool GetDouble(const string & payload, const string & key, double * value);
        bool GetInteger(string & payload, const std::string & key, int * value);
        bool GetString(const string & payload, const std::string & key, std::string & value);

};