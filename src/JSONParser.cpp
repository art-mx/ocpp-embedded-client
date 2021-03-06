#include "JSONParser.h"
extern HardwareSerial logser;

bool GetDouble(const string & msg, const string & key, double * value) {
  double raw_value;
  int result = mjson_get_number(msg.c_str(), msg.length(), key.c_str(), &raw_value);
  *value = raw_value; 
  return result == 0 ? false : true;
}

bool GetInteger(string & msg, const string & key, int * value) {
  double raw_value;
  bool res = GetDouble(msg, key, &raw_value);
  *value = static_cast<int>(raw_value);
  return res;
}

bool GetString(const string & msg, const char * key, string & value) {
  char buff[200];
  int n = mjson_get_string(msg.c_str(), msg.length(), key, buff, sizeof(buff));
  if (n > 0) {
      value.assign(buff, n);
      return true;
  }
  return false;
}

bool FindKey(const string & msg, const char * key) {
    const char *p;
    int sz;
    if (mjson_find(msg.c_str(), msg.length(), key, &p, &sz) > 0) return true;
    else return false;
}

bool GetObject(string & msg, const char * key, string & value) {
    const char *p;
    int n;
    if (mjson_find(msg.c_str(), msg.length(), key, &p, &n) == MJSON_TOK_OBJECT) {
        value.assign(p, n);
        return true;
    }
    else {
        return false;
    }
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