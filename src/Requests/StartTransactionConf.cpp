#include "Requests/StartTransactionConf.h"

Msg StartTransactionConf::Handle(Msg & msg) {
    int transactionId;
    string status_str;
    string expiryDate;
    /*
    example response: [3,"4",{"transactionId":8,"idTagInfo":{"status":"Accepted","expiryDate":"2021-02-26T13:47:44.433Z"}}]
    */
    logser.printf("handled CallResult to %s\r\n", msg.action.c_str());
    // store transaction id
    if (!GetInteger(msg.payload, "$.transactionId", &transactionId)){
        logser.printf("'transactionId' key not found in payload %s\r\n", msg.payload.c_str());
        return msg;
    }
    if(!FindKey(msg.payload, "$.idTagInfo")) {
        logser.printf("'idTagInfo' key not found in payload %s\r\n", msg.payload.c_str()); 
        return msg;
    }
    if(!GetString(msg.payload, "$.idTagInfo.status", status_str)) {
        logser.printf("'idTagInfo.status' not found in payload %s\r\n", msg.payload.c_str()); 
        return msg;
    }
    if(!GetString(msg.payload, "$.idTagInfo.expiryDate", expiryDate)) {
        logser.printf("'idTagInfo.expiryDate' not found in payload %s\r\n", msg.payload.c_str()); 
        return msg;
    }
    // store transactionId

    AuthorizationStatus status = AuthorizationStatusMap[status_str];
    switch (status) {
        case AUTH_STATUS_ACCEPTED:
            // Identifier is allowed for charging
            device_->client_->SetCurrentTransactionId(transactionId);
            logser.printf("\r\n\r\nTRANSACTION #%i STARTED.\r\n", transactionId);
            //TODO get connector which is used in this transaction
            this->device_->GetConnector(0)->SetStatus(CP_STATUS_Charging, CP_ERROR_NoError); 
            this->device_->ReportConnectorStateChange(0);
            break;
        case AUTH_STATUS_BLOCKED:
            // Identifier has been blocked. Not allowed for charging.
            logser.println("got AUTH_STATUS_BLOCKED");
            break;
        case AUTH_STATUS_EXPIRED:
            // Identifier has expired. Not allowed for charging.
            logser.println("got AUTH_STATUS_EXPIRED");
            break;
        case AUTH_STATUS_INVALID:
            // Identifier is unknown. Not allowed for charging.
            logser.println("got AUTH_STATUS_INVALID");
            break;
        case AUTH_STATUS_CONCURRENTTX:
            // Identifier is already involved in another transaction
            logser.println("got AUTH_STATUS_CONCURRENTTX");
            break;
        default:
            logser.println("unknown AuthorizationStatus");
            break;
    }
    return msg;
}   