#pragma once
#include <Arduino.h>
using std::string;
#include "Device.h"
extern HardwareSerial logser;


struct Request {
    string raw_message;
};


class Handler {
public:
    // Device * device_;
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual string & Handle(string & msg) = 0;
    virtual void SetDevice(Device * device) = 0;

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

  virtual ~AbstractHandler() = default;

  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
    this->next_handler_->SetDevice(device_);
    return handler;
  }

  string & Handle(string & msg) override {
    if (this->next_handler_) {
      Handler* next = this->next_handler_;

      // delete this;
      return next->Handle(msg);
    }
    return msg;
  }
};