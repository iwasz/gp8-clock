/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Button.h"

void Button::init (GPIO_TypeDef *g, uint16_t p)
{
        gpio = g;
        pin = p;

        // TODO not B. TODO class GPIO which would know which macro to use.
        __HAL_RCC_GPIOB_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = pin;
        gpioInitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
        gpioInitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init (gpio, &gpioInitStruct);

        HAL_NVIC_SetPriority (EXTI4_15_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ (EXTI4_15_IRQn);
}

/*****************************************************************************/

extern "C" void EXTI4_15_IRQHandler ()
{
        Button *b1 = Button::singleton ();

        if (__HAL_GPIO_EXTI_GET_IT (b1->pin) != RESET) {
                __HAL_GPIO_EXTI_CLEAR_IT (b1->pin);

                // TODO wykryć który pin spowodował.
                b1->onExti ();
        }
}

/*****************************************************************************/

void Button::onExti ()
{
        if (!debounceTimer.isExpired ()) {
                return;
        }
        debounceTimer.start (50);

        // Button pressed (button gpio is normally pulled up)
        if (!(gpio->IDR & pin)) {
                longPressTimer.start (1000);
                pressed = true;
        }
        else {
                if (!pressed) {
                        return;
                }

                pressed = false;

                //                if (!longPressTimer.isExpired()) {
                pressedEvent = true;
                //                }
        }
}

/*****************************************************************************/

bool Button::getPressClear () const
{
        if (pressedEvent) {
                pressedEvent = false;
                return true;
        }

        return false;
}

/*****************************************************************************/

bool Button::getLongPressClear () const
{
        if (longPressedEvent) {
                longPressedEvent = false;
                return true;
        }

        return false;
}

/*****************************************************************************/

void Button::run ()
{
        if (pressed && longPressTimer.isExpired ()) {
                longPressedEvent = true;
                pressed = false;
        }
}
