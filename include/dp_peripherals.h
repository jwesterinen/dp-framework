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

// DP peripheral base class
class Peripheral
{
protected:
	int cmdfd;
	std::string id;

	void WriteConfig(std::string resource, const std::string& arg);
	void WriteCommand(std::string command, std::string arg = "");

public:
	Peripheral(EventContext& framework, const char* _id) : cmdfd(framework.cmdfd), id(_id)
	{}
	virtual ~Peripheral()
	{}
};

// DP sensor base class
class Sensor : public Peripheral, public SelectableSensor
{
protected:
	std::string dataRsc;

	void ReadResponse(char* buffer, int bufSize);
	void StartDataStream();
	virtual void Handler() = 0;

public:
	Sensor(EventContext& framework, const char* id, const char* _dataRsc) : Peripheral(framework, id), dataRsc(_dataRsc)
	{}
	virtual ~Sensor()
	{}
};

// DP actuator base class interface
class Actuator : public Peripheral
{
public:
	Actuator(EventContext& framework, const char* id) : Peripheral(framework, id)
	{}
	virtual ~Actuator()
	{}
};

} // namespace DP

#endif /* DP_PERIPHERALS_H_ */
