/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LIB_MICRO_BUTTON_H
#define LIB_MICRO_BUTTON_H

#include "Hal.h"
#include "Timer.h"
#include <cstdint>

//extern "C" void EXTI4_15_IRQHandler ();

/**
 * This whole implementation will work only for 1 button.
 */
class Button {
public:
//        void init (GPIO_TypeDef *g, uint16_t p);

        // TODO ofcourse this can't be singleton.
        static Button *singleton ()
        {
                static Button b;
                return &b;
        }

        bool getPressClear () const;
        bool getLongPressClear () const;
        void run ();

private:
//        friend void EXTI4_15_IRQHandler ();
        void onExti ();

private:
//        GPIO_TypeDef *gpio = nullptr;
        uint16_t pin;
        mutable bool pressedEvent = false;
        mutable bool longPressedEvent = false;
        mutable bool pressed = false;

        Timer longPressTimer;
        Timer debounceTimer;
};

#endif // BUTTON_H
