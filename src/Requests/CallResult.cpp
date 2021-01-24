#include "Requests/CallResult.h"

Msg CallResult::Handle(Msg & msg) {
    logser.println("handling CALLRESULT");

    if(!GetString(msg.raw, UniqueId_key, msg.uid)) {
        logser.printf("UniqueId not found in message %s\r\n", msg.raw.c_str());
        return msg;
    }

    if(!GetObject(msg.raw, Payload_key, msg.payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.raw.c_str());
        return msg; // TODO handle null
    }

    bool result = device_->client_->pending_calls_->GetCallActionWithId(msg.uid, msg.action);
    if (result) {
        // logser.printf("got result for id: %s payload: %s action: %s \r\n", id.c_str(), payload.c_str(), action_str.c_str());
        MessageAction action = CallResultActionNamesMap[msg.action];
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