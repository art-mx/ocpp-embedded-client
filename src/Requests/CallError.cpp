#include "Requests/CallError.h"

string & CallError::Handle(string & msg) {
    logser.println("handling CALLERROR");
    return msg;
}