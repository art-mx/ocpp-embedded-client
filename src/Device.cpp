#include "Device.h"
#include "States/Initialization.h"
#include "OCPP_Client.h"

Device::Device() {
  this->ChangeState(new Initialization);
  this->SetClient(new OCPP_Client(this));
}

void Device::SetClient(OCPP_Client * client){
  client_ = client;
}

void Device::AddConnector(Connector * connector) {
  connector_list_.emplace_back(connector);
}

uint8_t Device::NumConnectors() {
  return connector_list_.size();
}

void Device::ReportConnectors() {
    if (connector_list_.size()>0) {
        for (unsigned i=0; i<connector_list_.size(); ++i) {
          // check here for health of connectors
          this->client_->SendStatusNotification(connector_list_[i]->id, 
                                          ChargePointErrorCodeNames[CP_ERROR_NoError], 
                                          ChargePointStatusNames[CP_STATUS_Available]);
          delay(100);
        }
    }
}

void Device::ReportConnectorStateChange(int id) {
  this->client_->SendStatusNotification(connector_list_[id]->id, 
                                        ChargePointErrorCodeNames[connector_list_[id]->error_], 
                                        ChargePointStatusNames[connector_list_[id]->status_]);

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

Connector * Device::GetConnector(int id) {
  // TODO check if connector exists
  return connector_list_[id];
}