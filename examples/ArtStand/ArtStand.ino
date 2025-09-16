/*
  Art Stand / Exhibition Stand Example
  ---------------------------
  Usage scenario:
  - When the device is plugged in to the visitor's location, it automatically searches for Wi-Fi information.
  - If no information is already registered, ESP initializes its own Access Point (AP). SSID: "ESP_Setup"
  - Connect to the "ESP_Setup" network with your phone or tablet.
  - Enter http://192.168.4.1/wifi from your browser.
  - A POST request is sent in the following JSON format:
  { "ssid":"YourHome'sWi-FiSSID", "password":"YourHome'sWi-FiPassword" }
*/

#include <ESPWiFiManagerByDroidbane.h>

ESPWiFiManagerByDroidbane wifiManagerByDroidbane("ESP_Setup");

void setup() {
  Serial.begin(115200);

  // Automatically attempts to load previously saved Wi-Fi information.
  // If there is no record, it activates its AP mode. It also activates HTTP endpoints:
  // /wifi -> Sends the SSID and password via POST
  // /restart -> Restarts the device
  // /wifi-update -> Deletes the saved information
  ESPWiFiManagerByDroidbane.begin();

  // Example: For the Art Exhibition application
  // After establishing the connection, you can add your own HTTP endpoint.

}

void loop() {
  // Continuously listens for HTTP requests
  wifiManager.handle();
}
