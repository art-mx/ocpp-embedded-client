#include "Requests/StatusNotificationReq.h"
using std::string;

string StatusNotificationReq::Payload(int connector, string error, string status) {

  char * buf = NULL;
  mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
                "connectorId", connector,
                "errorCode", error.c_str(),
                "status", status.c_str()
              );

  string payload(buf, strlen(buf));
  free(buf);
  return payload;
}
