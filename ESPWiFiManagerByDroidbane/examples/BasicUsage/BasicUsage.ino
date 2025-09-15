#include <ESPWiFiManager.h>

ESPWiFiManagerByDroidbane wifiManagerByDroidbane("ESP_Setup");

void setup() {
    wifiManager.begin();
}

void loop() {
    wifiManager.loop();
}
