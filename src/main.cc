#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
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

typedef enum { WATCH_INIT, WATCH_STOPPED, WATCH_RUNNING } WatchState;

uint8_t state = WATCH_STOPPED;

#define EVENT_TRESHOLD 300
// Delay between events
uint32_t timeFromLastEvent = EVENT_TRESHOLD + 1;

bool beep = false;

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

        beam->init ();
        stopWatch->init ();

        /*+-------------------------------------------------------------------------+*/
        /*| Backlight, beeper                                                       |*/
        /*+-------------------------------------------------------------------------+*/

        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init (GPIOA, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

        __HAL_RCC_GPIOC_CLK_ENABLE ();
        RCC->BDCR &= ~RCC_BDCR_LSEON;
        gpioInitStruct.Pin = GPIO_PIN_15;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init (GPIOC, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

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
                if (beep) {
                        beep = false;
                        GPIOC->BSRR |= GPIO_PIN_15;
                        HAL_Delay (100);
                        GPIOC->BSRR |= GPIO_PIN_15 << 16;
                }

                screen->refresh ();
        }
}

/*****************************************************************************/

/*****************************************************************************/

void SystemClock_Config (void)
{

        RCC_OscInitTypeDef RCC_OscInitStruct;
        RCC_ClkInitTypeDef RCC_ClkInitStruct;
        RCC_PeriphCLKInitTypeDef PeriphClkInit;

        /**Initializes the CPU, AHB and APB busses clocks
        */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
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
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
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
