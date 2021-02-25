#include "Requests/RemoteStartTransactionReq.h"
#include "Requests/RemoteStartTransactionConf.h"


extern HardwareSerial logser;

RemoteStartTransactionReq::RemoteStartTransactionReq() {
    RemoteStartTransactionConf_ = new RemoteStartTransactionConf();
}

Msg RemoteStartTransactionReq::Handle(Msg & msg) { //TODO change payload to OBJECT
    int connectorId;
    string idTag;

    if (this->device_->NumConnectors() > 1) {
        if (!GetInteger(msg.payload, "$.connectorId", &connectorId)){
            logser.printf("'connectorId' key not found in payload %s\r\n", msg.payload.c_str());
            return msg;
        }
    } else connectorId = 0;

    if (!GetString(msg.payload, "$.idTag", idTag)) {
        logser.printf("'type' key not found in payload %s\r\n", msg.payload.c_str());
        return msg;
    }
    RemoteStartTransactionConf_->SetStatus(REMOTE_STATUS_ACCEPTED);


    // AvailabilityStatus status = this->device_->state_->StateHandle_AvailabilityStatus(availability);
    

    this->SetNext(RemoteStartTransactionConf_);
    AbstractHandler::Handle(msg);

    // check if connector is available ?
    
    // if AuthorizeRemoteTxRequests is set
        // check idTag in localList 
        // if no idTag in localList
            // send AuthorizationRequest
    // else
        //send StartTransaction request




        delay(100);
        this->device_->client_->SendStartTransaction(connectorId, idTag, 0, "2021-02-25T13:01:23.684Z");
    return msg;
    
}