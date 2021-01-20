#include "Requests/Message.h"

using std::string;

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
