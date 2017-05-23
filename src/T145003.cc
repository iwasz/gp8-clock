/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "T145003.h"
#include <stm32f0xx_hal.h>

T145003 *T145003::singleton ()
{
        static T145003 lcd;
        return &lcd;
}

void T145003::init ()
{
        __HAL_RCC_GPIOA_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init (GPIOA, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}

void T145003::setDigit (uint8_t position, uint8_t digit)
{
        digits[position] = digit;
        needsRefresh = true;
}

void T145003::setDots (uint8_t bitmask)
{
        dots = bitmask;
        needsRefresh = true;
}

void T145003::setIcons (uint8_t bitmask)
{
        icons = bitmask;
        needsRefresh = true;
}

void T145003::setBatteryLevel (uint8_t level)
{
        batteryLevel = level;
        needsRefresh = true;
}

void T145003::refresh ()
{
        if (!needsRefresh) {
                return;
        }

        needsRefresh = false;
        buffer[0] = batteryFont[batteryLevel];

        for (int i = 0; i < 5; ++i) {
                buffer[i + 1] = font[digits[i]];
        }

        if (dots & DOT5) {
                buffer[2] |= 0x08;
        }

        if (dots & DOT4) {
                buffer[3] |= 0x08;
        }

        if (dots & DOT3) {
                buffer[4] |= 0x08;
        }

        if (dots & DOT2) {
                buffer[5] |= 0x08;
        }

        /*---------------------------------------------------------------------------*/

        if (icons & TOP_RIGHT_AROW) {
                buffer[0] |= 0x40;
        }

        if (icons & MINUS_SIGN) {
                buffer[0] |= 0x20;
        }

        if (icons & TOP_LEFT_ARROW) {
                buffer[0] = 0x10;
        }

        if (icons & BOTTOM_LEFT_ARROW) {
                buffer[1] |= 0x08;
        }

        driver->sendData (0, buffer, sizeof (buffer));
}

/*****************************************************************************/

void T145003::setBacklight (bool b)
{
        if (b) {
                GPIOA->BSRR = GPIO_PIN_1;
        }
        else {
                GPIOA->BSRR = GPIO_PIN_1 << 16;
        }
}

/*****************************************************************************/

bool T145003::getBacklight () const { return GPIOA->ODR & GPIO_PIN_1; }
