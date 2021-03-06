#include "rtc.h"

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib

extern HardwareSerial logser;
RTC_DS3231 rtc;
RTC_Millis rtc_millis;

static char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void init_rtc() {

  if (!rtc.begin(PB11, PB10)) {
    logser.println("Couldn't find RTC");
    logser.flush();
    abort();
  }

//   if (rtc.lostPower()) {
//     logser.println("RTC lost power, let's set the time!");
//     // When time needs to be set on a new device, or after a power loss, the
//     // following line sets the RTC to the date & time this sketch was compiled
       // rtc.adjust(DateTime(2021, 2, 26, 11, 3, 0));
//     // This line sets the RTC with an explicit date & time, for example to set
//     // January 21, 2014 at 3am you would call:
//     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//   }

//   When time needs to be re-set on a previously configured device, the
//   following line sets the RTC to the date & time this sketch was compiled
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   This line sets the RTC with an explicit date & time, for example to set
//   January 21, 2014 at 3am you would call:
//   rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

bool adjust_rtc(string dateTime) {
    /*
    datetime format: "2021-02-26T10:14:46.751Z"
    */

    int year = stoi(dateTime.substr(0,4));
    int month = stoi(dateTime.substr(5,2));
    int day = stoi(dateTime.substr(8,2));
    int hour = stoi(dateTime.substr(11,4));
    int minute = stoi(dateTime.substr(14,2));
    int second = stoi(dateTime.substr(17,2));

    logser.printf("parsed time: %i-%i-%i %i:%i:%i\r\n", year, month, day, hour, minute, second);
    DateTime datetime = DateTime(year, month, day, hour, minute, second);
    uint8_t ret = rtc.adjust(datetime);
    if (ret>0) {
        logser.printf("RTC ERROR! unable to set time!, error code=%i\r\n", ret);
        return false;
    }
    return true;
    // rtc_millis.adjust(DateTime(year, month, day, hour, minute, second));

}

string get_datetime_rtc() {
    char buff[25] = "YYYY-MM-DDThh:mm:ss.000Z";
    DateTime now = rtc.now();
    now.toString(buff);
    //logser.printf("get_datetime_rtc: %s\r\n", buff);
    return string(buff, 25);
}

void update_rtc() {
    DateTime now = rtc.now();
    logser.printf("%i-%i-%i %s %i:%i:%i, %u, runtime: %u \r\n", 
        now.year(), now.month(), now.day(), daysOfTheWeek[now.dayOfTheWeek()], now.hour(), now.minute(), now.second(), now.unixtime(), millis()); // TODO handle millis rollover

    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    //DateTime future (now + TimeSpan(7,12,30,6));

    // Serial.print(" now + 7d + 12h + 30m + 6s: ");
    // Serial.print(future.year(), DEC);
    // Serial.print('/');
    // Serial.print(future.month(), DEC);
    // Serial.print('/');
    // Serial.print(future.day(), DEC);
    // Serial.print(' ');
    // Serial.print(future.hour(), DEC);
    // Serial.print(':');
    // Serial.print(future.minute(), DEC);
    // Serial.print(':');
    // Serial.print(future.second(), DEC);
    // Serial.println();

}
