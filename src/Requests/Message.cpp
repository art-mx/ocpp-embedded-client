#include "Requests/Message.h"

using std::string;

string & Message::Handle(string & msg) {
    int id;
    double raw_value;

    if (!mjson_get_number(msg.c_str(), msg.length(), "$[0]", &raw_value)) {
        logser.println("message type not found");
        return msg;
    }
    id = static_cast<int>(raw_value);
    switch (id) {
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