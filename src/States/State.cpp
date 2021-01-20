#include "States/State.h"

uint32_t State::GetTimerValue() {
  return millis() - last_state_change_millis_;
}

void State::SetContext(Device* context) {
  last_state_change_millis_ = millis();
  this->device_ = context;
}

void State::UpdateTimerValue() {
  last_state_change_millis_ = millis();
}