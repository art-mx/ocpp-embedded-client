#include "Requests/RemoteStopTransactionConf.h"

using std::string;


void RemoteStopTransactionConf::SetPayload(string & payload) {
  char * buf = NULL;

  string status_str = RemoteStartStopStatusNames[status_];
  int n = mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
              "status", status_str.c_str()
            );
  logser.printf("%i, generated payload %s\r\n", n, buf);
  payload.assign(buf, strlen(buf));
  free(buf);
}

void RemoteStopTransactionConf::SetStatus(RemoteStartStopStatus status) {
  status_ = status;
}

Msg RemoteStopTransactionConf::Handle(Msg & msg) {
  SetPayload(msg.response_payload);
  this->device_->client_->SendCallResult(msg);
  return msg;
}