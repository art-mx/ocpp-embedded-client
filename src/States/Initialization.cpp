#include "States/Initialization.h"
#include "States/Operative.h"

const std::string Initialization::GetStateName() {
  return "Initialization";
}

void Initialization::StateHandle_RegistrationStatus(RegistrationStatus status) {
  switch (status) {
    case ACCEPTED:
        logser.println("got ACCEPTED RegistrationStatus");
        this->device_->ChangeState(new Operative);
        this->device_->ReportConnectors();
        break;
    case PENDING:
        logser.println("got PENDING RegistrationStatus");
        // handle this
        break;
    case REJECTED:
        logser.println("got REJECTED RegistrationStatus");
        // handle this
        break;
    case UNDEFINED:
        logser.println("got UNDEFINED RegistrationStatus");
    default:
        logser.println("unknown value for RegistrationStatus");
  }
}

void Initialization::HandleTimerChange(){}
