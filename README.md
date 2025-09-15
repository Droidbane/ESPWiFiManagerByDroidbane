# 🚀 ESPWiFiManagerByDroidbane

A one-stop solution for next-generation **ESP8266 Wi-Fi management**. **Remotely update  **SSID and password** fom your phone or any web client, **soft reboot** the device, and manage the entire process in minutes.

---

## ✨ Features
- 🌐 **Server-Side Remote Management**  
  Embedded HTTP server on ESP8266.
- 🔑 **Dynamic Wi-Fi Information**  
  Save and update SSID and password instantly.
- ♻️ **Soft-Reboot**  
  Remotely `reboot` the device with the Soft-Reboot endpoint.
- ⚡ **Easy Integration Starts working with** `#include` 
  It starts working with a single `#include` and a few lines of code.
- 🧩 **Library + Samples**
  It is installed from the Arduino Library Manager and comes with **BasicUsage** in the Examples menu.

---

## 📡 API Endpoints
| Endpoints        | Methods | Descriptions|
|-----------------|-------|----------------------------------------|
| `/wifi`         | POST  | Wi-Fi settings with `ssid` and `password` key-values. ESP won't forget them even if it's turned off! |
| `/wifi-update`  | POST  | Updating existing network with new information |
| `/restart`      | POST   | Remotely rebooting ESP8266   |

---

## 🛠️ Quick Start
```cpp
#include <ESPWiFiManager.h>

ESPWiFiManagerByDroidbane wifiManagerByDroidbane("ESP_Setup");

void setup() {
    wifiManager.begin();
}

void loop() {
    wifiManager.loop();
}
```

A working demo is available in the Arduino IDE under **File → Examples → ESPWiFiManagerByDroidbane → BasicUsage**.

---

## ⚙️ Setup
1. **Library Manager**  
   Arduino IDE → Tools → Manage Libraries → “ESPWiFiManagerByDroidbane” search → Install.
2. or **Manuel**  
   ```bash
   git clone https://github.com/Droidbane/ESPWiFiManagerByDroidbane.git
   ```
   Move the folder to the Arduino `libraries` directory.

---


## 🧑‍💻 Support
Pull requests and issues are welcome.
Please comply with the terms of the **MIT License**.

---

**ESPWiFiManagerByDroidbane**
Open the door to next-generation Wi-Fi management.
Take full control with just a few lines of code! 🚀
