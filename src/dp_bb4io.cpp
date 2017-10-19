/*
 * bb4io.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#include "../include/dp_bb4io.h"

namespace DP
{
void BB4IO::SetLeds(unsigned char pattern)
{
	char buffer[80] = {0};
    sprintf(buffer, "%x", pattern);
	WriteConfig("leds", buffer);
}

void BB4IO::Handler()
{
	char buffer[80] = {0};
    int paramQty = 0;

    ReadResponse(buffer, sizeof(buffer));
    paramQty = sscanf(buffer, "%u", &buttons);
    if (paramQty != 0 && paramQty != 1)
    {
    	throw FrameworkException("DP_BB4IO", ERR_RESPONSE);
    }
}

} // namespace DP
