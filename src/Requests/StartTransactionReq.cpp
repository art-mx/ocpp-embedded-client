#include "Requests/StartTransactionReq.h"

using std::string;

string StartTransactionReq::Payload(int connector, string idTag, int meterStart, string timestamp) {
  char * buf = NULL;
  mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
                "connectorId", connector,
                "idTag", idTag.c_str(),
                "meterStart", meterStart,
                "timestamp", timestamp.c_str()
              );

  string payload(buf, strlen(buf));
  free(buf);
  return payload;
}
