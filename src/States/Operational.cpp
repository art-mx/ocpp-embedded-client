#include "States/Initialization.h"
#include "States/Operational.h"

const std::string Operational::GetStateName() {
  return "Operational";
}

void Operational::HandleRegistrationStatusAccepted() {
  logser.println("already in Operational");
  // this->device_->ChangeState(new Operational(0));
}

void Operational::HandleTimerChange(){}
