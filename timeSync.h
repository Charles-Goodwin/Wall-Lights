

#ifndef TIME_SYNC_H
#define TIME_SYNC_H
/*
 * sprintf
 * The variables are inserted at the placeholder position, and formatted based on the type of placeholder used.
 * %d = signed integer               %f = floating point number  
 * %s = string                     %.1f = float to 1 decimal place
 * %c = character                  %.3f = float to 3 decimal places
 * %e = scientific notation          %g = shortest representation of %e or %f                
 * %u = unsigned integer             %o = unsigned octal
 * %x = unsigned hex (lowercase)     %X = unsigned hex (uppercase)
 * %hd = short int                  %ld = long int
 * %lld = long long int
 * =============================================================================  */

#include <Arduino.h>
#include <TimeLib.h>

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

String fetchTime(){
  struct tm timeInfo;
  char format[10];
  if(!getLocalTime(&timeInfo)){
    Serial.println("Failed to obtain time");
    return "";
  } 
  sprintf (format, "%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min);
  return format; 
}

String fetchDate(){
  struct tm timeInfo;
  char format[10];
  int intMonth;
  if(!getLocalTime(&timeInfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  intMonth = timeInfo.tm_mon + 1;
  sprintf (format, "%02d.%02d", timeInfo.tm_mday, intMonth);
  return format;
}

void timeSync(){
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  setTime(timeinfo.tm_hour,
          timeinfo.tm_min,
          timeinfo.tm_sec,
          timeinfo.tm_mday,
          timeinfo.tm_mon + 1,
          timeinfo.tm_year +1900);
  printLocalTime();
  Serial.println(fetchDate());
  Serial.println(fetchTime());
}

void tomorrow_old_ISO8601(char isodate[30] ){

  tmElements_t tim;
  time_t tomorrow;

  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
  }

  byte _month = timeinfo.tm_mon + 1;
  int _year = timeinfo.tm_year +1900;

  tim.Second = timeinfo.tm_sec;
  tim.Hour = timeinfo.tm_hour;
  tim.Minute =  timeinfo.tm_min;
  tim.Day = timeinfo.tm_mday;
  tim.Month = _month;
  tim.Year = _year - 1970;   // offset from 1970;
  tomorrow =  makeTime(tim); // convert time elements into time_t (seconds)
  tomorrow += 86400;  //add number of seconds in a day

  sprintf(isodate, "%4d-%02d-%02dT%d:%02d:%02d.000Z", year(tomorrow), month(tomorrow), day(tomorrow), 
                                                                timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}

void tomorrow_ISO8601(char isodate[30] ){

  time_t tomorrow =  now();  // fetch time in seconds
  tomorrow += 86400;  //add number of seconds in a day

  sprintf(isodate, "%4d-%02d-%02dT%d:%02d:%02d.000Z", year(tomorrow), month(tomorrow), day(tomorrow), 
                                                                hour(tomorrow), minute(tomorrow), second(tomorrow));
}





#endif
