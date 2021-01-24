#pragma once
#include "States/State.h"
// #include "Types/Types.h"

class Initialization : public State {
 public:
  void StateHandle_RegistrationStatus(RegistrationStatus status);

  // when in initialization state we're not handling anything besides Registration
  AvailabilityStatus StateHandle_AvailabilityStatus(AvailabilityType type) {}; 
  void HandleTimerChange();
  const std::string GetStateName();
};