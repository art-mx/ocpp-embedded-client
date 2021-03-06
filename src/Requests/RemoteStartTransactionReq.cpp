#include "Requests/RemoteStartTransactionReq.h"
#include "Requests/RemoteStartTransactionConf.h"
#include "rtc.h"

extern HardwareSerial logser;
extern HardwareSerial comser;

RemoteStartTransactionReq::RemoteStartTransactionReq() {
    RemoteStartTransactionConf_ = new RemoteStartTransactionConf();
}

Msg RemoteStartTransactionReq::Handle(Msg & msg) { //TODO change payload to OBJECT
    int connectorId;
    string idTag;
    RemoteStartStopStatus resp_status = REMOTE_STATUS_UNDEFINED;

    // check connectorId 
    if (this->device_->NumConnectors() > 1) {
        if (!GetInteger(msg.payload, "$.connectorId", &connectorId)){
            logser.printf("'connectorId' key not found in payload %s\r\n", msg.payload.c_str());
            resp_status = REMOTE_STATUS_REJECTED;
        }
    } else {
        // message should not contain connectorId as this station has just 1 connector.
        if(!FindKey(msg.payload, "$.connectorId")) {
            connectorId = 0;
        } else {
            // unexpected
            resp_status = REMOTE_STATUS_REJECTED;
            logser.println("message should not contain connectorId as this station has just 1 connector\r\n");
        }
    }

    if (!GetString(msg.payload, "$.idTag", idTag)) {
        logser.printf("'type' key not found in payload %s\r\n", msg.payload.c_str());
        resp_status = REMOTE_STATUS_REJECTED;
    }

    // check if connector is inoperable
        //resp_status = REMOTE_STATUS_REJECTED;

    if(!resp_status) resp_status = REMOTE_STATUS_ACCEPTED;
    RemoteStartTransactionConf_->SetStatus(resp_status);
    this->SetNext(RemoteStartTransactionConf_);
    AbstractHandler::Handle(msg);

    // if no errors above
    if (resp_status == REMOTE_STATUS_ACCEPTED) {
        // if AuthorizeRemoteTxRequests is set
            // check idTag in localList 
            // if no idTag in localList
                // send AuthorizationRequest
        // else
        this->device_->client_->SendStartTransaction(connectorId, idTag, 0, get_datetime_rtc());
        comser.flush();
        this->device_->GetConnector(connectorId)->SetStatus(CP_STATUS_Preparing, CP_ERROR_NoError); //doc p.39 A2
        this->device_->ReportConnectorStateChange(connectorId);
    }

    return msg;
    
}