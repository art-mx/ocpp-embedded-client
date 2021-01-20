#include "States/Initialization.h"
#include "States/Operational.h"

const char* Initialization::GetStateName() {
  return "Initialization";
}

void Initialization::HandleRegistrationStatusAccepted() {
  logser.println("Handle Registration Status Accepted");
  // this->device_->ChangeState(new Operational);
}

void Initialization::HandleTimerChange(){}
