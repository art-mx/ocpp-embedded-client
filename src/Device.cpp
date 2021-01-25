#include "Device.h"
#include "States/Initialization.h"
#include "OCPP_Client.h"

Device::Device() {
  this->ChangeState(new Initialization);
  this->SetClient(new OCPP_Client(this));
  // this->client_->SetDevice(this);
}

void Device::SetClient(OCPP_Client * client){
  client_ = client;
}

void Device::AddConnector(Connector * connector) {
  connector_list_.emplace_back(connector);
}

void Device::ReportConnectors() {
    if (connector_list_.size()>0) {
        for (unsigned i=0; i<connector_list_.size(); ++i) {
          // check here for health of connectors
          this->client_->SendStatusNotification(connector_list_[i]->id, 
                                          ChargePointErrorCodeNames[CP_ERROR_NoError], 
                                          ChargePointStatusNames[CP_STATUS_Available]);
        }
    }
}

void Device::ChangeState(State *state) {
  delete this->state_; // nullptr is ignored... they said
  this->state_ = state;
  this->state_->SetContext(this);
  logser.printf("changed state to %s\r\n", state->GetStateName().c_str());
}

void Device::Update() {
  client_->Update();
}