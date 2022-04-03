#include <time.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266SSDP.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <OneWire.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
//#include <PubSubClientTools.h>
//#include "EspMQTTClient.h"

// DS18b20 Sections //
#define DS18B20PIN 14     //14 - sonoff, 13 - kit-8
OneWire ds(DS18B20PIN);

// WEB, DNS & MQTT Sections //
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer HTTP (80);
WiFiClient wclient;
DNSServer dnsServer;
File fsUploadFile;
IPAddress ip_MQTTip (192,168,10,100);
// PubSubClient client(wclient, ip_MQTTip);
PubSubClient client(ip_MQTTip, 1883, wclient);
