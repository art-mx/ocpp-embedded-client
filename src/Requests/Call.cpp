#include "Requests/Call.h"


Call::Call(string action, string payload): Action(action), Payload(payload) {
    UniqueId = GenerateUniqueId();
}

// struct CallInfo {
//     string Action;
//     string UniqueId;
// };

// PendingCalls::PendingCalls(){};

void PendingCalls::StoreCall(Call * call) {
    call_list_.emplace_back(call);
}

bool PendingCalls::GetCallActionWithId(string & id, string & action) {
    // possibly better to use map 
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


