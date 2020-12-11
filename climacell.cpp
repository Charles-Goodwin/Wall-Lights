/*
  climacell.cpp - Library wrapper for Climacell API.
  Created by Charles Goodwin, 30 April 2020.
  
*/
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>



#include "climacell.h"
//Climacell
#define BASE_URL "https://api.climacell.co/v3/"
//path queries
#define HOURLY "weather/forecast/hourly"


Climacell::Climacell(String credentials) {
  _baseURL = BASE_URL;
  _credentials = credentials;

}

//Climacell::Climacell();

String Climacell::buildCmdURL(Command cmd) {
  switch (cmd){
    case Hourly:{
      Serial.println("Command is Hourly");
      String _queryParams = "?";
      _queryParams += "lon=" + _lon;
      _queryParams += "&lat=" + _lat;
      if (_units !="") _queryParams += "&unit_system=" + _units;
      _queryParams += "&start_time=" + _startTime;
      if (_endTime !="") _queryParams += "&end_time=" + _endTime;
      if (_fields !="") _queryParams += "&fields=" + _fields;
      _queryParams += "&apikey="+ _credentials;
      _cmdURL = _baseURL + HOURLY + _queryParams;
      return _cmdURL;  
    }
    default: {
      Serial.print("Invalid Command");
      break;
    }
  }
}

String Climacell::hourlyWeather(float lat, float lon, 
          String units, 
          String startTime, String endTime ,
          String fields) {

  //Set up new secure client
       
  _lat = lat;
  _lon = lon;
  _units = units;
  _startTime = startTime;
  _endTime = endTime;
  _fields = fields;

  WiFiClientSecure *client = new WiFiClientSecure;
  Serial.println("Set up secure client"); 

  if(client) { //Check client created successfully 
    Serial.println("Client created successfully");  
    {      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
 
      Serial.println("Create https object");
      Serial.println("[HTTPS] begin...");
      //if (https.begin(*client, "https://postman-echo.com/get")) {
      
      if (https.begin(*client, buildCmdURL(Hourly))) {  // HTTPS
        Serial.println(buildCmdURL(Hourly));
        //Add bearer token to header
              
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK) {
            String payload = https.getString();
            //Serial.println(payload);
            return payload;
          }
        } else {
          Serial.printf("[HTTPS] GET... failed");
        }
  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
      Serial.print("End extra scoping block");
      // End extra scoping block
    }
    Serial.print("About to delete client");
    delete client;
    Serial.print("Client deleted");
  } else {
    Serial.println("Unable to create client");
  }
  
}

  
  
  
 
  
