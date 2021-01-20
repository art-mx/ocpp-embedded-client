#pragma once
#include "States/State.h"

class Initialization : public State {
 public:
  void HandleRegistrationStatusAccepted();
  void HandleTimerChange();
  const char * GetStateName();
};