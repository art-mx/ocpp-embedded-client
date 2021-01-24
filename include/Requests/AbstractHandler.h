#pragma once
#include <Arduino.h>
using std::string;
#include "Device.h"
extern HardwareSerial logser;
#include "Types/Types.h"

struct Msg {
  string raw;
  int type;
  string uid;
  string action;
  string payload;
  string response_payload;
};


class Handler {
public:
    // Device * device_;
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual Msg Handle(Msg & msg) = 0;
    virtual void SetDevice(Device * device) = 0;
    virtual ~Handler() = default;
};


class AbstractHandler : public Handler {
 private:
  Handler *next_handler_;
 public:
  Device * device_;
  void SetDevice(Device * device) override { 
    device_= device;
  }
  AbstractHandler() : next_handler_(nullptr) {}
  
  // https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP52-CPP.+Do+not+delete+a+polymorphic+object+without+a+virtual+destructor
  virtual ~AbstractHandler() = default;

  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
    this->next_handler_->SetDevice(device_);
    return handler;
  }

  Msg Handle(Msg & msg) override {
    if (this->next_handler_) {
      Handler* next = this->next_handler_;
      // TODO
      // delete this;
      return next->Handle(msg);
    }
    return msg;
  }
};