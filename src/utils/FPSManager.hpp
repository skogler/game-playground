/*
 * FPSManager.h
 *
 *  Created on: Jun 12, 2012
 *      Author: zeheron
 */

#ifndef FPSMANAGER_HPP_
#define FPSMANAGER_HPP_

#include <boost/chrono.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>



class FPSManager {

private:
	unsigned short int avarageCalculationFrameCount;
	unsigned short int delta;
	unsigned short int fixedFrameRate;
	boost::circular_buffer<unsigned short int> frameTimeCiBuffer;
	boost::chrono::high_resolution_clock::time_point start;
	boost::chrono::high_resolution_clock::time_point end;

	boost::chrono::milliseconds calculateframeTime();


public:
	FPSManager();
	FPSManager(int startDelta);
	virtual ~FPSManager();

	void markStartPoint();
	void markEndPoint();
	void markFixedRateEndPoint();
	void setFixedFrameRate(unsigned short int fixedFrameRate);

	unsigned short int getFixedFrameRate() const
	{
		return fixedFrameRate;
	}

	unsigned short int getAvarageCalculationFrameCount() const
	{
		return avarageCalculationFrameCount;
	}

	void setAvarageCalculationFrameCount(unsigned short int avarageCalculationFrameCount)
	{
		this->avarageCalculationFrameCount = avarageCalculationFrameCount;
	}

	unsigned short int getDelta() const
	{
		return delta;
	}
};

#endif /* FPSMANAGER_HPP_ */
