#include "Requests/StopTransactionReq.h"

using std::string;

string StopTransactionReq::Payload(int meterStop, string timestamp, int transactionId, StopTransactionReason reason) {
    char * buf = NULL;
    mjson_printf(&mjson_print_dynamic_buf, &buf, payload_format,
                "meterStop", meterStop,
                "timestamp", timestamp.c_str(),
                "transactionId", transactionId,
                "reason", StopTransactionReasonNames[reason].c_str()
                );

    string payload(buf, strlen(buf));
    free(buf);
    return payload;
}
