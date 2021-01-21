#pragma once
#include "States/State.h"


class Available : public State {
 public:
  void HandleRegistrationStatusAccepted();
  void HandleTimerChange();
  const std::string GetStateName();
};