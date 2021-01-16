#include <Arduino.h>
#include <vector>
#include <map>

#pragma once

using namespace std;

#define MAX_CALL_NUM 10 // number of calls to store

struct CallInfo {
    string Action;
    string UniqueId;
};

class Call {
    public:
        Call(string Action, string Payload);
        Call();
        // Call& operator=(Call&&);
        // ~Call();
        const uint8_t MessageTypeId = 2;
        string Action;
        string UniqueId;
        string Payload;
        /*
        * [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
        */
        const char * call_format = "[%d, %Q, %Q, %s]\n";
        string GenerateUniqueId() {
            static int i = 0;
            ++i;
            return to_string(i);
        }
};

class PendingCalls {
    private:
        vector<Call*> call_list_;
        // map<string, string> call_map_;
    public:
        PendingCalls()  {} ;
        ~PendingCalls() = default;
        void StoreCall(Call * call);
        bool GetCallActionWithId(string & id, string & action);

};



// BootNotificationConf * BootNotificationConf;
// Msg2 * Msg2;

// Conf list[20] = {BootNotificationConf, Msg2};

// enum_val = CallActionsMap[action];
// list(enum_val).parse(payload);

// enum CallActions {
//     BOOT_NOTIFICATION=0,
//     MSG2=1
// };

// static std::map<std::string, CallActions> CallActionsMap = {
//    { "BootNotification", BOOT_NOTIFICATION},

// };

