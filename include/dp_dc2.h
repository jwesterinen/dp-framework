/*
 * dc2.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#ifndef INCLUDE_DP_DC2_H_
#define INCLUDE_DP_DC2_H_

#include "dp_peripherals.h"

namespace DP
{
// TODO: implement missing configurators
/**
 * \brief DC2 DP peripheral
 */
class DC2 : public Actuator
{
public:
	enum MODE {BREAK = 'b', FORWARD = 'f', REVERSE = 'r', COAST = 'c'};

	DC2(EventContext& framework, const char* id) : Actuator(framework, id)
	{}
	virtual ~DC2()
	{}
	void SetMode0(char mode);
	void SetMode1(char mode);
	void SetPower0(float power);
	void SetPower1(float power);
	void SetPWMfrequency(unsigned freqInHz);
	/*
	slow_start0, slow_start1 : Acceleration curve
	The acceleration curve is a list of ten space separated integers
	representing the time (in milliseconds) between each 10 percent
	increase from 0 to 100 percent ON time.  The following string
	shows how to specify a slow start that takes half a second to
	get to 50 percent power and three-quarters of a second to get
	from zero to full power:
		dpset dc2 slow_start0 100 100 100 100 100 50 50 50 50 50
	The default value for slow_start is off to full power in zero
	milliseconds.  That is, the default is to turn off slow start.
	*/
	void SetSlow_start0();
	void SetSlow_start1();
	/*
	slow_stop0, slow_stop1 : Deceleration curve.
	The deceleration curve is a list of ten space separated integers
	representing the time (in milliseconds) between each 10 percent
	decrease from 100 to 0 percent ON time.  The following string
	shows a slow stop that takes half a second to get to 50% power
	and three-quarters of a second to get from full power to zero:
	    dpset cd2 slow_stop0 100 100 100 100 100 50 50 50 50 50
	The default value for slow_stop is full on to full off in zero
	milliseconds.  That is, the default is to turn off slow stop.
	*/
	void SetSlow_stop0();
	void SetSlow_stop1();
	void SetWatchdog(unsigned timeout);
};

} // namespace DP

#endif /* INCLUDE_DP_DC2_H_ */
