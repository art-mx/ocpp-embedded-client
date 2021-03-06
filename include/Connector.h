#pragma once
#include <Arduino.h>
#include "Types/Types.h"

class Connector {
    private:
        PinName pin_;

    public:
        Connector(PinName pin, int id): pin_(pin), id(id) {};
        const int id;
        void SetStatus(ChargePointStatus status, ChargePointErrorCode error) {
            status_ = status;
            error_ = error;
        }
        int currentTransactionId;
        ChargePointStatus status_;
        ChargePointErrorCode error_;




        
};