#include "Requests/StopTransactionConf.h"

Msg StopTransactionConf::Handle(Msg & msg) {

    string status_str;
    string expiryDate;
    /*
    example response: [3,"4",{}]
    */
    logser.printf("handled CallResult to %s\r\n", msg.action.c_str());
    //TODO get connector which is used in this transaction
    this->device_->GetConnector(0)->SetStatus(CP_STATUS_Available, CP_ERROR_NoError); 
    this->device_->ReportConnectorStateChange(0);
    return msg;
}   