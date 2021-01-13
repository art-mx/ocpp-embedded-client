#include "Requests/BootNotificationReq.h"


using namespace std;

BootNotificationReq::BootNotificationReq() {
  chargePointModel_ = "X"; // TODO
  chargePointVendor_ = "Y"; // TODO
}

string BootNotificationReq::GetPayload() {
  char *s = NULL;
  mjson_printf(&mjson_print_dynamic_buf, &s, payload_format,
                "chargePointVendor", chargePointVendor_.c_str(),
                "chargePointModel", chargePointModel_.c_str()
              );
  return s;
}