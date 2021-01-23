#include "Requests/Call.h"


string & Call::Handle(string & msg) {

    logser.println("handling CALL");
    string payload;
    string action_str;
    MessageAction action;

    if(!GetObject(msg, Payload_key, payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.c_str());
        return msg;
    }
    
    if(!GetString(msg, Action_key, action_str)) {
        logser.printf("Action not found in message %s\r\n", msg.c_str());
        return msg;
    }
    action = MessageNamesMap[action_str];
        switch (action) {
            case CHANGE_AVAILABILITY:
                logser.println("got CHANGE_AVAILABILITY");
                // this->SetNext(new BootNotificationConf());
                break;
        }

    return AbstractHandler::Handle(msg);
}