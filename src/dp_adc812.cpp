/*
 * adc812.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#include <dp_adc812.h>

namespace DP
{
void ADC812::Config(unsigned period, DIFF_PAIRS differentialPairs)
{
	char buffer[80] = {0};
	sprintf(buffer, "%u, 0x%02x", period, differentialPairs);
    WriteConfig("config", buffer);
}

void ADC812::Handler()
{
    char buffer[80] = {0};

    // read the tick counts
    ReadResponse(buffer, sizeof(buffer));
    if (sscanf(buffer, "%x %x %x %x %x %x %x %x",
        &samples[0], &samples[1],&samples[2], &samples[3],
		&samples[4], &samples[5], &samples[6], &samples[7]
    ) != 8)
    {
    	throw FrameworkException("DP_Adc812", ERR_RESPONSE);
    }
}

} // namespace DP

