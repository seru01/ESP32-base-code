#ifndef WIFI_MANGER_H
#define WIFI_MANGER_H

#include <WiFi.h>

class WiFiManager
{
private:
	const char *ssid;
	const char *password;

public:
	WiFiManager(const char *ssid, const char *password);
	void connect();
	void disconnect();
};

#endif
