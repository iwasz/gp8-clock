#include "Timer.h"
#include <stm32f0xx_hal.h>

Timer::Timer () : startTime (0), interval (0) {}

/*****************************************************************************/

void Timer::start (uint32_t interval)
{
        startTime = HAL_GetTick ();
        this->interval = interval;
}

/*****************************************************************************/

bool Timer::isExpired () const { return HAL_GetTick () - startTime > interval; }
