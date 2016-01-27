#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
#include "config.h"
#include "7segmentLed.h"
#include "weight_scale_lcd.h"

static void SystemClock_Config (void);
//USBD_HandleTypeDef USBD_Device;
extern uint32_t noOfUpdateEventsSinceLastRise;
static TIM_HandleTypeDef stopWatchTimHandle;

typedef enum { WATCH_STOPPED,
               WATCH_RUNNING } WatchState;
uint8_t state = WATCH_STOPPED;

#define EVENT_TRESHOLD 300
// Delay between events
uint32_t timeFromLastEvent = EVENT_TRESHOLD + 1;

/**
 * How much update events since last rise (noOfUpdateEventsSinceLastRise) indicates
 * that light path is cut.
 */
#define UPDATE_EVENT_TRESHOLD 50

/*****************************************************************************/

int main (void)
{
        HAL_Init ();
        SystemClock_Config ();
        wslcdInit ();

        // Backlight
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init (GPIOA, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, 0);

        //        gpioInitStruct.Pin = GPIO_PIN_5;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);
        //        gpioInitStruct.Pin = GPIO_PIN_4;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);
        //        GPIOB->BSRR = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; // Set

        //        while (1) {
        //                GPIOB->BSRR = GPIO_PIN_4; // Set = floating
        //                GPIOB->PUPDR = 2 << (4 * 2); // Pull down on pin 4

        //                HAL_Delay (1);

        //                GPIOB->BSRR = GPIO_PIN_4; // Set = floating
        //                GPIOB->PUPDR = 0; // No pull up / pull down on entire GPIOB

        //                HAL_Delay (1);

        //                GPIOB->BSRR = GPIO_PIN_4; // Set = floating
        //                GPIOB->PUPDR = 2 << (4 * 2); // Pull down on pin 4

        //                HAL_Delay (1);

        //                GPIOB->BSRR = GPIO_PIN_4 << 16; // Reset = 0
        //                HAL_Delay (1);
        //        }

        //        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        //        gpioInitStruct.Pull = GPIO_NOPULL;
        //        gpioInitStruct.Pin = GPIO_PIN_3;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);
        //        gpioInitStruct.Pin = GPIO_PIN_2;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);
        //        gpioInitStruct.Pin = GPIO_PIN_1;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);
        //        gpioInitStruct.Pin = GPIO_PIN_0;
        //        HAL_GPIO_Init (GPIOB, &gpioInitStruct);

        // Stop-watch
        stopWatchTimHandle.Instance = TIM14;

        // 100Hz
        stopWatchTimHandle.Init.Period = 100;
        stopWatchTimHandle.Init.Prescaler = (uint32_t) (HAL_RCC_GetHCLKFreq () / 10000) - 1;
        stopWatchTimHandle.Init.ClockDivision = 0;
        stopWatchTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
        stopWatchTimHandle.Init.RepetitionCounter = 0;

        // Uwaga! Zpisać to!!! Msp init jest wywoływane PRZED TIM_Base_SetConfig
        __HAL_RCC_TIM14_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIM14_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ (TIM14_IRQn);

        if (HAL_TIM_Base_Init (&stopWatchTimHandle) != HAL_OK) {
                Error_Handler ();
        }

        if (HAL_TIM_Base_Start_IT (&stopWatchTimHandle) != HAL_OK) {
                Error_Handler ();
        }

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
        }
}

/**
 * Stop-watch ISR.
 * Here the value displayed is updated. 100Hz
 */
void TIM14_IRQHandler (void)
{
        __HAL_TIM_CLEAR_IT (&stopWatchTimHandle, TIM_IT_UPDATE);

        static uint16_t cnt = 0;
        uint16_t cntTmp = cnt;

        // Second digit of 1/100-s of second (0-99)
        wslcdSetDigit (4, cntTmp % 10);
        cntTmp /= 10;
        // First digit of 1/100-s of second (0-99)
        wslcdSetDigit (3, cntTmp % 10);
        cntTmp /= 10;

        // Second digit of second (0-99)
        wslcdSetDigit (2, cntTmp % 10);
        cntTmp /= 10;
        // First digit of second (0-99)
        wslcdSetDigit (1, cntTmp % 6);
        cntTmp /= 6;

        // One digit of miniutes
        wslcdSetDigit (0, cntTmp % 10);

        if (state == WATCH_RUNNING) {
                ++cnt;
        }

        ++timeFromLastEvent;

        if (timeFromLastEvent > EVENT_TRESHOLD && noOfUpdateEventsSinceLastRise >= UPDATE_EVENT_TRESHOLD) {
                timeFromLastEvent = 0;

                if (state == WATCH_RUNNING) {
                        state = WATCH_STOPPED;
                }
                else if (state == WATCH_STOPPED) {
                        cnt = 0;
                        state = WATCH_RUNNING;
                }
        }
}

/*****************************************************************************/

void SystemClock_Config (void)
{

        RCC_OscInitTypeDef RCC_OscInitStruct;
        RCC_ClkInitTypeDef RCC_ClkInitStruct;

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
        RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
        HAL_RCC_OscConfig (&RCC_OscInitStruct);

        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
        HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_1);

        HAL_SYSTICK_Config (HAL_RCC_GetHCLKFreq () / 1000);

        HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler (void)
{
        /* User may add here some code to deal with this error */
        while (1) {
        }
}
