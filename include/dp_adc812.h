/*
 * adc812.h
 *
 *  Created on: Oct 18, 2017
 *      Author: jeff
 */

#ifndef ADC812_H_
#define ADC812_H_

#include "dp_peripherals.h"

namespace DP
{

class ADC812 : public Sensor
{
private:
	unsigned samples[8];

protected:
	unsigned GetSample_mV(unsigned inputId)
	{
		return samples[inputId];
	}
	void Handler();

public:
	enum CHANNELS {CHANNEL_1 = 0, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5, CHANNEL_6, CHANNEL_7, CHANNEL_8};
	// OR these together to form an enable pair pattern
	enum DIFF_PAIRS {NO_PAIRS = 0, PAIR_1 = 1, PAIR_2 = 2, PAIR_3 = 4, PAIR_4 = 8};

	ADC812(EventContext& framework, const char* id) : Sensor(framework, id, "samples")
	{
		for (int i = 0; i < 8; ++i)
			samples[i] = 0;
	}
	virtual ~ADC812()
	{}
	void Config(unsigned period, DIFF_PAIRS differentialPairs);
};

} // namespace DP

#endif /* ADC812_H_ */
