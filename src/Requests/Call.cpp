#include "Requests/Call.h"
#include "Requests/ChangeAvailabilityReq.h"
#include "Requests/RemoteStartTransactionReq.h"
#include "Requests/RemoteStopTransactionReq.h"

Call::Call() {
    ChangeAvailabilityReq_ = new ChangeAvailabilityReq();
    RemoteStartTransactionReq_ = new RemoteStartTransactionReq();
    RemoteStopTransactionReq_ = new RemoteStopTransactionReq();
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
    logser.printf("got %s , id=%i", msg.action.c_str(), action);
    switch (action) {
        case CHANGE_AVAILABILITY:
            this->SetNext(ChangeAvailabilityReq_);
            break;
        case REMOTE_START_TRANSACTION:
            this->SetNext(RemoteStartTransactionReq_);
            break;
        case REMOTE_STOP_TRANSACTION:
            this->SetNext(RemoteStopTransactionReq_);
            break;
        default:
            logser.printf("unknown Action: %s\r\n", msg.action.c_str());
            return msg;
    }

    return AbstractHandler::Handle(msg);
}