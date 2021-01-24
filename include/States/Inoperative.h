#pragma once
#include "States/State.h"
// #include "Types/Types.h"
// #include "States/Initialization.h"


class Inoperative : public State {
 public:

  void StateHandle_RegistrationStatus(RegistrationStatus status) {};
  AvailabilityStatus StateHandle_AvailabilityStatus(AvailabilityType type);
  void HandleTimerChange();
  const std::string GetStateName();
};