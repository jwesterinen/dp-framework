/*
 * count4.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#include "../include/dp_count4.h"

namespace DP
{
void COUNT4::SetUpdateRate(unsigned rate)
{
	// the update period must be between 10 and 60 milliseconds in steps of 10 milliseconds
	if (rate != 10 && rate != 20 && rate != 30 && rate != 40 && rate != 50 && rate != 60)
	{
		throw FrameworkException("DP_Count4", ERR_PARAMS);
	}
	WriteConfig("update_rate", ToString(rate));
}
void COUNT4::SetEdges(unsigned setting1, unsigned setting2, unsigned setting3, unsigned setting4)
{
	std::string argStr;
	argStr = ToString(setting1) + " " + ToString(setting2) + " " + ToString(setting3) + " " + ToString(setting4);
    WriteConfig("edges", argStr);
}
void COUNT4::Handler()
{
    char buffer[80] = {0};

    // read the tick counts
    ReadResponse(buffer, sizeof(buffer));
    if (sscanf(buffer, "%d %f %d %f %d %f %d %f",
        &counts[0], &intervals[0],
        &counts[1], &intervals[1],
        &counts[2], &intervals[2],
        &counts[3], &intervals[3]
    ) != 8)
    {
    	throw FrameworkException("DP_Count4", ERR_RESPONSE);
    }
}

} // namespace DP
