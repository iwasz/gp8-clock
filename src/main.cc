#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
#include "I2CLcdDataLink.h"
#include "PCF85176Driver.h"
#include "T145003.h"
#include "config.h"
#include <cstdbool>
#include <cstring>

static void SystemClock_Config (void);
// USBD_HandleTypeDef USBD_Device;
uint32_t noOfUpdateEventsSinceLastRise;
static TIM_HandleTypeDef stopWatchTimHandle;
static TIM_HandleTypeDef timHandle;

typedef enum { WATCH_INIT, WATCH_STOPPED, WATCH_RUNNING } WatchState;

uint8_t state = WATCH_STOPPED;

#define EVENT_TRESHOLD 300
// Delay between events
uint32_t timeFromLastEvent = EVENT_TRESHOLD + 1;

/**
 * How much update events since last rise (noOfUpdateEventsSinceLastRise) indicates
 * that light path is cut. Roughly proportional to ms.
 */
#define UPDATE_EVENT_TRESHOLD 50
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

/*+-------------------------------------------------------------------------+*/
/*| IR detection timer 10kHz                                                |*/
/*+-------------------------------------------------------------------------+*/
#if 1
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
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_AF_PP;
        gpioInitStruct.Pull = GPIO_PULLUP;
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
#endif
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

#if 1
/**
 * Stop-watch ISR.
 * Here the value displayed is updated. 100Hz
 */
extern "C" void TIM14_IRQHandler (void)
{
        __HAL_TIM_CLEAR_IT (&stopWatchTimHandle, TIM_IT_UPDATE);

        static uint16_t cnt = 0;
        uint16_t cntTmp = cnt;
        T145003 *screen = T145003::singleton ();

        // 2nd digit of 1/100-s of second (0-99)
        screen->setDigit (4, cntTmp % 10);
        cntTmp /= 10;
        // First digit of 1/100-s of second (0-99)
        screen->setDigit (3, cntTmp % 10);
        cntTmp /= 10;

        // Second digit of second (0-99)
        screen->setDigit (2, cntTmp % 10);
        cntTmp /= 10;
        // First digit of second (0-99)
        screen->setDigit (1, cntTmp % 6);
        cntTmp /= 6;

        // One digit of miniutes
        screen->setDigit (0, cntTmp % 10);

        switch (state) {
        case WATCH_INIT:
                break;
        }

        if (state == WATCH_RUNNING) {
                ++cnt;
        }

        ++timeFromLastEvent;

        if (timeFromLastEvent > EVENT_TRESHOLD && noOfUpdateEventsSinceLastRise >= UPDATE_EVENT_TRESHOLD) {
                timeFromLastEvent = 0;
                beep = true;

                if (state == WATCH_RUNNING) {
                        state = WATCH_STOPPED;
                }
                else if (state == WATCH_STOPPED) {
                        cnt = 0;
                        state = WATCH_RUNNING;
                }
        }
}
#endif

/*****************************************************************************/

extern "C" void TIM3_IRQHandler ()
{
        /*
         * I.C. ~1kHz
         * Uwaga! Makro __HAL_TIM_GET_IT_SOURCE ma mylną nazwę, bo ono sprawdza rejestr DIER, czyli
         * sprawdza, czy dane przerwanie jest WŁĄCZONE czy nie. Jeśli by nie było włączone, to byśmy
         * nigdy się nie znaleźli w ISR z powodu tego konkretnego przerwania.
         */
        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_CC4) /*&& __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_IT_CC1)*/) {
                __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_CC4);
                //                 static int i = 0;
                //                 static int32_t prevVal = -1;
                //
                //                 int32_t val = HAL_TIM_ReadCapturedValue (&timHandle, TIM_CHANNEL_4);
                //
                //
                //                 if (!(++i % 1000)) {
                //                         //inputCapture = (uint16_t)((val > prevVal) ? (val - prevVal) : (prevVal - val));
                //                         inputCapture = noOfUpdateEventsSinceLastRise;
                //                 }
                //
                //
                //                 prevVal = val;
                noOfUpdateEventsSinceLastRise = 0;
                return;

                //                static int i = 0;
                //                segment7SetDisplayOn (0, ++i % 2);
                //                segment7SetSegmentsOn (0xff);
        }

        //        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_CC2) && __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_azsZZSSQIT_CC2)) {
        //                __HAL_TIM_CLEAR_FLAG (&timHandle, TIM_FLAG_CC2);

        //        }

        // 10kHz
        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_UPDATE) && __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_IT_UPDATE)) {
                __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_UPDATE);
                ++noOfUpdateEventsSinceLastRise;

                //                // From 0 to 49 (example value when DISPLAYS_NO == 5 and CYCLES_NO == 10).
                //                static uint8_t cnt = 0;
                //                // Which segment to lit up. From 0 to 4.
                //                uint8_t segmentNo = cnt / CYCLES_NO;
                //                // Previous value for determining if there was a change or not. There's no point in doing anything if nothing changed.
                //                static int8_t prevSegmentNo = -1;

                //                // From 0 to 9. For brightnes control.
                //                uint8_t cycleNo = cnt % CYCLES_NO;
                //                // Duty cycle. Or conpletely off if displayOn is false.
                //                bool cycleOn = (cycleNo < brightness) && displayOn;
                //                static bool prevCycleOn = false;

                //                // If nothing happened, skip this tick.
                //                if (cycleOn != prevCycleOn || segmentNo != prevSegmentNo) {

                //                        if (segmentNo != prevSegmentNo) {
                //                                segment7SetDisplayOn (prevSegmentNo, false);
                //                        }

                //                        // Set individual segments to segment[segmentNo]
                //                        segment7SetSegmentsOn (segment[segmentNo]);
                //                        // Turn apropriate display on or off.
                //                        segment7SetDisplayOn (segmentNo, cycleOn);
                //                }

                //                cnt = (cnt + 1) % (DISPLAYS_NO * CYCLES_NO);
                //                prevSegmentNo = segmentNo;
                //                prevCycleOn = cycleOn;
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
