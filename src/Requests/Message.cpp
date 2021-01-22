#include "Requests/Message.h"

using std::string;
// Message::Message(Message const& p): Message(p) {};

void Message::MessageHandler(string & msg) {
    int id;
    double raw_value;

    if (!mjson_get_number(msg.c_str(), msg.length(), "$[0]", &raw_value)) {
        logser.println("message type not found");
        return;
    }
    id = static_cast<int>(raw_value);
    switch (id) {
        case CALLRESULT:
            logser.println("got CALLRESULT");
            // CallResult * call_result = new CallResult(msg);
            // ProcessCallResult(msg);
            break;
        case CALLERROR:
            logser.println("got CALLERROR");
            // ProcessCallError(msg);
            break;
        case CALL:
            logser.println("got CALL");
            // ProcessCall(msg);
            break;
        default:
            logser.println("got UNDEFINED MessageType\r\n");
            break;
    }
}

bool Message::GetDouble(const string & payload, const string & key, double * value) {
  double raw_value;
  int result = mjson_get_number(payload.c_str(), payload.length(), key.c_str(), &raw_value);
  *value = raw_value; 
  return result == 0 ? false : true;
}

bool Message::GetInteger(string & payload, const string & key, int * value) {
  double raw_value;
  bool res = GetDouble(payload, key, &raw_value);
  *value = static_cast<int>(raw_value);
  return res;
}

bool Message::GetString(const string & payload, const string & key, string & value) {
  char buff[100];
  int result = mjson_get_string(payload.c_str(), payload.length(), key.c_str(), buff, sizeof(buff));
  if (result == 0) {
      return false;
  }
  value = buff;
  return true;
}

bool Message::GetPayload(string & msg, string & Payload) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), Payload_key, &p, &n) == MJSON_TOK_OBJECT) {
        Payload.assign(p, n);
        return true;
    }
    else {
        return false;
    }
}

bool Message::GetUniqueId(string & msg, string & UniqueId) {
    char buff[100];
    int result = mjson_get_string(msg.c_str(), msg.length(), UniqueId_key, buff, sizeof(buff));
    if (result == 0) {
        return false;
    }
    UniqueId = buff;
    return true;
}

bool Message::GetAction(string & msg, string & action) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), Action_key, &p, &n) == MJSON_TOK_STRING) {
        action.assign(p, n);
        return true;
    }
    else {
        return false;
    }
}