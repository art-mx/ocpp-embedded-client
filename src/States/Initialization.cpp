#include "States/Initialization.h"
#include "States/Available.h"

const std::string Initialization::GetStateName() {
  return "Initialization";
}

void Initialization::HandleRegistrationStatusAccepted() {
  this->device_->ChangeState(new Available);
}

void Initialization::HandleTimerChange(){}
