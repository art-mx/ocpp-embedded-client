#include "Requests/RemoteStopTransactionReq.h"
#include "Requests/RemoteStopTransactionConf.h"
#include "Requests/StopTransactionReq.h"
#include "rtc.h"

extern HardwareSerial logser;
extern HardwareSerial comser;

RemoteStopTransactionReq::RemoteStopTransactionReq() {
    RemoteStopTransactionConf_ = new RemoteStopTransactionConf();
    StopTransactionReq_ = new StopTransactionReq();
}

Msg RemoteStopTransactionReq::Handle(Msg & msg) {
    int transactionId;
    RemoteStartStopStatus resp_status = REMOTE_STATUS_UNDEFINED;

    // if payload missing transactionId
    if(!GetInteger(msg.payload, "$.transactionId", &transactionId)) {
        logser.printf("'transactionId' key not found in payload %s\r\n", msg.payload.c_str());
        resp_status = REMOTE_STATUS_REJECTED;
    } else {
        // if currect transaction id matches received id
        int id = device_->client_->GetCurrentTransactionId();
        if (id != transactionId) {
            logser.printf("current 'transactionId' %i doesn't match received id %i in payload %s\r\n", id, transactionId, msg.payload.c_str());
            resp_status = REMOTE_STATUS_REJECTED;
        }
    }
    // respond with status
    if(!resp_status) resp_status = REMOTE_STATUS_ACCEPTED;
    RemoteStopTransactionConf_->SetStatus(resp_status);
    this->SetNext(RemoteStopTransactionConf_);
    AbstractHandler::Handle(msg);

    // if no errors above
    if (resp_status == REMOTE_STATUS_ACCEPTED) {
        logser.printf("transaction %i has stopped.\r\n", transactionId);
        logser.printf("\r\nCHARGING STOPPED!\r\n\r\n");
        // TODO calculate meter values
        this->device_->client_->SendStopTransaction(this->device_->GetMeterValueForTransaction(transactionId), get_datetime_rtc(), transactionId, STOP_TRANS_REMOTE);
        comser.flush();
        //TODO get connector which is used in this transaction
        this->device_->GetConnector(0)->SetStatus(CP_STATUS_Finishing, CP_ERROR_NoError); 
        this->device_->ReportConnectorStateChange(0);
    }
    
    return msg;
}