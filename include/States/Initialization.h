#pragma once
#include "States/State.h"

class Initialization : public State {
 public:
  void HandleRegistrationStatusAccepted();
  void HandleTimerChange();
  const std::string GetStateName();
};