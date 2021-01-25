#pragma once
#include <Arduino.h>

class Connector {
    private:
        PinName pin_;
    public:
        Connector(PinName pin, int id): pin_(pin), id(id) {};
        const int id;

        
};