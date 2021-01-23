#include "OCPP_Client.h"

using std::string;
extern HardwareSerial comser;
extern HardwareSerial logser;


OCPP_Client::OCPP_Client() { //(Device * device): device_(device){
    jsonrpc_init(NULL, NULL);
    
    // CallResult * call_result = new CallResult();
    pending_calls_ = new PendingCalls();
    // boot_notification_req = new BootNotificationReq();
    // boot_notification_conf = new BootNotificationConf();

    message = new Message();
    // string msg = "[2,\"b39d8e77-7353-4534-949a-0966dd102661\",\"ChangeAvailability\",{\"connectorId\":0,\"type\":\"Operative\"}]";
    // message->Handle(msg);
}

void OCPP_Client::SetDevice(Device * device) {
    device_ = device;
}

void OCPP_Client::SendBootNotification() {
    // PendingCall *call = new PendingCall(boot_notification_req->Action, boot_notification_req->Payload());
    // SendCall(call);
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
            logser.println(msg.c_str());
            std::fill_n(buf, 200, 0);
            len = 0;
            message->Handle(msg);

        }        
    } 
    
}

void OCPP_Client::SendCall(PendingCall* call) {
    // send the call
    mjson_printf(Sender, NULL, call->format, call->MessageTypeId, call->UniqueId.c_str(), call->Action.c_str(), call->Payload.c_str());
    logser.printf("sent %s with id %s, payload: %s\r\n", call->Action.c_str(), call->UniqueId.c_str(), call->Payload.c_str());
    pending_calls_->StoreCall(call);
}

int Sender(const char *frame, int frame_len, void *privdata) {
    return comser.write(frame, frame_len);
}