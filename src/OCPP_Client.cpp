#include "OCPP_Client.h"

using std::string;
extern HardwareSerial comser;
extern HardwareSerial logser;


OCPP_Client::OCPP_Client(Device * device): device_(device) {
    jsonrpc_init(NULL, NULL);
    pending_calls_ = new PendingCalls(this);
    boot_notification_req = new BootNotificationReq();
    status_notification_req = new StatusNotificationReq();
    start_transaction_req = new StartTransactionReq();
    stop_transaction_req = new StopTransactionReq();
    message = new Message();
    message->SetDevice(device_);
    SendBootNotification();
}

void OCPP_Client::SendBootNotification() {
    PendingCall *call = new PendingCall(boot_notification_req->Action, boot_notification_req->Payload());
    SendCall(call);
}

void OCPP_Client::SendStatusNotification(int connector, string error, string status) {
    PendingCall *call = new PendingCall(status_notification_req->Action, status_notification_req->Payload(connector, error, status));
    SendCall(call);
}

void OCPP_Client::SendStartTransaction(int connector, string idTag, int meterStart, string timestamp) {
    PendingCall *call = new PendingCall(start_transaction_req->Action, start_transaction_req->Payload(connector, idTag, meterStart, timestamp));
    SendCall(call);
}

void OCPP_Client::SendStopTransaction(int meterStop, string timestamp, int transactionId, StopTransactionReason reason) {
    PendingCall *call = new PendingCall(stop_transaction_req->Action, stop_transaction_req->Payload(meterStop, timestamp, transactionId, reason));
    SendCall(call);
}

void OCPP_Client::SendCall(PendingCall* call) {
    // send the call
    mjson_printf(Sender, NULL, call->format, call->MessageTypeId, call->UniqueId.c_str(), call->Action.c_str(), call->Payload.c_str());
    logser.printf("sent %s with id %s, payload: %s\r\n", call->Action.c_str(), call->UniqueId.c_str(), call->Payload.c_str());
    pending_calls_->StoreCall(call);
}

void OCPP_Client::ReSendCall(PendingCall* call) {
    // send the call
    mjson_printf(Sender, NULL, call->format, call->MessageTypeId, call->UniqueId.c_str(), call->Action.c_str(), call->Payload.c_str());
    logser.printf("sent %s with id %s, payload: %s\r\n", call->Action.c_str(), call->UniqueId.c_str(), call->Payload.c_str());
}

void OCPP_Client::SendCallResult(Msg & msg) {
    mjson_printf(Sender, NULL, "[%d, %Q, %s]\n", CALLRESULT, msg.uid.c_str(), msg.response_payload.c_str());
    logser.printf("sent response with id %s, payload: %s\r\n", msg.uid.c_str(), msg.response_payload.c_str());
}

int Sender(const char *frame, int frame_len, void *privdata) {
    return comser.write(frame, frame_len);
}

void OCPP_Client::Update(){
    static char buf[200];
    static int len;
    static string raw;

    pending_calls_->Update();

    if (comser.available()) {
        char ch = comser.read();
        buf[len++] = ch;
        int res = check_if_frame_is_complete(buf, len, raw);
        if(res>0) {
            logser.println(raw.c_str());
            std::fill_n(buf, 200, 0);
            len = 0;
            Msg msg;
            msg.raw = raw;
            message->Handle(msg);
        }        
    }  
}