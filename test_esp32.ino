#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
// Wifi Credentials
const char* ssid = " 190380434500"; // Wifi SSID
const char* password = "tttt8888"; //Wi-FI Password
//const char* ssid = "TP-Link_94F8"; // Wifi SSID
//const char* password = ""; //Wi-FI Password

String host = "homeos.vn";
uint16_t port = 81;
String path = "/forwarding";
WebSocketsClient webSocketClient; // websocket client class instance
StaticJsonDocument<100> doc; // Allocate a static JSON document
String fP = "33 E4 E8 08 07 20 4C 2B 61 82 A3 A1 4B 59 1A CD 25 B5 F0 DB";
//ws://homeos.vn:81/forwarding
void setup() {
  Serial.begin(115200);
  // Connect to local WiFi
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print local IP address
 
  webSocketClient.begin(host, port, path);
  // webSocket event handler
  webSocketClient.onEvent(webSocketClientEvent);
  // if connection failed retry every 5s
  webSocketClient.setReconnectInterval(5000);
  
}
void loop() {
  webSocketClient.loop(); // Keep the socket alive
}
void webSocketClientEvent(WStype_t type, uint8_t * payload, size_t length) {
  // Make sure the screen is clear
  //  u8g2.clearBuffer();
  Serial.println("webSocketClientEvent");
  if (type == WStype_TEXT)
  {
    DeserializationError error = deserializeJson(doc, payload); // deserialize incoming Json String
    if (error) { // Print erro msg if incomig String is not JSON formated
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
  }
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocketClient.sendTXT("Connected");
      delay(1000);
      webSocketClient.sendPing((uint8_t*)("PINGPONG"));
      delay(1000);
      webSocketClient.disconnect();
      
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }
}
