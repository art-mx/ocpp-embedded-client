#include <Arduino.h>
#include "mjson.h"
#include "Requests/Call.h"
#include "Requests/BootNotificationReq.h"
#include "Requests/BootNotificationConf.h"

#pragma once 
#define CALL 2
#define CALLRESULT 3
#define CALLERROR 4
using std::string;



class OCPP_Client {
  public:
  struct jsonrpc_ctx ctx;
    static void ocpp_cb(struct jsonrpc_request *r);
    static int CTXInitCallback(const char *buf, int len, void *pivate_data) {};
    static int Sender(const char* frame, int frame_len, void* privdata);
    OCPP_Client();
    ~OCPP_Client();
    

    void ProcessMessage(struct jsonrpc_request *r);
    void SendCall(Call * call);
    static void ocpp_cb(struct jsonrpc_request *r);
    static int Sender(const char *frame, int frame_len, void *privdata);

    void ProcessCallResult(struct jsonrpc_request *r);
    void ProcessCallError(struct jsonrpc_request *r);
    static bool GetUniqueId(struct jsonrpc_request *r, string & UniqueId);
    static bool GetPayload(struct jsonrpc_request *r, string & Payload);
    void Update();
    struct jsonrpc_ctx ctx;
    PendingCalls * pending_calls_;
    BootNotificationReq * boot_notification_req;
    BootNotificationConf * boot_notification_conf;
    Call * call;
};