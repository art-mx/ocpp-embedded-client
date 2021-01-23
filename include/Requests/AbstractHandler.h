#pragma once
#include <Arduino.h>
using std::string;


struct Request {
    string raw_message;
};

class Handler {
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual string & Handle(string & msg) = 0;

};


class AbstractHandler : public Handler {
 private:
  Handler *next_handler_;

 public:
  AbstractHandler() : next_handler_(nullptr) {}
  virtual ~AbstractHandler() = default;

  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
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