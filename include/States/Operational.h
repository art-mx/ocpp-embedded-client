#pragma once
#include "States/State.h"


class Operational : public State {
 public:
  void HandleRegistrationStatusAccepted();
  void HandleTimerChange();
  const std::string GetStateName();
};