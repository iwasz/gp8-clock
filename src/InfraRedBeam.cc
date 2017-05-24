/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "InfraRedBeam.h"
#include "Debug.h"
#include "utils.h"

/*****************************************************************************/

void InfraRedBeam::init ()
{

        /*+-------------------------------------------------------------------------+*/
        /*| IR detection timer 10kHz                                                |*/
        /*+-------------------------------------------------------------------------+*/
        timHandle.Instance = TIM3;

        // 10kHz
        timHandle.Init.Period = (uint32_t) ((HAL_RCC_GetHCLKFreq () / 2) / 10000) - 1; // 8399
        timHandle.Init.Prescaler = 0;

        // timHandle.Init.Prescaler = (uint32_t)((HAL_RCC_GetHCLKFreq () / 2) / 840000) - 1; // 1 tick = 84MHz/100 = 840kHz
        // timHandle.Init.Period = 8400 - 1;                                                 // Update event every 10ms = 100Hz
        timHandle.Init.ClockDivision = 0;
        timHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

        __HAL_RCC_TIM3_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIM3_IRQn, 3, 0);
        HAL_NVIC_EnableIRQ (TIM3_IRQn);

        if (HAL_TIM_Base_Init (&timHandle) != HAL_OK) {
                Error_Handler ();
        }

        if (HAL_TIM_Base_Start_IT (&timHandle) != HAL_OK) {
                Error_Handler ();
        }

        // Konfigureacja kanału. Input Capture. Wejście.
        __HAL_RCC_GPIOB_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_AF_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Alternate = GPIO_AF1_TIM3;
        gpioInitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init (GPIOB, &gpioInitStruct);

        // Dotycząca timera
        TIM_IC_InitTypeDef sICConfig;
        sICConfig.ICPolarity = TIM_ICPOLARITY_RISING;
        sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
        sICConfig.ICFilter = 0;
        sICConfig.ICPrescaler = TIM_ICPSC_DIV1;

        if (HAL_TIM_IC_ConfigChannel (&timHandle, &sICConfig, TIM_CHANNEL_4) != HAL_OK) {
                Error_Handler ();
        }

        if (HAL_TIM_IC_Start_IT (&timHandle, TIM_CHANNEL_4) != HAL_OK) {
                Error_Handler ();
        }
}

/*****************************************************************************/

extern "C" void TIM3_IRQHandler () { InfraRedBeam::singleton ()->onInterrupt (); }

/*****************************************************************************/

void InfraRedBeam::onInterrupt ()
{
        static uint32_t time = 0;
        static uint32_t timeOfLastRise = 0;
        static uint32_t noOfSuccesiveRises = 0;

        /*
         * I.C. ~1kHz
         * Uwaga! Makro __HAL_TIM_GET_IT_SOURCE ma mylną nazwę, bo ono sprawdza rejestr DIER, czyli
         * sprawdza, czy dane przerwanie jest WŁĄCZONE czy nie. Jeśli by nie było włączone, to byśmy
         * nigdy się nie znaleźli w ISR z powodu tego konkretnego przerwania.
         */
        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_CC4) /*&& __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_IT_CC1)*/) {
                __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_CC4);

                timeOfLastRise = time;

                if (time - timeOfLastRise <= 12) {
                        if (++noOfSuccesiveRises >= 10) {
                                beamPresent = true;
                        }
                }

                return;
        }

        // 10kHz
        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_UPDATE) && __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_IT_UPDATE)) {
                __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_UPDATE);

                // Will re-wind to 0 after ~120hours
                ++time;

                // Znikło na 100ms
                if (time - timeOfLastRise > 1000) {
                        beamPresent = false;
                        noOfSuccesiveRises = 0;
                }

                // Znikło na 7ms
                if (time - timeOfLastRise > 70) {
                        beamInterrupted = true;
                }

        }
}
