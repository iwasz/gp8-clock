#include "Adc.h"
#include "AdcChannel.h"
#include "Button.h"
#include "Buzzer.h"
#include "Debug.h"
#include "FastStateMachine.h"
#include "History.h"
#include "I2CLcdDataLink.h"
#include "InfraRedBeam.h"
#include "PCF85176Driver.h"
#include "StopWatch.h"
#include "T145003.h"
#include "Timer.h"
#include "config.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include <cstdbool>
#include <cstring>
#include <stm32f0xx_hal.h>
#include <storage/FlashEepromStorage.h>

namespace __gnu_cxx {
void __verbose_terminate_handler ()
{
        while (1)
                ;
}
}

static void SystemClock_Config (void);

USBD_HandleTypeDef usbdDevice;

/*****************************************************************************/

int main (void)
{
        HAL_Init ();
        SystemClock_Config ();

        /*+-------------------------------------------------------------------------+*/
        /*| Screen                                                                  |*/
        /*+-------------------------------------------------------------------------+*/

        I2CLcdDataLink *link = I2CLcdDataLink::singleton ();
        link->init ();

        PCF85176Driver *lcdd = PCF85176Driver::singleton ();
        lcdd->setDataLink (link);
        lcdd->init (3, 4, true);

        T145003 *screen = T145003::singleton ();
        screen->setLcdDriver (lcdd);
        screen->init ();

        /*+-------------------------------------------------------------------------+*/
        /*| Backlight, beeper                                                       |*/
        /*+-------------------------------------------------------------------------+*/

        Buzzer *buzzer = Buzzer::singleton ();
        buzzer->init ();

#if 1
        Debug *debug = Debug::singleton ();
        debug->init (115200);
        debug->print ("gp8 stopwatch ready\n");
#endif

        /*+-------------------------------------------------------------------------+*/
        /*| StopWatch, machine and IR                                               |*/
        /*+-------------------------------------------------------------------------+*/

        History *history = History::singleton (/*3*/);
        FlashEepromStorage<2048> hiScoreStorage (2, 1, 0x801E800 /*0x08020000 - 3 * 2048*/);
        hiScoreStorage.init ();
        history->setHiScoreStorage (&hiScoreStorage);
        FlashEepromStorage<2048> historyStorage (2, 2, 0x801F000 /*0x08020000 - 2 * 2048*/);
        historyStorage.init ();
        history->setHistoryStorage (&historyStorage);
        history->init ();
        debug->print ("gp8-stopwatch\n");
        history->printHistory ();

        StopWatch *stopWatch = StopWatch::singleton ();
        stopWatch->setDisplay (screen);
        FastStateMachine *fStateMachine = FastStateMachine::singleton ();
        fStateMachine->setStopWatch (stopWatch);
        stopWatch->setStateMachine (fStateMachine);
        InfraRedBeam *beam = InfraRedBeam::singleton ();

        Button *button = Button::singleton ();
        button->init (GPIOB, GPIO_PIN_8);
        fStateMachine->setIr (beam);
        fStateMachine->setDisplay (screen);
        fStateMachine->setBuzzer (buzzer);
        fStateMachine->setHistory (history);
        fStateMachine->setButton (button);

        beam->init ();
        stopWatch->init ();

        /*+-------------------------------------------------------------------------+*/
        /*| Battery, light sensor                                                   |*/
        /*+-------------------------------------------------------------------------+*/

        Adc *adc = Adc::instance (2);
        adc->init ();

        AdcChannel ambientLightVoltMeter (GPIOA, GPIO_PIN_2, ADC_CHANNEL_2);
        adc->addChannel (&ambientLightVoltMeter);

        AdcChannel batteryVoltMeter (GPIOA, GPIO_PIN_3, ADC_CHANNEL_3);
        adc->addChannel (&batteryVoltMeter);
        Timer batteryTimer;

        /*+-------------------------------------------------------------------------+*/
        /*| USB                                                                     |*/
        /*+-------------------------------------------------------------------------+*/

        /* Init Device Library */
        USBD_Init (&usbdDevice, &VCP_Desc, 0);

        /* Add Supported Class */
        USBD_RegisterClass (&usbdDevice, USBD_CDC_CLASS);

        /* Add CDC Interface Class */
        USBD_CDC_RegisterInterface (&usbdDevice, &USBD_CDC_fops);

        /* Start Device Process */
        USBD_Start (&usbdDevice);

        while (1) {
                screen->refresh ();
                buzzer->run ();
                button->run ();

                if (batteryTimer.isExpired ()) {
                        adc->run ();
                        batteryTimer.start (1000);
                        uint8_t batteryVoltage = batteryVoltMeter.getValue ();

                        if (batteryVoltage <= 125) {
                                screen->setBatteryLevel (1);
                        }
                        else if (batteryVoltage <= 130) {
                                screen->setBatteryLevel (2);
                        }
                        else if (batteryVoltage <= 140) {
                                screen->setBatteryLevel (3);
                        }
                        else if (batteryVoltage <= 148) {
                                screen->setBatteryLevel (4);
                        }
                        else {
                                screen->setBatteryLevel (5);
                        }

                        uint8_t ambientLightVoltage = ambientLightVoltMeter.getValue ();

                        if (!screen->getBacklight () && ambientLightVoltage < 50) {
                                screen->setBacklight (true);
                        }
                        else if (screen->getBacklight () && ambientLightVoltage > 80) {
                                screen->setBacklight (false);
                        }
                }
        }
}

/*****************************************************************************/

void SystemClock_Config (void)
{

        RCC_OscInitTypeDef RCC_OscInitStruct;
        RCC_ClkInitTypeDef RCC_ClkInitStruct;
        RCC_PeriphCLKInitTypeDef PeriphClkInit;

        /**Initializes the CPU, AHB and APB busses clocks
        */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
        RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
        if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK) {
                Error_Handler ();
        }

        /**Initializes the CPU, AHB and APB busses clocks
        */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
                Error_Handler ();
        }

        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB | RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C1;
        PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
        PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
        PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;

        if (HAL_RCCEx_PeriphCLKConfig (&PeriphClkInit) != HAL_OK) {
                Error_Handler ();
        }

        /**Configure the Systick interrupt time
        */
        HAL_SYSTICK_Config (HAL_RCC_GetHCLKFreq () / 1000);

        /**Configure the Systick
        */
        HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);

        /* SysTick_IRQn interrupt configuration */
        HAL_NVIC_SetPriority (SysTick_IRQn, 0, 0);
}
