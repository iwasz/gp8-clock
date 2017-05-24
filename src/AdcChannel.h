/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ADCCHANNEL_H
#define ADCCHANNEL_H

#include <stm32f0xx_hal.h>

class Adc;

/**
 * @brief The AdcChannel class
 */
class AdcChannel {
public:
        AdcChannel (GPIO_TypeDef *gpioInstance, uint32_t gpioPin, uint32_t num) : number (num), lastValue (0), gpioPin (gpioPin), gpioInstance (gpioInstance) {}
        uint32_t getValue () const { return lastValue; }
        void init (Adc *adc);

private:
        friend class Adc;
        uint32_t number;
        uint32_t lastValue;
        uint32_t gpioPin;
        GPIO_TypeDef *gpioInstance;
};

#endif // ADCCHANNEL_H
