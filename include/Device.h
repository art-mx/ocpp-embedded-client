#pragma once

#include <Arduino.h>
#include "Connector.h"
#include <vector>
#include "Types/Types.h"

using std::vector;
class OCPP_Client;
class State;

class Device {
    public:
        Device();
        ~Device();
        void SetClient(OCPP_Client * client);
        void AddConnector(Connector * connector);
        void ReportConnectors();
        void ChangeState(State * state);
        void Update();
        OCPP_Client * client_{nullptr};
        State * state_{nullptr};
    private:
        std::vector<Connector *> connector_list_;

        // Connector connector_list[4];
    private:
        
};


    