#ifndef SENSE_READER_H
#define SENSE_READER_H

#include <Arduino.h>

class SenseReader
{
protected:
	const char *sensorType;
	uint8_t sensorAddress;
	const char *sensorUnit;

public:
	SenseReader(const char *sensorType, uint8_t sensorAddress, const char *sensorUnit);

	virtual void readSensorData() = 0; // pure virtual - must be implemented by derived class
	virtual void printSensorData();	   // optionally override

	void setSensorType(const char *sensorType);
	void setSensorAddress(uint8_t sensorAddress);
	void setSensorUnit(const char *sensorUnit);

	const char *getSensorType() const;
	uint8_t getSensorAddress() const;
	const char *getSensorUnit() const;

	virtual ~SenseReader() = default;
};

#endif
