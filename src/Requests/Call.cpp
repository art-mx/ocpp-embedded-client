#include "Requests/Call.h"


Call::Call(string action, string payload): Action(action), Payload(payload) {
    UniqueId = GenerateUniqueId();
}

// PendingCalls::PendingCalls(){};

void PendingCalls::StoreCall(Call * call) {
    call_list_.emplace_back(*call);
}

Call PendingCalls::GetCallWithId(string & id) {
    // possibly better to use map 
    for (auto & call: call_list_) {
        if (call.UniqueId == id) {
            return call;
        }
    }
}



