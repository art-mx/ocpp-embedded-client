#include "States/Operative.h"
#include "States/Inoperative.h"
#include "OCPP_Client.h" 

const std::string Operative::GetStateName() {
  return "Operative";
}

// void Operative::StateHandle_RegistrationStatus(RegistrationStatus status) {
//   // logser.println("already in Operative state");
// }

AvailabilityStatus Operative::StateHandle_AvailabilityStatus(AvailabilityType type) {
  switch (type) {
      case OPERATIVE:
          this->device_->ChangeState(new Operative());
          return AVAIL_STATUS_ACCEPTED;
      case INOPERATIVE:
          this->device_->ChangeState(new Inoperative());
          return AVAIL_STATUS_ACCEPTED;
      default:
        return AVAIL_STATUS_UNDEFINED;
  }
}


void Operative::HandleTimerChange(){}
