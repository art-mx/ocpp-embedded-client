#include "States/Initialization.h"
#include "States/Operational.h"

const std::string Initialization::GetStateName() {
  return "Initialization";
}

void Initialization::HandleRegistrationStatusAccepted() {
  this->device_->ChangeState(new Operational);
}

void Initialization::HandleTimerChange(){}
