#include "Requests/BootNotificationReq.h"
using std::string;

string BootNotificationReq::Payload() {
  chargePointModel_ = "X"; // TODO
  chargePointVendor_ = "Y"; // TODO
  char * buf = NULL;
  mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
                "chargePointVendor", chargePointVendor_.c_str(),
                "chargePointModel", chargePointModel_.c_str()
              );

  string payload(buf, strlen(buf));
  free(buf);
  return payload;
}
