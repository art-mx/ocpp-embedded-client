#include "Requests/Call.h"

extern HardwareSerial comser;
extern HardwareSerial logser;

Call::Call(string action, string payload): Action(action), Payload(payload) {
    UniqueId = GenerateUniqueId();
}

void PendingCalls::Update() {
    if (call_list_.size()>MAX_CALL_NUM) {
        logser.println("reached MAX_CALL_NUM!");
        Call * pointer_to_deleted = *(call_list_.begin());
        call_list_.erase(call_list_.begin());  
        delete pointer_to_deleted;
    }
}

void PendingCalls::StoreCall(Call * call) {
    call_list_.emplace_back(call);
}

bool PendingCalls::GetCallActionWithId(string & id, string & action) {

    for (unsigned i=0; i<call_list_.size(); ++i) {
        if (call_list_[i]->UniqueId == id) {
            action.assign(call_list_[i]->Action);
            Call * pointer_to_deleted = *(call_list_.begin() + i);
            call_list_.erase(call_list_.begin()+i); // TODO
            delete pointer_to_deleted;
            return true;
        }
    } 
    return false;
}


