/* ESP32 as AP Config
 * 5 November 2019
 * Adapted and modified from https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
 * Modified by Alvin Samuel and Muhammad Arifin
 * Department of Nuclear Engineering and Engineering Physics
 * Universitas Gadjah Mada, Yogyakarta, Indonesia
 */


// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32AP1";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){}
