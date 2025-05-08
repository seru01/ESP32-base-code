#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

class MqttClient
{
private:
	const char *server;
	const int port;
	const char *user;
	const char *password;
	const char *topic;
	const int qos;

	WiFiClientSecure secureClient;
	PubSubClient client;

	static void callback(char *topic, byte *message, unsigned int length);

public:
	MqttClient(
		const char *server,
		int port,
		const char *user,
		const char *password,
		const char *topic,
		int qos = 1);

	void connect();
	void loop();
	void publish(const char *message);
};

#endif
