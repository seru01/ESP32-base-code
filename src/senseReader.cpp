#include <Arduino.h>
#include "SenseReader.h"
#include "config.h"
#include <Wire.h>



// Constructor
SenseReader::SenseReader(const char* sensorType, uint8_t sensorAddress, const char* sensorUnit)
	: sensorType(sensorType), sensorAddress(sensorAddress), sensorUnit(sensorUnit) {}

// Setters
void SenseReader::setSensorType(const char* sensorType) {
	this->sensorType = sensorType;
}

void SenseReader::setSensorAddress(uint8_t sensorAddress) {
	this->sensorAddress = sensorAddress;
}

void SenseReader::setSensorUnit(const char* sensorUnit) {
	this->sensorUnit = sensorUnit;
}

// Getters
const char* SenseReader::getSensorType() const {
	return sensorType;
}

uint8_t SenseReader::getSensorAddress() const {
	return sensorAddress;
}

const char* SenseReader::getSensorUnit() const {
	return sensorUnit;
}

// Default implementation (optional)
void SenseReader::printSensorData() {
	Serial.print("Sensor Type: ");
	Serial.print(sensorType);
	Serial.print(", Address: 0x");
	Serial.print(sensorAddress, HEX);
	Serial.print(", Unit: ");
	Serial.println(sensorUnit);
}
