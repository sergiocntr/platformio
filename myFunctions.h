#ifndef myFunctions_h
#define myFunctions_h
#include "pitches.h"
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>
#include <topic.h>
#include <myIP.h>
#include "password.h"
//HTTPClient http;
WiFiClient c;
PubSubClient client(c);
IPAddress ip;
const char* mqttID;
const char* remote_host = "www.google.com";
uint8_t mqtt_reconnect_tries = 0;
unsigned long wifi_reconnect_time;
unsigned long wifi_check_time = 15000;

uint8_t checkForUpdates(uint16_t FW_VERSION) {
  //Serial.println( "Checking for firmware updates." );
  //Serial.print( "Current firmware version: " );
  ////Serial.println( FW_VERSION );
uint8_t check=0;
String fwURL = String( fwUrlBase );
fwURL.concat( mqttID );
String fwVersionURL = fwURL;
fwVersionURL.concat( "/version.php" );
//Serial.print( "Firmware version URL: " );
//Serial.println( fwVersionURL );

String fwImageURL = fwURL;
fwImageURL.concat( "/firmware.bin" );
  //Serial.print( "Firmware  URL: " );
  //Serial.println( fwImageURL );
//#ifdef HTTP_ON
  WiFiClient myUpdateConn;
  HTTPClient http;
  http.begin( myUpdateConn, fwVersionURL );
  int httpCode = http.GET();
  if( httpCode == 200 ) {
    String newFWVersion = http.getString();
    int newVersion = newFWVersion.toInt();
    if( newVersion > FW_VERSION ) {
    //  //Serial.println( "Preparing to update" );
      t_httpUpdate_return ret = ESPhttpUpdate.update(myUpdateConn , fwImageURL );
      switch(ret) {
        case HTTP_UPDATE_FAILED:
          check=1;
          //Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          check=2;
          //Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;
        case HTTP_UPDATE_OK:
          //Serial.println("[update] Update ok."); // may not called we reboot the ESP
          break;
      }
    }
    else {
      check=0;
      //Serial.println( "Already on latest version" );
    }
  }
  else {
    //Serial.print( "Firmware version check failed, got HTTP response code " );
    //Serial.println( httpCode );
    check= httpCode;
  }
  http.end();
  myUpdateConn.stop();
  return check;
}
int8_t connectMQTT(){
  if(client.state()==0){
    //DDEBUG_PRINT("MQTT_ALREADY_CONNECTED");
    return 0;
  }
  unsigned long wifi_initiate = millis();
  String clientId = String(mqttID);
  clientId += String(random(0xffff), HEX);
  yield();
  while ((!client.connected()) && ((millis() - wifi_initiate) < 3000)){
    client.connect(clientId.c_str(),mqttUser,mqttPass);
    while((millis() - wifi_initiate) < 900){
      client.loop();
      delay(100);
    }

  }
  return client.state();
  //return client.state();
      /*switch (check) {
          case -4:
            //DDEBUG_PRINT("MQTT_CONNECTION_TIMEOUT");
            break;
          case -3:
            //DDEBUG_PRINT("MQTT_CONNECTION_LOST");
            break;
          case -2:
            //DDEBUG_PRINT("MQTT_CONNECT_FAILED");
            break;
          case -1:
            //DDEBUG_PRINT("MQTT_DISCONNECTED");
            break;
          case 0:
            //DDEBUG_PRINT("MQTT_CONNECTED");
            break;
          case 1:
            //DDEBUG_PRINT("MQTT_CONNECT_BAD_PROTOCOL");
            break;
          case 2:
            //DDEBUG_PRINT("MQTT_CONNECT_BAD_CLIENT_ID");
            break;
          case 3:
            //DDEBUG_PRINT("MQTT_CONNECT_UNAVAILABLE");
            break;
          case 4:
            //DDEBUG_PRINT("MQTT_CONNECT_BAD_CREDENTIALS");
            break;
          case 5:
            //DDEBUG_PRINT("MQTT_CONNECT_UNAUTHORIZED");
            break;
          default:
            //DDEBUG_PRINT("MQTT_UNKNOWN_ERROR");
            break;
        }*/
      ////DDEBUG_PRINT(" try again in 5 seconds");
      //delay(5000);
  //  }
  //}
  //return client.state();
}
int send(const char* topic, String message){
  int check = client.publish(topic, message.c_str(), true);
  client.loop();
  return check;
}
int send(const char* topic, const char* message){
  int check = client.publish(topic, message, true);
  client.loop();
  return check;
}
void setIP(IPAddress myIP,const char* mymqID){
  ip=myIP;
  mqttID=mymqID;
}
uint8_t connectWiFi(){
  //Serial.print( "dentro conn wifi " );
  delay(100);
  if(WiFi.status() == WL_CONNECTED) return 0;
  //Serial.println( "0" );
  WiFi.mode(WIFI_STA);
  WiFi.forceSleepWake();
  delay(10);
  //Serial.println( "1" );
  WiFi.config(ip, gateway, subnet,dns1); // Set static IP (2,7s) or 8.6s with DHCP  + 2s on battery
  delay(10);
  WiFi.begin(ssid, password);
  unsigned long wifi_initiate = millis();
  //Serial.println( "2" );
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if ((millis() - wifi_initiate) > 5000L) {
      //Serial.println( "3" );
      wifi_set_sleep_type(LIGHT_SLEEP_T);
      WiFi.mode(WIFI_OFF); //energy saving mode if local WIFI isn't connected
      WiFi.forceSleepBegin();
      delay(10);
      return 1;
    }
    delay(500);

  }
  //Serial.println( "4" );
  wifi_initiate = millis();
  while (!c.connect("www.google.com", 80 )) {
  //while(!Ping.ping(remote_host)){
    if (millis() - wifi_initiate > 5000L) {
      //Serial.println( "5" );
      return  2;
    }
    delay(500);
  }
  //Serial.println( "6" );
  return 0;
}
#endif
