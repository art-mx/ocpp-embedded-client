#pragma once

#include <Arduino.h>

class OCPP_Client;
class State;

class Device {
    public:
        Device();
        ~Device();
        void SetClient(OCPP_Client * client);
        void ChangeState(State * state);
        void Update();
        OCPP_Client * client_{nullptr};
        State * state_{nullptr};
    private:
        
};


    