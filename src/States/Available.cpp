#include "States/Initialization.h"
#include "States/Available.h"

const std::string Available::GetStateName() {
  return "Available";
}

void Available::HandleRegistrationStatusAccepted() {
  logser.println("already in Available state");
}

void Available::HandleTimerChange(){}
