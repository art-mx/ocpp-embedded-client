#include "Requests/Message.h"

using std::string;

Msg Message::Handle(Msg & msg) {

    double raw_value;
    if (!mjson_get_number(msg.raw.c_str(), msg.raw.length(), MessageTypeId_key, &raw_value)) {
        logser.println("message type not found");
        return msg;
    }
    msg.type = static_cast<int>(raw_value);
    switch (msg.type) {
        case CALLRESULT:
            logser.println("got CALLRESULT");
            this->SetNext(new CallResult());
            break;
        case CALLERROR:
            logser.println("got CALLERROR");
            this->SetNext(new CallError());
            break;
        case CALL:
            logser.println("got CALL");
            this->SetNext(new Call());
            break;
        default:
            logser.println("got UNDEFINED MessageType\r\n");
            return msg;
    }
    return AbstractHandler::Handle(msg);
}