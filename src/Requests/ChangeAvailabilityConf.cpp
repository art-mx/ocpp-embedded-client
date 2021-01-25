#include "Requests/ChangeAvailabilityConf.h"

using std::string;


void ChangeAvailabilityConf::SetPayload(string & payload) {
  char * buf = NULL;

  string status_str = AvailabilityStatusNames[status_];
  int n = mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
              "status", status_str.c_str()
            );
  logser.printf("%i, generated payload %s\r\n", n, buf);
  payload.assign(buf, strlen(buf));
  free(buf);
}

Msg ChangeAvailabilityConf::Handle(Msg & msg) {
  SetPayload(msg.response_payload);
  this->device_->client_->SendCallResult(msg);
  return msg;
}