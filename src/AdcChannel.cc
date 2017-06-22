/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AdcChannel.h"
#include "Adc.h"
#include "ErrorHandler.h"

void AdcChannel::init (Adc *adc)
{
        __HAL_RCC_GPIOA_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = gpioPin;
        gpioInitStruct.Mode = GPIO_MODE_ANALOG;
        gpioInitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init (gpioInstance, &gpioInitStruct);

        ADC_ChannelConfTypeDef sConfig;
        sConfig.Channel = number;
        sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
        sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

        if (HAL_ADC_ConfigChannel (&adc->hadc, &sConfig) != HAL_OK) {
                Error_Handler ();
        }
}
