/*
 * debugLed.c
 *
 *  Created on: May 26, 2015
 *      Author: liwaszkiewicz
 */

#include <stm32f4xx_hal.h>
#include "debugLed.h"
#include "config.h"

#define LED_N 4

static GPIO_TypeDef* GPIO_PORT[LED_N] = { GPIO_LED_D2,
                                          GPIO_LED_D3,
                                          GPIO_LED_D4,
                                          GPIO_LED_D5 };

static const uint16_t GPIO_PIN[LED_N] = { GPIO_PIN_LED_D2,
                                          GPIO_PIN_LED_D3,
                                          GPIO_PIN_LED_D4,
                                          GPIO_PIN_LED_D5 };

void debugLedInit (LedTypeDef led)
{
        GPIO_InitTypeDef GPIO_InitStruct;

        switch (led) {
        case D2:
                __HAL_RCC_LED_D2_CLK_ENABLE ();
                break;
        case D3:
                __HAL_RCC_LED_D3_CLK_ENABLE ();
                break;
        case D4:
                __HAL_RCC_LED_D4_CLK_ENABLE ();
                break;
        case D5:
                __HAL_RCC_LED_D5_CLK_ENABLE ();
                break;
        default:
                break;
        }

        /* Configure the GPIO_LED pin */
        GPIO_InitStruct.Pin = GPIO_PIN[led];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

        HAL_GPIO_Init (GPIO_PORT[led], &GPIO_InitStruct);
        HAL_GPIO_WritePin (GPIO_PORT[led], GPIO_PIN[led], GPIO_PIN_RESET);
}

void debugLedOn (LedTypeDef led)
{
        HAL_GPIO_WritePin (GPIO_PORT[led], GPIO_PIN[led], GPIO_PIN_SET);
}

void debugLedOff (LedTypeDef led)
{
        HAL_GPIO_WritePin (GPIO_PORT[led], GPIO_PIN[led], GPIO_PIN_RESET);
}

void debugLedToggle (LedTypeDef led)
{
        HAL_GPIO_TogglePin (GPIO_PORT[led], GPIO_PIN[led]);
}
