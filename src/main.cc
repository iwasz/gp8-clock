#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
#include "Buzzer.h"
#include "Debug.h"
#include "FastStateMachine.h"
#include "I2CLcdDataLink.h"
#include "InfraRedBeam.h"
#include "PCF85176Driver.h"
#include "StopWatch.h"
#include "T145003.h"
#include "Timer.h"
#include "config.h"
#include <cstdbool>
#include <cstring>

static void SystemClock_Config (void);
// USBD_HandleTypeDef USBD_Device;

/*****************************************************************************/

class VoltMeter {
public:
        static VoltMeter *instance () { return new VoltMeter; }
        void init (uint32_t channel, GPIO_TypeDef *gpio, uint32_t pin);
        uint32_t getVoltage () const;

private:
        static ADC_HandleTypeDef hadc;
        static bool adcInited;
};

bool VoltMeter::adcInited = false;
ADC_HandleTypeDef VoltMeter::hadc;

/*****************************************************************************/

void VoltMeter::init (uint32_t channel, GPIO_TypeDef *gpio, uint32_t pin)

{
        __HAL_RCC_GPIOA_CLK_ENABLE ();
        __HAL_RCC_ADC1_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = pin;
        gpioInitStruct.Mode = GPIO_MODE_ANALOG;
        gpioInitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init (gpio, &gpioInitStruct);

        if (!adcInited) {
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

                adcInited = true;
        }

        /*##-2- Configure ADC regular channel ######################################*/

        ADC_ChannelConfTypeDef sConfig;
        sConfig.Channel = channel;
        sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
        sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

        if (HAL_ADC_ConfigChannel (&hadc, &sConfig) != HAL_OK) {
                Error_Handler ();
        }
}

/*****************************************************************************/

uint32_t VoltMeter::getVoltage () const
{
//        static bool started = false;

//        if (!started) {
                if (HAL_ADC_Start (&hadc) != HAL_OK) {
                        Error_Handler ();
                }
//                started = true;
//        }

        if (HAL_ADC_PollForConversion (&hadc, 10) != HAL_OK) {
                Error_Handler ();
        }

        uint32_t tmp = HAL_ADC_GetValue (&hadc);

#if 1
        Debug *debug = Debug::singleton ();
        debug->print (tmp);
        debug->print (" ");

        if (HAL_ADC_Start (&hadc) != HAL_OK) {
                Error_Handler ();
        }

        if (HAL_ADC_PollForConversion (&hadc, 10) != HAL_OK) {
                Error_Handler ();
        }

        tmp = HAL_ADC_GetValue (&hadc);
        debug->print (tmp);
        debug->print ("\n");
#endif

        return tmp;
}

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
        screen->setDots (T145003::DOT5 | T145003::DOT3);
        screen->setBatteryLevel (5);
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

        StopWatch *stopWatch = StopWatch::singleton ();
        stopWatch->setDisplay (screen);
        FastStateMachine *fStateMachine = FastStateMachine::singleton ();
        fStateMachine->setStopWatch (stopWatch);
        stopWatch->setStateMachine (fStateMachine);
        InfraRedBeam *beam = InfraRedBeam::singleton ();
        fStateMachine->setIr (beam);
        fStateMachine->setDisplay (screen);
        fStateMachine->setBuzzer (buzzer);

        beam->init ();
        stopWatch->init ();

        /*+-------------------------------------------------------------------------+*/
        /*| Battery, light sensor                                                   |*/
        /*+-------------------------------------------------------------------------+*/

        VoltMeter *batteryVoltMeter = VoltMeter::instance ();
        batteryVoltMeter->init (ADC_CHANNEL_3, GPIOA, GPIO_PIN_3);
        Timer batteryTimer;

        VoltMeter *ambientLightVoltMeter = VoltMeter::instance ();
        ambientLightVoltMeter->init (ADC_CHANNEL_2, GPIOA, GPIO_PIN_2);

        /*+-------------------------------------------------------------------------+*/
        /*| USB                                                                     |*/
        /*+-------------------------------------------------------------------------+*/

        //        /* Init Device Library */
        //        USBD_Init (&USBD_Device, &VCP_Desc, 0);
        //
        //        /* Add Supported Class */
        //        USBD_RegisterClass (&USBD_Device, USBD_CDC_CLASS);
        //
        //        /* Add CDC Interface Class */
        //        USBD_CDC_RegisterInterface (&USBD_Device, &USBD_CDC_fops);
        //
        //        /* Start Device Process */
        //        USBD_Start (&USBD_Device);
        //        printf ("init OK\n");

        while (1) {
                screen->refresh ();
                buzzer->run ();

                if (batteryTimer.isExpired ()) {
                        batteryTimer.start (1000);
                        uint8_t batteryVoltage = batteryVoltMeter->getVoltage ();

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

                        //                        uint8_t ambientLightVoltage = ambientLightVoltMeter->getVoltage ();

                        //                        if (!screen->getBacklight () && ambientLightVoltage < 50) {
                        //                                screen->setBacklight (true);
                        //                        }
                        //                        else if (screen->getBacklight () && ambientLightVoltage > 80) {
                        //                                screen->setBacklight (false);
                        //                        }
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
