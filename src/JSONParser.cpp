#include "JSONParser.h"

bool GetDouble(const string & payload, const string & key, double * value) {
  double raw_value;
  int result = mjson_get_number(payload.c_str(), payload.length(), key.c_str(), &raw_value);
  *value = raw_value; 
  return result == 0 ? false : true;
}

bool GetInteger(string & payload, const string & key, int * value) {
  double raw_value;
  bool res = GetDouble(payload, key, &raw_value);
  *value = static_cast<int>(raw_value);
  return res;
}

bool GetString(const string & payload, const string & key, string & value) {
  char buff[100];
  int result = mjson_get_string(payload.c_str(), payload.length(), key.c_str(), buff, sizeof(buff));
  if (result == 0) {
      return false;
  }
  value = buff;
  return true;
}

int check_if_frame_is_complete(char * buf, int len, string & frame) {
    int n = mjson(buf, len, NULL, NULL);
    if (n == 0) {
        // Not full JSON object was buffered
        return 0; 
    } else if (n < 0) {
        //handle_error(); // Invalid JSON
        return -1;
    } else {
        // JSON object length is `n`. Parse, and then remove n bytes from the input
        frame.assign(buf, n);
        return 1;
    }
}