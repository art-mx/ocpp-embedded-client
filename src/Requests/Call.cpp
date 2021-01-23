#include "Requests/Call.h"


string & Call::Handle(string & msg) {
    logser.println("handling CALL");
    logser.println(device->bla);
    string payload;
    if(!GetString(msg, Payload_key, payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.c_str());
        return msg;
    }
    string action;
    if(!GetString(msg, Action_key, payload)) {
        logser.printf("Action not found in message %s\r\n", msg.c_str());
        return msg;
    }
    return AbstractHandler::Handle(msg);
}