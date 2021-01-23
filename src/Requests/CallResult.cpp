#include "Requests/CallResult.h"

string & CallResult::Handle(string & msg) {
    logser.println("handling CALLRESULT");

    string id;
    string payload;
    string action_str;
    MessageAction action;

    if(!GetString(msg, UniqueId_key, id)) {
        logser.printf("UniqueId not found in message %s\r\n", msg.c_str());
        return msg;
    }

    if(!GetObject(msg, Payload_key, payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.c_str());
        return msg; // TODO handle null
    }

    bool result = device_->client_->pending_calls_->GetCallActionWithId(id, action_str);
    if (result) {
        // logser.printf("got result for id: %s payload: %s action: %s \r\n", id.c_str(), payload.c_str(), action_str.c_str());
        action = MessageNamesMap[action_str];
        switch (action) {
            case BOOT_NOTIFICATION:
                this->SetNext(new BootNotificationConf());
                break;
            // case CHANGE_AVAILABILITY:
            //     // handle this
            //     break;
        }
        return AbstractHandler::Handle(msg);
    }   
    else {
        logser.println("Unknown response");
        return msg;
    }
}