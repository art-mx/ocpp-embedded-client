#include "Requests/CallResult.h"
#include "Device.h"
#include "OCPP_Client.h"

string & CallResult::Handle(string & msg) {
    logser.println("handling CALLRESULT");
    string id;
    string payload;
    string action_str;
    MessageAction action;

    if(!GetString(msg, UniqueId_key, id)) return msg;
    if(!GetString(msg, Payload_key, payload)) return msg; // TODO handle null

    // bool result = 0;
    bool result = device->client_->pending_calls_->GetCallActionWithId(id, action_str);
    if (result) {
        logser.printf("got result for id:%s payload:%s action: %s \r\n", id.c_str(), payload.c_str(), action_str.c_str());
        action = MessageNamesMap[action_str];
        switch (action) {
            case BOOT_NOTIFICATION:
                // boot_notification_conf->MessageHandler(payload, device_);
                break;
            case CHANGE_AVAILABILITY:
                // handle this
                break;
        }
    }
    else logser.println("Unknown response");
    return msg;
}