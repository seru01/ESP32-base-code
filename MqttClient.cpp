#include "MqttClient.h"
#include <Arduino.h>
#include "config.h"


MqttClient::MqttClient(
	const char *server,
	int port,
	const char *user,
	const char *password,
	const char *topic,
	int qos)
	: server(server), port(port), user(user),
	  password(password), topic(topic), qos(qos),
	  client(secureClient)
{
	secureClient.setInsecure(); // Skip certificate verification
	client.setServer(server, port);
	client.setCallback(callback);
}

void MqttClient::callback(char *topic, byte *message, unsigned int length)
{
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("]: ");

	String msg;
	for (unsigned int i = 0; i < length; i++)
	{
		msg += (char)message[i];
	}
	Serial.println(msg);

	// LED control
	if (msg == "on")
	{
		Serial.println("Turning LED ON");
		digitalWrite(LED_PIN, HIGH);
	}
	else if (msg == "off")
	{
		Serial.println("Turning LED OFF");
		digitalWrite(LED_PIN, LOW);
	}
}

void MqttClient::connect()
{
	while (!client.connected())
	{
		Serial.println("Connecting to MQTT...");
		if (client.connect("ESP32Client", user, password))
		{
			Serial.println("Connected to MQTT broker");
			client.subscribe(topic, qos);
		}
		else
		{
			Serial.print("MQTT connection failed, rc=");
			Serial.println(client.state());
			delay(2000);
		}
	}
}

void MqttClient::loop()
{
	client.loop();
}

void MqttClient::publish(const char *message)
{
	if (client.connected())
	{
		client.publish(topic, message, qos);
		Serial.print("Published to topic: ");
		Serial.println(topic);
	}
	else
	{
		Serial.println("Cannot publish, MQTT not connected.");
	}
}
