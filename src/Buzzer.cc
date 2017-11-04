///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/

//#include "Buzzer.h"

///*****************************************************************************/

//void Buzzer::init ()
//{
//        __HAL_RCC_GPIOC_CLK_ENABLE ();
//        GPIO_InitTypeDef gpioInitStruct;
//        //        RCC->BDCR &= ~RCC_BDCR_LSEON;
//        gpioInitStruct.Pin = GPIO_PIN_15;
//        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//        gpioInitStruct.Pull = GPIO_NOPULL;
//        HAL_GPIO_Init (GPIOC, &gpioInitStruct);
//        HAL_GPIO_WritePin (GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
//}

///*****************************************************************************/

//void Buzzer::beep (uint16_t periodOn, uint16_t periodOff, uint8_t times)
//{
//        this->periodOn = periodOn;
//        this->periodOff = periodOff;
//        this->setTimes = times;
//        this->elapsedTimes = 0;
//        this->soundState = true;
//        timer.start (periodOn);
//        on ();
//}

///*****************************************************************************/

//void Buzzer::run ()
//{
//        if (elapsedTimes >= setTimes) {
//                return;
//        }

//        if (!timer.isExpired ()) {
//                return;
//        }

//        if (soundState) {
//                off ();
//                soundState = false;
//                timer.start (periodOff);
//                ++elapsedTimes;
//        }
//        else {
//                on ();
//                soundState = true;
//                timer.start (periodOn);
//        }
//}
