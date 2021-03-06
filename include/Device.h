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
        Connector * GetConnector(int id);
        uint8_t NumConnectors();
        void ReportConnectors();
        void ReportConnectorStateChange(int id);
        void ChangeState(State * state);
        int GetMeterValueForTransaction(int transactionId){return 1000;} //TODO
        void Update();
        OCPP_Client * client_{nullptr};
        State * state_{nullptr};
    private:
        std::vector<Connector *> connector_list_;
    private:
        
};


    