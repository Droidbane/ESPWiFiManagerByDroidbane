#include "ESPWiFiManager.h"

ESPWiFiManager::ESPWiFiManager(const char* apSSID) 
: server(80), apSSID(apSSID), connected(false) {}

void ESPWiFiManager::begin() {
    Serial.begin(115200);

    // Önce kaydedilmiş Wi-Fi bilgilerini dene
    String savedSsid, savedPass;
    if (loadCredentials(savedSsid, savedPass)) {
        connectToWiFi(savedSsid, savedPass);
    }

    // Bağlanamazsa AP aç
    if (!connected) {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(apSSID);
        Serial.println("\nAP modu başlatıldı");
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
    }

    // HTTP server endpoint
    server.on("/wifi", [this]() { handleWifi(); });
    server.on("/wifi-update", [this]() { handleWifiUpdate(); });
    server.on("/restart", [this]() { handleRestart(); });
    server.begin();
    Serial.println("HTTP server başlatıldı");
}

void ESPWiFiManager::loop() {
    server.handleClient();
}

// Wi-Fi bağlantısı
void ESPWiFiManager::connectToWiFi(const String &ssid, const String &password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("WiFi'ye bağlanılıyor");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        Serial.println("\nWiFi'ye bağlandı!");
        Serial.print("IP adresi: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi'ye bağlanılamadı!");
    }
}

// HTTP endpointler
void ESPWiFiManager::handleWifi() {
    if (server.method() == HTTP_POST) {
        String cacheSsid = server.arg("ssid");
        String cachePassword = server.arg("password");
        Serial.println("Gelen SSID: " + cacheSsid);
        Serial.println("Gelen Password: " + cachePassword);

        if (saveCredentials(cacheSsid.c_str(), cachePassword.c_str())) {
            server.send(200, "text/plain", "OK");
            Serial.println("Şifre kaydedildi. Cihaz yeniden başlatılıyor...");
            ESP.restart();
        } else {
            server.send(500, "text/plain", "Kayit hatasi");
        }
    } else {
        server.send(405, "text/plain", "Sadece POST destekleniyor!");
    }
}

void ESPWiFiManager::handleRestart() {
    if (server.method() == HTTP_POST) {
        server.send(200, "text/plain", "Cihaz yeniden başlatılıyor...");
        delay(500);
        ESP.restart();
    } else {
        server.send(405, "text/plain", "Sadece POST destekleniyor!");
    }
}

void ESPWiFiManager::handleWifiUpdate() {
    if (server.method() == HTTP_POST) {
        server.send(200, "text/plain", "WiFi bilgileri siliniyor.");
        clearCredentials();
    } else {
        server.send(405, "text/plain", "Sadece POST destekleniyor!");
    }
}

// LittleFS işlemleri
bool ESPWiFiManager::saveCredentials(const char* ssid, const char* password) {
    if (!LittleFS.begin()) return false;
    DynamicJsonDocument doc(256);
    doc["ssid"] = ssid;
    doc["password"] = password;

    File file = LittleFS.open("/wifi.json", "w");
    if (!file) return false;
    serializeJson(doc, file);
    file.close();
    return true;
}

bool ESPWiFiManager::loadCredentials(String &ssid, String &password) {
    if (!LittleFS.begin()) return false;
    if (!LittleFS.exists("/wifi.json")) return false;

    File file = LittleFS.open("/wifi.json", "r");
    if (!file) return false;

    DynamicJsonDocument doc(256);
    DeserializationError err = deserializeJson(doc, file);
    file.close();
    if (err) return false;

    ssid = doc["ssid"].as<String>();
    password = doc["password"].as<String>();
    return true;
}

bool ESPWiFiManager::clearCredentials() {
    if (!LittleFS.begin()) return false;
    if (LittleFS.exists("/wifi.json")) {
        return LittleFS.remove("/wifi.json");
    }
    return true;
}
