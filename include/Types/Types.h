#include <Arduino.h>
#include <map>
#pragma once
using namespace std;

// typedef char CiString50Type[50];
// typedef char CiString25Type[25]; 
// typedef char CiString20Type[20];

class CiString {
    private:
        const uint8_t length_;
        string value_;
    public:
        CiString(uint8_t length, string value);
        ~CiString();
        string Get();
        bool Set(string value);
};



class CiString20 : public CiString {
    public:
        CiString20(string value) : CiString(20, value) {};
        // CiString20(): CiString(20, "") {};
};

typedef char dateTime[20];

enum RegistrationStatus {
    UNDEFINED = 0,
    ACCEPTED = 1,
    PENDING = 2,
    REJECTED = 3
};


static std::map<std::string, RegistrationStatus> RegistrationStatusMap = {
   {"Accepted", ACCEPTED},
   {"Rending", PENDING},
   {"Rejected", REJECTED}
};

enum MessageType {
    CALL = 2,
    CALLRESULT = 3,
    CALLERROR = 4
};

// TODO split into call actions and call result actions?
enum MessageAction { 
    BOOT_NOTIFICATION = 1,
    CHANGE_AVAILABILITY = 2
};

static std::map<std::string, MessageAction> CallResultActionNamesMap = {
   {"BootNotification", BOOT_NOTIFICATION}
};

static std::map<std::string, MessageAction> CallActionNamesMap = {
   {"ChangeAvailability", CHANGE_AVAILABILITY}
};

enum AvailabilityType {
    INOPERATIVE = 1,
    OPERATIVE = 2
};

static std::map<std::string, AvailabilityType> AvailabilityTypeNamesMap = {
   {"Inoperative", INOPERATIVE},
   {"Operative", OPERATIVE}
};

enum AvailabilityStatus {
    AVAIL_STATUS_ACCEPTED = 1,
    AVAIL_STATUS_REJECTED = 2,
    AVAIL_STATUS_SCHEDULED = 3
};

static std::map<AvailabilityStatus, std::string> AvailabilityStatusNamesMap = {
   {AVAIL_STATUS_ACCEPTED, "Accepted"},
   {AVAIL_STATUS_SCHEDULED, "Scheduled"},
   {AVAIL_STATUS_REJECTED, "Rejected"}
};