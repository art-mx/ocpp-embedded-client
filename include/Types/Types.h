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
   {"Refected", REJECTED}
};