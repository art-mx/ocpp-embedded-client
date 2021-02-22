#include "Requests/Message.h"
#include "Requests/CallResult.h"
#include "Requests/Call.h" 
#include "Requests/CallError.h"

using std::string;

Message::Message(){
    call_ = new Call();
    callResult_ = new CallResult();
    callerror_ = new CallError();
}

Msg Message::Handle(Msg & msg) {

    int type;
    if (!GetInteger(msg.raw, MessageTypeId_key, &type)) {
        logser.println("message type not found");
        return msg;
    }

    msg.type = static_cast<int>(type);
    switch (msg.type) {
        case CALLRESULT:
            this->SetNext(callResult_);
            break;
        case CALLERROR:
            this->SetNext(callerror_);
            break;
        case CALL:
            this->SetNext(call_);
            break;
        default:
            logser.println("got UNDEFINED MessageType\r\n");
            return msg;
    }
    return AbstractHandler::Handle(msg);
}