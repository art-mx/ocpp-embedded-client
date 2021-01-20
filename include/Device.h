#pragma once

#include <Arduino.h>

class State;
class OCPP_Client;

class Device {
    public:
        Device();
        ~Device();
        void SetClient(OCPP_Client * client);
        void ChangeState(State * state);
        void Update();
        OCPP_Client * client_{nullptr};
    private:
        State * state_{nullptr};
        
};


    