#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "config.h"

void setup() 
{
  Serial.begin(9600);
  Serial.println("STARTED");

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void SendGetRequest()
{
  HTTPClient http;

  String serverPath = "http://worldclockapi.com/api/json/est/now";

  http.begin(serverPath.c_str());

  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}

void loop() 
{
  SendGetRequest();

  delay(3000);
}
