/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUZZER_H
#define BUZZER_H

#include "Timer.h"
#include <cstdint>
#include <stm32f0xx_hal.h>

class Buzzer {
public:
        static Buzzer *singleton ()
        {
                static Buzzer b;
                return &b;
        }

        void init ();

        void beep (uint16_t periodOn, uint16_t periodOff, uint8_t times);
        void run ();

private:
        void on () { /*GPIOC->BSRR |= GPIO_PIN_15;*/ }
        void off () { GPIOC->BSRR |= GPIO_PIN_15 << 16; }

private:
        Timer timer;
        uint16_t periodOn = 0;
        uint16_t periodOff = 0;
        uint8_t setTimes = 0;
        uint8_t elapsedTimes = 0;
        bool soundState = true;
};

#endif // BUZZER_H
