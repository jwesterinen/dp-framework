/*
 * peripherals.h
 *
 */

#ifndef DP_PERIPHERALS_H_
#define DP_PERIPHERALS_H_

#include <cstdio>
#include <sstream>
#include <cassert>

#include "dp_events.h"

namespace DP
{

// local implementation of the std::to_string function
template <typename T>
const std::string ToString(T val)
{
	std::stringstream stream;
	stream << val;
	return stream.str();
}

/**
 * \brief Base class for a DP peripheral
 */
class Peripheral
{
protected:
	int cmdfd;
	std::string id;

	void WriteConfig(std::string resource, const std::string& arg);
	void WriteCommand(std::string command, std::string arg = "");

public:
	/**
	 * @param evtCtx The application's event context object
	 * @param _id The id string of the peripheral
	 */
	Peripheral(EventContext& evtCtx, const char* _id) : cmdfd(evtCtx.cmdfd), id(_id)
	{}
	virtual ~Peripheral()
	{}
};

/**
 * \brief Base class for a DP sensor peripheral
 *
 * A DP sensor is a peripheral that is a selectable sensor.
 */
class Sensor : public Peripheral, public SelectableSensor
{
protected:
	std::string dataRsc;

	void ReadResponse(char* buffer, int bufSize);
	void StartDataStream();
	virtual void Handler() = 0;

public:
	/**
	 * @param framework The event context object of the application
	 * @param id ID string of the DP peripheral
	 * @param _dataRsc ID of the data resource to be read from the sensor
	 */
	Sensor(EventContext& evtCtx, const char* id, const char* _dataRsc) : Peripheral(evtCtx, id), dataRsc(_dataRsc)
	{}
	virtual ~Sensor()
	{}
};

/**
 * \brief Base class for a DP actuator peripheral
 *
 * A DP actuator is a peripheral that is used to cause actions.
 */
class Actuator : public Peripheral
{
public:
	/**
	 * @param framework The event context object of the application
	 * @param id ID string of the DP peripheral
	 */
	Actuator(EventContext& evtCtx, const char* id) : Peripheral(evtCtx, id)
	{}
	virtual ~Actuator()
	{}
};

} // namespace DP

#endif /* DP_PERIPHERALS_H_ */
