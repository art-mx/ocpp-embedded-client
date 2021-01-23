#include "Device.h"
#include "States/Initialization.h"

Device::Device() {
  this->ChangeState(new Initialization);
}

void Device::SetClient(OCPP_Client * client){
  client_ = client;
}

void Device::ChangeState(State *state) {
  delete this->state_; // nullptr is ignored... they said
  this->state_ = state;
  this->state_->SetContext(this);
  logser.printf("changed state to %s\r\n", state->GetStateName().c_str());
}

#include "OCPP_Client.h"
void Device::Update() {
  client_->Update();
}