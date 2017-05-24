/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Adc.h"
#include "AdcChannel.h"
#include "Debug.h"
#include "utils.h"

/*****************************************************************************/

void Adc::init ()
{
        __HAL_RCC_ADC1_CLK_ENABLE ();

        hadc.Instance = ADC1;
        if (HAL_ADC_DeInit (&hadc) != HAL_OK) {
                Error_Handler ();
        }

        hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
        hadc.Init.Resolution = ADC_RESOLUTION_8B;
        hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
        hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
        hadc.Init.LowPowerAutoWait = DISABLE;
        hadc.Init.LowPowerAutoPowerOff = DISABLE;
        hadc.Init.ContinuousConvMode = DISABLE;
        hadc.Init.DiscontinuousConvMode = ENABLE;
        hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
        hadc.Init.DMAContinuousRequests = DISABLE;
        hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;

        if (HAL_ADC_Init (&hadc) != HAL_OK) {
                Error_Handler ();
        }
}

/*****************************************************************************/

void Adc::run ()
{
        // TODO Suboptimal, shold use DMA or interrupts.
        for (int i = 0; i < maxChannelsNo; ++i) {

                if (HAL_ADC_Start (&hadc) != HAL_OK) {
                        Error_Handler ();
                }

                if (HAL_ADC_PollForConversion (&hadc, 10) != HAL_OK) {
                        Error_Handler ();
                }

                channels[i]->lastValue = HAL_ADC_GetValue (&hadc);

#if 1
                Debug *debug = Debug::singleton ();
                debug->print (channels[i]->getValue ());
                debug->print (" ");
#endif
        }

#if 1
        Debug::singleton ()->print ("\n");
#endif
}

/*****************************************************************************/

void Adc::addChannel (AdcChannel *channel)
{
        channels[channelsNum++] = channel;
        channel->init (this);
}
