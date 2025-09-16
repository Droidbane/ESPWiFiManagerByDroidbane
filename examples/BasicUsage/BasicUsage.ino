/* Setup Wi-Fi Connection (never forgets the connection)
 *
 * POST http://<ESP IP>/wifi
 * Body: ssid=<Your Home's WiFi SSID>&password=<Your Home's WiFi Password>
*/


/* Delete Wi-Fi Connection
 *
 * POST http://<ESP IP>/wifi-update
*/


/* Restart Device
 *
 * POST http://<ESP IP>/restart
*/
#include <ESPWiFiManager.h>

// Wi-Fi name in setup mode.
ESPWiFiManagerByDroidbane wifiManagerByDroidbane("ESP_Setup");

void setup() {
    Serial.begin(115200);

    // Automatic Wi-Fi connection or setup mode start.
    wifiManager.begin();
}

void loop() {
    // Listen for HTTP requests.
    wifiManager.loop();

    // your code...
}
