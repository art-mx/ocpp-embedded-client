#pragma once
#include <Arduino.h>
using std::string;

extern HardwareSerial logser;


struct Request {
    string raw_message;
};


class Handler {
public:
    // Device * device_;
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual string & Handle(string & msg) = 0;

};


class AbstractHandler : public Handler {
 private:
  Handler *next_handler_;
 public:
  // Device * device_;
  // AbstractHandler(Device * device) :  next_handler_(nullptr), device_(device) {}
  AbstractHandler() : next_handler_(nullptr) {}

  virtual ~AbstractHandler() = default;

  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
    // AbstractHandler::next_handler_->device_ = device_;
    return handler;
  }

  string & Handle(string & msg) override {
    if (this->next_handler_) {
      Handler* next = this->next_handler_;
      // if (this->device_ != nullptr) {
      //   logser.println(next->device_->bla);
      // }
      // delete this;
      return next->Handle(msg);
    }
    return msg;
  }
};