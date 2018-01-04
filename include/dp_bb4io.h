/*
 * bb4io.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#ifndef INCLUDE_DP_BB4IO_H_
#define INCLUDE_DP_BB4IO_H_

#include "dp_peripherals.h"

namespace DP
{
/**
 * \brief BB4IO DP peripheral
 */
class BB4IO : public Sensor
{
private:
	unsigned buttons;

protected:
	void SetLeds(unsigned char pattern);
	void Handler();

public:
	// OR these together to combine buttons
	enum SWITCHES {S1 = 1, S2 = 2, S3 = 4};

	BB4IO(EventContext& framework) : Sensor(framework, "bb4io", "buttons"), buttons(0)
	{}
	virtual ~BB4IO()
	{}
	bool IsButtonPressed(int buttonId)
	{
		return (buttons & buttonId);
	}
};

} // namespace DP

#endif /* INCLUDE_DP_BB4IO_H_ */
