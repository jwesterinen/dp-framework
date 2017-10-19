/*
 * ping4.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#include <dp_ping4.h>

namespace DP
{
unsigned PING4::GetDistance(unsigned channelId)
{
	switch (channelId)
	{
		case SENSOR_0:
			return distances[0];
			break;
		case SENSOR_1:
			return distances[1];
			break;
		case SENSOR_2:
			return distances[2];
			break;
		case SENSOR_3:
			return distances[3];
			break;

		// should never happen
		default:
			assert(false);
	}
	return 0;
}

void PING4::Handler()
{
    char buffer[80] = {0};
    unsigned distance;
    int id;

    ReadResponse(buffer, sizeof(buffer));
    if (sscanf(buffer, "%d %d", &id, &distance) != 2)
    {
    	throw FrameworkException("DP_Ping4", ERR_RESPONSE);
    }
    distances[id] = distance;
}

} // namespace DP
