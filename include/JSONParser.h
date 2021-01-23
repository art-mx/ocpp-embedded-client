#pragma once
#include <Arduino.h>
#include "mjson.h"
using std::string;

bool GetDouble(const string & payload, const string & key, double * value);

bool GetInteger(string & payload, const string & key, int * value);

bool GetString(const string & payload, const string & key, string & value);

int check_if_frame_is_complete(char * buf, int len, string & frame);

