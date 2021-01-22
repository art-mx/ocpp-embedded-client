#include "OCPP_Client.h"

using std::string;
extern HardwareSerial comser;
extern HardwareSerial logser;


OCPP_Client::OCPP_Client() { //(Device * device): device_(device){
    jsonrpc_init(NULL, NULL);
    pending_calls_ = new PendingCalls();
    Message * message = new Message();
    CallResult * call_result = new CallResult();
    boot_notification_req = new BootNotificationReq();
    boot_notification_conf = new BootNotificationConf();
}

void OCPP_Client::SetDevice(Device * device) {
    device_ = device;
}

void OCPP_Client::SendBootNotification() {
    Call *call = new Call(boot_notification_req->Action, boot_notification_req->Payload());
    SendCall(call);
}

void OCPP_Client::Update(){
    static char buf[200];
    static int len;
    static string msg;

    pending_calls_->Update();

    if (comser.available()) {
        char ch = comser.read();
        buf[len++] = ch;
        int res = check_if_frame_is_complete(buf, len, msg);
        if(res>0) {
            // logser.println(msg.c_str());
            std::fill_n(buf, 200, 0);
            len = 0;
            ProcessMessage(msg);
            // new Message(frame);
            // MessageHandler();
        }        
    } 
    
}

void OCPP_Client::ProcessCall(string & msg) {
    string payload;
    if(!GetCallPayload(msg, payload)) {
        logser.printf("Payload not found in message %s\r\n", msg.c_str());
        return;
    }
    string action;
    if(!GetCallAction(msg, payload)) {
        logser.printf("Action not found in message %s\r\n", msg.c_str());
        return;
    }

}

void OCPP_Client::ProcessCallResult(string & msg) {
    string id;
    string payload;
    string action_str;
    MessageAction action;

    if(!GetUniqueId(msg, id)) return;
    if(!GetCallResultPayload(msg, payload)) return; // TODO handle null

    bool result = pending_calls_->GetCallActionWithId(id, action_str);
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
}

void OCPP_Client::ProcessCallError(string & msg) {
    logser.println(msg.c_str());
}

void OCPP_Client::SendCall(Call* call) {
    // send the call
    mjson_printf(Sender, NULL, call->format, call->MessageTypeId, call->UniqueId.c_str(), call->Action.c_str(), call->Payload.c_str());
    logser.printf("sent %s with id %s, payload: %s\r\n", call->Action.c_str(), call->UniqueId.c_str(), call->Payload.c_str());
    pending_calls_->StoreCall(call);
}

bool OCPP_Client::GetCallResultPayload(string & msg, string & Payload) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), "$[2]", &p, &n) == MJSON_TOK_OBJECT) {
        Payload.assign(p, n);
        return true;
    }
    else {
        return false;
    }
}

bool OCPP_Client::GetCallPayload(string & msg, string & Payload) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), "$[3]", &p, &n) == MJSON_TOK_OBJECT) {
        Payload.assign(p, n);
        return true;
    }
    else {
        return false;
    }
}

bool OCPP_Client::GetUniqueId(string & msg, string & UniqueId) {
    char buff[100];
    int result = mjson_get_string(msg.c_str(), msg.length(), "$[1]", buff, sizeof(buff));
    if (result == 0) {
        // (r, result, "Failed to parse the request", NULL);
        return false;
    }
    UniqueId = buff;
    return true;
}

bool OCPP_Client::GetCallAction(string & msg, string & action) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), "$[2]", &p, &n) == MJSON_TOK_STRING) {
        action.assign(p, n);
        return true;
    }
    else {
        return false;
    }
}

void OCPP_Client::ProcessMessage(string & msg) {
    int id;
    double raw_value;

    if (!mjson_get_number(msg.c_str(), msg.length(), "$[0]", &raw_value)) {
        logser.println("message type not found");
        return;
    }
    id = static_cast<int>(raw_value);
    switch (id) {
        case CALLRESULT:
            logser.println("got CALLRESULT");
            ProcessCallResult(msg);
            break;
        case CALLERROR:
            logser.println("got CALLERROR");
            ProcessCallError(msg);
            break;
        case CALL:
            logser.println("got CALL");
            ProcessCall(msg);
            break;
        default:
            logser.println("got UNDEFINED MessageType\r\n");
            break;
    }
}

int check_if_frame_is_complete(char * buf, int len, string & frame) {
    int n = mjson(buf, len, NULL, NULL);
    if (n == 0) {
        // Not full JSON object was buffered
        return 0; 
    } else if (n < 0) {
        //handle_error(); // Invalid JSON
        return -1;
    } else {
        // JSON object length is `n`. Parse, and then remove n bytes from the input
        frame.assign(buf, n);
        return 1;
    }
}

int Sender(const char *frame, int frame_len, void *privdata) {
    return comser.write(frame, frame_len);
}