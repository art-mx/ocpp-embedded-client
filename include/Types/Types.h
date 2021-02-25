#pragma once
#include <Arduino.h>
#include <map>
#include <string>
using namespace std;


// typedef char CiString50Type[50];
// typedef char CiString25Type[25]; 
typedef char CiString20Type[20];

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
    UNDEFINED_ACTION = 0,
    BOOT_NOTIFICATION,
    CHANGE_AVAILABILITY,
    STATUS_NOTIFICATION,
    REMOTE_START_TRANSACTION,
    START_TRANSACTION
};

static std::map<std::string, MessageAction> MessageActionNamesMap = {
    {"BootNotification", BOOT_NOTIFICATION},
    {"ChangeAvailability", CHANGE_AVAILABILITY},
    {"StatusNotification", STATUS_NOTIFICATION},
    {"RemoteStartTransaction", REMOTE_START_TRANSACTION},
    {"StartTransaction", START_TRANSACTION}
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
    AVAIL_STATUS_UNDEFINED = 0,
    AVAIL_STATUS_ACCEPTED = 1,
    AVAIL_STATUS_REJECTED = 2,
    AVAIL_STATUS_SCHEDULED = 3
};
static const string AvailabilityStatusNames[4] = {
    "Undefined",
    "Accepted",
    "Scheduled",
    "Rejected"
};

enum ChargePointStatus {
    CP_STATUS_Available,
    CP_STATUS_Preparing,
    CP_STATUS_Charging,
    CP_STATUS_SuspendedEVSE,
    CP_STATUS_SuspendedEV,
    CP_STATUS_Finishing,
    CP_STATUS_Reserved,
    CP_STATUS_Unavailable,
    CP_STATUS_Faulted
};

static const string ChargePointStatusNames[9] = {
    "Available", 
    "Preparing", 
    "Charging",
    "SuspendedEVSE",
    "SuspendedEV",
    "Finishing",
    "Reserved",
    "Unavailable",
    "Faulted"
};

enum ChargePointErrorCode {
    CP_ERROR_ConnectorLockFailure,
    CP_ERROR_EVCommunicationError,
    CP_ERROR_GroundFailure,
    CP_ERROR_HighTemperature,
    CP_ERROR_InternalError,
    CP_ERROR_LocalListConflict,
    CP_ERROR_NoError,
    CP_ERROR_OtherError,
    CP_ERROR_OverCurrentFailure,
    CP_ERROR_OverVoltage,
    CP_ERROR_PowerMeterFailure,
    CP_ERROR_PowerSwitchFailure,
    CP_ERROR_ReaderFailure,
    CP_ERROR_ResetFailure,
    CP_ERROR_UnderVoltage,
    CP_ERROR_WeakSignal
};
static const string ChargePointErrorCodeNames[16] = {
    "ConnectorLockFailure",
    "EVCommunicationError",
    "GroundFailure",
    "HighTemperature",
    "InternalError",
    "LocalListConflict",
    "NoError",
    "OtherError",
    "OverCurrentFailure",
    "OverVoltage",
    "PowerMeterFailure",
    "PowerSwitchFailure",
    "ReaderFailure",
    "ResetFailure",
    "UnderVoltage",
    "WeakSignal"
};

enum RemoteStartStopStatus {
    REMOTE_STATUS_UNDEFINED = 0,
    REMOTE_STATUS_ACCEPTED = 1,
    REMOTE_STATUS_REJECTED = 2
};
static const string RemoteStartStopStatusNames[3] = {
    "Undefined",
    "Accepted",
    "Rejected"
};

enum AuthorizationStatus {
    AUTH_STATUS_UNDEFINED = 0,
    AUTH_STATUS_ACCEPTED,
    AUTH_STATUS_BLOCKED,
    AUTH_STATUS_EXPIRED,
    AUTH_STATUS_INVALID,
    AUTH_STATUS_CONCURRENTTX
};


static std::map<std::string, AuthorizationStatus> AuthorizationStatusMap = {
   {"Accepted", AUTH_STATUS_ACCEPTED},
   {"Blocked", AUTH_STATUS_BLOCKED},
   {"Expired", AUTH_STATUS_EXPIRED},
   {"Invalid", AUTH_STATUS_INVALID},
   {"ConcurrentTx", AUTH_STATUS_CONCURRENTTX}
};