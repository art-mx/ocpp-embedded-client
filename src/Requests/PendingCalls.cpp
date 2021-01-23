#include "Requests/PendingCalls.h"

extern HardwareSerial comser;
extern HardwareSerial logser;

PendingCall::PendingCall(string action, string payload): Action(action), Payload(payload) {
    UniqueId = GenerateUniqueId();
}

void PendingCalls::Update() {
    // logser.println(call_list_.capacity());
    if (call_list_.size()>MAX_CALL_NUM) {
        logser.printf("size: %s - reached MAX_CALL_NUM!\r\n", call_list_.size());
        PendingCall * pointer_to_deleted = *(call_list_.begin());
        call_list_.erase(call_list_.begin());  
        delete pointer_to_deleted;
    }
    if (call_list_.size()>MAX_CALL_NUM) {
        // check timeout for pending call
        // if timeout:
        // inc n++
        // send again
        // if n>3 handle com issue - light fault led
    }
}

void PendingCalls::StoreCall(PendingCall * call) {
    call_list_.emplace_back(call);
}

bool PendingCalls::GetCallActionWithId(string & id, string & action) {

    for (unsigned i=0; i<call_list_.size(); ++i) {
        if (call_list_[i]->UniqueId == id) {
            action.assign(call_list_[i]->Action);
            PendingCall * pointer_to_deleted = *(call_list_.begin() + i);
            call_list_.erase(call_list_.begin()+i); // TODO
            delete pointer_to_deleted;
            return true;
        }
    } 
    return false;
}


