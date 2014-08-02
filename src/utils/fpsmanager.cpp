/*
 * FPSManager.cpp
 *
 *  Created on: Jun 12, 2012
 *      Author: zeheron
 */

#include "fpsmanager.hpp"
#include <iostream>

/*
 * Initializes a FPSManger with a starting delta of 22ms
 *
 */
FPSManager::FPSManager()
{
    delta                        = 22;
    avarageCalculationFrameCount = 10;
    frameTimeCiBuffer.set_capacity(avarageCalculationFrameCount);
    for (int i = 0; i < avarageCalculationFrameCount; i++)
    {
        frameTimeCiBuffer.push_back(delta);
    }
}

/*
 * Initializes a FPSManager with the default averageFrameTimeStartValue
 *specified ( milliseconds )
 */
FPSManager::FPSManager(int startDelta)
{
    frameTimeCiBuffer.set_capacity(avarageCalculationFrameCount);
    delta = startDelta;
    for (int i = 0; i < avarageCalculationFrameCount; i++)
    {
        frameTimeCiBuffer.push_back(delta);
    }
}

FPSManager::~FPSManager()
{
    // TODO Auto-generated destructor stub
}

void FPSManager::markStartPoint()
{
    start = boost::chrono::high_resolution_clock::now();
}

boost::chrono::milliseconds FPSManager::calculateframeTime()
{
    return boost::chrono::duration_cast<boost::chrono::milliseconds>(
        end - start);
}

void FPSManager::markEndPoint()
{
    end = boost::chrono::high_resolution_clock::now();
    frameTimeCiBuffer.push_back(calculateframeTime().count());

    unsigned short int avarage = 0;
    for (int i = 0; i < avarageCalculationFrameCount; i++)
    {
        avarage += frameTimeCiBuffer[i];
    }
    delta = avarage / avarageCalculationFrameCount;
}

/*
 * This methods need to be called instead of markEndPoint() to be effective.
 * The frame rate will be governed to be the specified fps value.
 */
void FPSManager::markFixedRateEndPoint()
{
    end   = boost::chrono::high_resolution_clock::now();
    delta = calculateframeTime().count();
    if (fixedFrameRate > delta)
    {
        boost::this_thread::sleep(boost::posix_time::millisec(fixedFrameRate -
                                                              delta));
    }
}

/*
 * Sets the governed frame rate and take the fps as milliseconds per frame.
 *
 */
void FPSManager::setFixedFrameRate(unsigned short int fixedFrameRate)
{
    this->fixedFrameRate = fixedFrameRate;
}
