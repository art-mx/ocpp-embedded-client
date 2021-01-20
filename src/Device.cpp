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
}

void Device::Update() {
  // client_->Update();
}