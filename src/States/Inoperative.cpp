#include "States/Inoperative.h"
#include "States/Operative.h"

const std::string Inoperative::GetStateName() {
  return "Inoperative";
}

AvailabilityStatus Inoperative::StateHandle_AvailabilityStatus(AvailabilityType type) {
  switch (type) {
      case OPERATIVE:
        this->device_->ChangeState(new Operative());
        return AVAIL_STATUS_ACCEPTED;
      case INOPERATIVE:
      this->device_->ChangeState(new Inoperative());
        return AVAIL_STATUS_ACCEPTED;
  }
}

void Inoperative::HandleTimerChange(){}
