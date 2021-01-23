#pragma once
#include <Arduino.h>
#include "Requests/AbstractHandler.h"
#include "Types/Types.h"
#include "JSONParser.h"

class ChangeAvailabilityReq: public AbstractHandler {
    public:
        string & Handle(string & msg) override;

};
