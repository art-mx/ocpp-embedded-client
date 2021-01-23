#pragma once
#include <Arduino.h>
#include "mjson.h"
#include "Requests/PendingCalls.h"
#include "Requests/BootNotificationReq.h"
// #include "Requests/BootNotificationConf.h"
#include "Requests/Message.h"
#include "Requests/CallResult.h"
#include "Requests/Call.h" 
#include "Requests/CallError.h"
#include "JSONParser.h"


using std::string;

int Sender(const char *frame, int frame_len, void *privdata);

class Device;
class Message;

class OCPP_Client {
  public:
    struct jsonrpc_ctx ctx;
    // static void ocpp_cb(struct jsonrpc_request *r);
    // static int CTXInitCallback(const char *buf, int len, void *pivate_data) {};
    // static int Sender(const char* frame, int frame_len, void* privdata);
   
    Device * device_;
    OCPP_Client();
    ~OCPP_Client();
    void SetDevice(Device * device);
    uint32_t counter = 0;
    void SendBootNotification();
    // void ProcessMessage(string &msg);
    void SendCall(PendingCall * call);
    // void ProcessCallResult(string & msg);
    // void ProcessCallError(string & msg);
    // void ProcessCall(string & msg);
    // static bool GetUniqueId(string & msg, string & UniqueId);
    // static bool GetCallResultPayload(string & msg, string & Payload);
    // static bool GetCallPayload(string & msg, string & Payload);
    // static bool GetCallAction(string & msg, string & action);
    void Update();
    PendingCalls * pending_calls_;
    BootNotificationReq * boot_notification_req;
    // BootNotificationConf * boot_notification_conf;
    Message * message;

};