#pragma once
#include <Arduino.h>
#include "mjson.h"
using std::string;

bool GetDouble(const string & msg, const string & key, double * value);

bool GetInteger(string & msg, const string & key, int * value);

bool GetObject(string & msg, const char * key, string & value);

bool GetString(const string & msg, const char * key, string & value);

int check_if_frame_is_complete(char * buf, int len, string & frame);

