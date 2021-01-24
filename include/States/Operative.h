#pragma once
#include "States/State.h"
// #include "Types/Types.h"


class State;

class Operative : public State {
 public:
  void StateHandle_RegistrationStatus(RegistrationStatus status) {};
  AvailabilityStatus StateHandle_AvailabilityStatus(AvailabilityType type);

  void HandleTimerChange();
  const std::string GetStateName();
};