/*
 * dc2.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#include <dp_dc2.h>

namespace DP
{
void DC2::SetMode0(char mode)
{
	return WriteConfig("mode0", ToString(mode));
}

void DC2::SetMode1(char mode)
{
	return WriteConfig("mode1", ToString(mode));
}

void DC2::SetPower0(float power)
{
	return WriteConfig("power0", ToString(power));
}

void DC2::SetPower1(float power)
{
	return WriteConfig("power1", ToString(power));
}

void DC2::SetPWMfrequency(unsigned freqInHz)
{
	return WriteConfig("pwm_frequency", ToString(freqInHz));
}

void DC2::SetSlow_start0()
{
	return;
}

void DC2::SetSlow_start1()
{
	return;
}

void DC2::SetSlow_stop0()
{
	return;
}

void DC2::SetSlow_stop1()
{
	return;
}

void DC2::SetWatchdog(unsigned timeout)
{
	return WriteConfig("watchdog", ToString(timeout));
}

} // namespace DP
