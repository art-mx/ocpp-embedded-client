#include "Requests/StatusNotificationConf.h"

Msg StatusNotificationConf::Handle(Msg & msg) {
    logser.printf("handled CallResult to %s\r\n", msg.action.c_str());
    return msg;
}   