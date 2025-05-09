#include <Arduino.h>
#include "WiFiManager.h"
#include "MqttClient.h"
#include "config.h"

// DS3232
#include <Wire.h>
#include <RTClib.h>

#define SDA 21
#define SCL 22

RTC_DS3231 rtc;

class RtcTimeManager
{
private:
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t day;
	uint8_t month;
	uint16_t year;

public:
	void setTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint16_t year)
	{
		rtc.adjust(DateTime(year, month, day, hour, minute, second));
	}

	void getTime()
	{
		DateTime now = rtc.now();
		hour = now.hour();
		minute = now.minute();
		second = now.second();
		day = now.day();
		month = now.month();
		year = now.year();
	}

	void printTime() const
	{
		Serial.print("Time: ");
		Serial.print(hour);
		Serial.print(":");
		if (minute < 10)
			Serial.print("0");
		Serial.print(minute);
		Serial.print(":");
		if (second < 10)
			Serial.print("0");
		Serial.println(second);
	}

	uint8_t getHour() const { return hour; }
	uint8_t getMinute() const { return minute; }
	uint8_t getSecond() const { return second; }
};

class AlarmManager
{
private:
	int alarm1Hour;
	int alarm1Minute;
	bool alarm1Excuted;
	int alarm2Hour;
	int alarm2Minute;
	bool alarm2Excuted;

	RtcTimeManager *timeManager; // Use a pointer or reference to the time manager

public:
	// Constructor to inject dependency
	AlarmManager(RtcTimeManager *manager) : timeManager(manager), alarm1Hour(0), alarm1Minute(0) {}

	void setAlarm1(int hour, int minute)
	{
		alarm1Hour = hour;
		alarm1Minute = minute;
	}
	void setAlarm2(int hour, int minute)
	{
		alarm2Hour = hour;
		alarm2Minute = minute;
	}

	void checkAlarm()
	{
		timeManager->getTime(); // update current time
		if (timeManager->getHour() == alarm1Hour && timeManager->getMinute() == alarm1Minute && !alarm1Excuted)
		{
			Serial.println("Alarm 1 triggered!");
			digitalWrite(LED_PIN, HIGH);
			alarm1Excuted = true;
			alarm2Excuted = false;
		}
		else if (timeManager->getHour() == alarm2Hour && timeManager->getMinute() == alarm2Minute && !alarm2Excuted)
		{
			Serial.println("Alarm 2 triggered!");
			digitalWrite(LED_PIN, LOW);
			alarm1Excuted = false;
			alarm2Excuted = true;
			
		}
	}
};

WiFiManager wifi("seru", "1234567890");
MqttClient mqtt(
	"a22f5d5594744d5c952c2157662a16e1.s1.eu.hivemq.cloud",
	8883,
	"rbtestmqtt",
	"Rbtestmqtt123",
	"switch");

RtcTimeManager rtcManager;
AlarmManager alarmMgr(&rtcManager);
void setup()
{
	Serial.begin(115200);
	pinMode(LED_PIN,OUTPUT);
	if (!rtc.begin())
	{
		Serial.println("Couldn't find RTC");
		while (1)
			;
	}

	if (rtc.lostPower())
	{
		Serial.println("RTC lost power, setting the time!");
		// Set the RTC to the date & time this sketch was compiled
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	wifi.connect();
	mqtt.connect();
	rtcManager.getTime();
	rtcManager.printTime();
	alarmMgr.setAlarm1(11, 50);
	alarmMgr.setAlarm2(11, 51);
}

void loop()
{
	alarmMgr.checkAlarm();
	mqtt.loop();
}
