/*
 * Climacell.h - library wrapper for Climacell API
 * Created by Charles Goodwin 30 May 2020
 */

#ifndef CLIMACELL_H
#define CLIMACELL_H

#include <Arduino.h>

#define HTTP_CODE_OK 200
#define BASE_URL "https://api.climacell.co/v3/"
//path queries
#define HOURLY "weather/forecast/hourly"





enum Command {
  Hourly
};



class Climacell {
  public:
    Climacell(String credentials);
    Climacell();
    String hourlyWeather(float lat, float lon, 
          String units, 
          String startTime, String endTime ,
          String fields);         
  private:
    String buildCmdURL(Command cmd);
    String _queryParams;
    String _cmdURL;
    String _baseURL;
    String _credentials;
    String _lon;
    String _lat;
    String _units;
    String _startTime;
    String _endTime;
    String _fields;
   
};


#endif
