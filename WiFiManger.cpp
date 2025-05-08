#include "WiFiManager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char *s, const char *p)
    : ssid(s), password(p) {}

void WiFiManager::connect()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void WiFiManager::disconnect()
{
    WiFi.disconnect();
    Serial.println("Disconnected from WiFi");
}