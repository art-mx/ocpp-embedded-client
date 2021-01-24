#include "Requests/CallError.h"

Msg CallError::Handle(Msg & msg) {
    logser.println("handling CALLERROR");
    return msg;
}