/*
 * ping4.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#ifndef INCLUDE_DP_PING4_H_
#define INCLUDE_DP_PING4_H_

#include "dp_peripherals.h"

namespace DP
{
class PING4 : public Sensor
{
public:
private:
	unsigned distances[4];

protected:
	unsigned GetDistance(unsigned channelId);
	void Handler();

public:
	// TODO: fill in the actual ranges for a Ping device
	const static unsigned MinRange = 0;
	const static unsigned MaxRange = 5000;
	// OR these together to form an enable sensor pattern
	enum SENSORS {SENSOR_0 = 1, SENSOR_1 = 2, SENSOR_2 = 4, SENSOR_3 = 8};

	PING4(EventContext& framework, const char* id) : Sensor(framework, id, "distance")
	{
		distances[0] = distances[1] = distances[2] = distances[3] = 0;
	}
	virtual ~PING4()
	{}
	void Enable(unsigned sensorPattern)
	{
	    return WriteConfig("enable", ToString(sensorPattern));
	}
};

} // namespace DP

#endif /* INCLUDE_DP_PING4_H_ */
