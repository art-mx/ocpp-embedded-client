#include "Requests/Call.h"
#include "Requests/ChangeAvailabilityReq.h"

Call::Call() {
    ChangeAvailabilityReq_ = new ChangeAvailabilityReq();
}

Msg Call::Handle(Msg & msg) {

    logser.println("handling CALL");

    if(!GetObject(msg.raw, Payload_key, msg.payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.raw.c_str());
        return msg;
    }
    
    if(!GetString(msg.raw, Action_key, msg.action)) {
        logser.printf("Action not found in message %s\r\n", msg.raw.c_str());
        return msg;
    }

    if(!GetString(msg.raw, UniqueId_key, msg.uid)) {
    logser.printf("UniqueId not found in message %s\r\n", msg.raw.c_str());
    return msg;
    }
    MessageAction action = MessageActionNamesMap[msg.action];
        switch (action) {
            case CHANGE_AVAILABILITY:
                logser.println("got CHANGE_AVAILABILITY");
                this->SetNext(ChangeAvailabilityReq_);
                break;
            default:
                logser.printf("unknown Action: %s", msg.action);
                return msg;
        }

    return AbstractHandler::Handle(msg);
}