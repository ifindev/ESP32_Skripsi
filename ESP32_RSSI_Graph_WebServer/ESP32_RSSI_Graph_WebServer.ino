 /* ESP32 as STA and Web Server for Real Time RSSI Graph using ESP32
 * Data streamed to the webpage is refreshed using Ajax 
 * 15th April, 2020
 * Adapted and modified from https://circuits4you.com/2018/03/10/esp8266-jquery-and-ajax-web-server/
 * Modified by Muhammad Arifin and Wafa
 * Department of Nuclear Engineering and Engineering Physics
 * Universitas Gadjah Mada, Yogyakarta, Indonesia
 */
 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "index1.h" //Our HTML webpage contents with javascripts

#define LED 27  //On board LED

//SSID and Password of your WiFi router
const char* ssid = "YOUR-SSID-WiFi-Name";
const char* password = "Wi-Fi Password";

WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC() {
  
  // RSSI data string buffer
  String rss1 = "";
  String rss2 = "";
  String rss3 = "";
  String rsstot ="";
  
  // scan network
  int numberOfNetworks = WiFi.scanNetworks(); 
  for (int i = 0; i < numberOfNetworks; i++) {
    if (WiFi.SSID(i) == "ESP32_AP1"){
      rss1 = rss1 + String(WiFi.RSSI(i));
    }
    else if (WiFi.SSID(i) == "ESP32_AP2"){
      rss2 = rss2 + String(WiFi.RSSI(i));
    }
    else if (WiFi.SSID(i) == "ESP32_AP3"){
      rss3 = rss3 + String(WiFi.RSSI(i));
    }
  }

  rsstot = rsstot + rss1 + ";" + rss2 + ";" + rss3;
  digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
  server.send(200, "text/html", rsstot);
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readADC", handleADC); //This page is called by java Script AJAX

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
