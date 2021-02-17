#include "Requests/Message.h"

using std::string;

Msg Message::Handle(Msg & msg) {

    int type;
    if (!GetInteger(msg.raw, MessageTypeId_key, &type)) {
        logser.println("message type not found");
        return msg;
    }

    msg.type = static_cast<int>(type);
    switch (msg.type) {
        case CALLRESULT:
            this->SetNext(new CallResult());
            break;
        case CALLERROR:
            this->SetNext(new CallError());
            break;
        case CALL:
            this->SetNext(new Call());
            break;
        default:
            logser.println("got UNDEFINED MessageType\r\n");
            return msg;
    }
    return AbstractHandler::Handle(msg);
}