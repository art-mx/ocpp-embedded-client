#pragma once
#include <Arduino.h>
#include "mjson.h"
#include "Requests/Call.h"
#include "Requests/BootNotificationReq.h"
#include "Requests/BootNotificationConf.h"
#include "Device.h" 
#define CALL 2
#define CALLRESULT 3
#define CALLERROR 4
using std::string;

class Device;

class OCPP_Client {
  public:
    struct jsonrpc_ctx ctx;
    // static void ocpp_cb(struct jsonrpc_request *r);
    // static int CTXInitCallback(const char *buf, int len, void *pivate_data) {};
    // static int Sender(const char* frame, int frame_len, void* privdata);
    // OCPP_Client();
    Device * device_;
    OCPP_Client();
    ~OCPP_Client();
    void SetDevice(Device * device);
    uint32_t counter = 0;
    void SendBootNotification();
    void ProcessMessage(string &msg);
    void SendCall(Call * call);
    void ProcessCallResult(string & msg);
    void ProcessCallError(string & msg);
    void ProcessCall(string & msg);
    static bool GetUniqueId(string & msg, string & UniqueId);
    static bool GetPayload(string & msg, string & Payload);
    void Update();
    PendingCalls * pending_calls_;
    BootNotificationReq * boot_notification_req;
    BootNotificationConf * boot_notification_conf;
    // Call * call;
};