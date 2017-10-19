/*
 * count4.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#ifndef INCLUDE_DP_COUNT4_H_
#define INCLUDE_DP_COUNT4_H_

#include "dp_peripherals.h"

namespace DP
{
class COUNT4 : public Sensor
{
private:
    unsigned counts[4];
    float intervals[4];

protected:
    unsigned GetCount(unsigned channelId)
    {
    	return counts[channelId];
    }
    float GetInterval(unsigned channelId)
    {
    	return intervals[channelId];
    }
	void Handler();

public:
    enum EDGE_CONFIG {DISABLE_EDGE = 0, LEADING_EDGE = 1, TRAILING_EDGE = 2, BOTH_EDGES = 3};

    COUNT4(EventContext& framework, const char* id) : Sensor(framework, id, "counts")
    {
    	for (int i = 0; i < 4; ++i)
    	{
    		counts[i] = 0;
    		intervals[i] = 0.0;
    	}
    }
	virtual ~COUNT4()
	{}
	void SetUpdateRate(unsigned rate);
	void SetEdges(unsigned setting1, unsigned setting2, unsigned setting3, unsigned setting4);
};

} // namespace DP

#endif /* INCLUDE_DP_COUNT4_H_ */
