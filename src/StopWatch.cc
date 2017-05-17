/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "StopWatch.h"
#include "FastStateMachine.h"
#include "IDisplay.h"
#include "utils.h"

StopWatch::StopWatch () : running (false), time (0) {}

/*****************************************************************************/

void StopWatch::init ()
{
        /*+-------------------------------------------------------------------------+*/
        /*| Stopwatch timer 100Hz                                                   |*/
        /*+-------------------------------------------------------------------------+*/

        stopWatchTimHandle.Instance = TIM14;
        stopWatchTimHandle.Init.Period = 100; // 100Hz
        stopWatchTimHandle.Init.Prescaler = (uint32_t) (HAL_RCC_GetHCLKFreq () / 10000) - 1;
        stopWatchTimHandle.Init.ClockDivision = 0;
        stopWatchTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
        stopWatchTimHandle.Init.RepetitionCounter = 0;

        // Uwaga! Zapisać to!!! Msp init jest wywoływane PRZED TIM_Base_SetConfig
        __HAL_RCC_TIM14_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIM14_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ (TIM14_IRQn);

        if (HAL_TIM_Base_Init (&stopWatchTimHandle) != HAL_OK) {
                Error_Handler ();
        }

        if (HAL_TIM_Base_Start_IT (&stopWatchTimHandle) != HAL_OK) {
                Error_Handler ();
        }
}

/**
 * Stop-watch ISR.
 * Here the value displayed is updated. 100Hz
 */
extern "C" void TIM14_IRQHandler ()
{
        __HAL_TIM_CLEAR_IT (&StopWatch::singleton ()->stopWatchTimHandle, TIM_IT_UPDATE);
        StopWatch::singleton ()->onInterrupt ();
}

void StopWatch::onInterrupt ()
{
        stateMachine->run ();

        if (!running) {
                return;
        }

        uint16_t cntTmp = time;

        // 2nd digit of 1/100-s of second (0-99)
        display->setDigit (4, cntTmp % 10);
        cntTmp /= 10;
        // First digit of 1/100-s of second (0-99)
        display->setDigit (3, cntTmp % 10);
        cntTmp /= 10;

        // Second digit of second (0-99)
        display->setDigit (2, cntTmp % 10);
        cntTmp /= 10;
        // First digit of second (0-99)
        display->setDigit (1, cntTmp % 6);
        cntTmp /= 6;

        // One digit of miniutes
        display->setDigit (0, cntTmp % 10);

        //        switch (state) {
        //        case WATCH_INIT:
        //                break;
        //        }

        //        if (state == WATCH_RUNNING) {

        if (++time >= MAX_TIME) {
                time = 0;
        }

        //}

        //        ++timeFromLastEvent;

        //        if (timeFromLastEvent > EVENT_TRESHOLD && noOfUpdateEventsSinceLastRise >= UPDATE_EVENT_TRESHOLD) {
        //                timeFromLastEvent = 0;
        //                beep = true;

        //                if (state == WATCH_RUNNING) {
        //                        state = WATCH_STOPPED;
        //                }
        //                else if (state == WATCH_STOPPED) {
        //                        cnt = 0;
        //                        state = WATCH_RUNNING;
        //                }
        //        }
}
