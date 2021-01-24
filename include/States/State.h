#pragma once
#include <Arduino.h>
#include "Device.h"
#include "Types/Types.h"
extern HardwareSerial logser;

class Device;

class State {
  protected:
    Device* device_;
    uint32_t last_state_change_millis_ {0};
    uint32_t kAutoStateChangeThreshold{5000};
  public:
    virtual ~State() {}
    void SetContext(Device* context) ;
    virtual const std::string GetStateName();
    uint32_t GetTimerValue();
    void UpdateTimerValue();

    virtual void StateHandle_RegistrationStatus(RegistrationStatus status);
    virtual AvailabilityStatus StateHandle_AvailabilityStatus(AvailabilityType type);
    // virtual void HandleRegistrationStatusRejected();
    // virtual void HandleAvailabilityChange();

};