#pragma once
#include "Arduino.h"
extern "C" {
  #include "mjson.h"
}
#include <string>
#include "Types/Types.h"

class Device;
extern HardwareSerial logser;

class Message {
 public:
  static void MessageHandler(std::string & payload, Device * device) {
    // SendErrorResponse(r, "message not implemented");
  } // override this in child classes
  static void PayloadHandler(const std::string payload) {} 
  static bool GetDouble(const string & payload, const string & key, double * value);
  static bool GetInteger(string & payload, const std::string & key, int * value);
  static bool GetString(const string & payload, const std::string & key, std::string & value);
  // static void SendErrorResponse(struct jsonrpc_request* r, const std::string & err_messages);
  
};

