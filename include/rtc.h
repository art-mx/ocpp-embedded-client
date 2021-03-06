#include <Arduino.h>
#include "RTClib.h"
#include <string>
void update_rtc();
void init_rtc();
bool adjust_rtc(string dateTime);
string get_datetime_rtc();