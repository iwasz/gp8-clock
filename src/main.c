#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
#include "config.h"
#include "7segmentLed.h"
#include "weight_scale_lcd.h"
#include <stdbool.h>

static void SystemClock_Config (void);
//USBD_HandleTypeDef USBD_Device;
extern uint32_t noOfUpdateEventsSinceLastRise;
//static TIM_HandleTypeDef stopWatchTimHandle;

typedef enum { WATCH_INIT,
               WATCH_STOPPED,
               WATCH_RUNNING } WatchState;

uint8_t state = WATCH_INIT;

#define EVENT_TRESHOLD 300
// Delay between events
uint32_t timeFromLastEvent = EVENT_TRESHOLD + 1;

/**
 * How much update events since last rise (noOfUpdateEventsSinceLastRise) indicates
 * that light path is cut. Roughly proportional to ms.
 */
#define UPDATE_EVENT_TRESHOLD 50
bool beep = false;

I2C_HandleTypeDef i2cHandle;

/*****************************************************************************/

int main (void)
{
        HAL_Init ();
        SystemClock_Config ();

        /*---------------------------------------------------------------------------*/

        GPIO_InitTypeDef gpioInitStruct;
        __HAL_RCC_GPIOB_CLK_ENABLE ();

        /* I2C TX GPIO pin configuration  */
        gpioInitStruct.Pin = GPIO_PIN_6;
        gpioInitStruct.Mode = GPIO_MODE_AF_OD;
        gpioInitStruct.Pull = GPIO_PULLUP;
        gpioInitStruct.Speed = GPIO_SPEED_HIGH;
        gpioInitStruct.Alternate = GPIO_AF1_I2C1;

        HAL_GPIO_Init (GPIOB, &gpioInitStruct);

        gpioInitStruct.Pin = GPIO_PIN_7;
        gpioInitStruct.Alternate = GPIO_AF1_I2C1;

        HAL_GPIO_Init (GPIOB, &gpioInitStruct);

        /*---------------------------------------------------------------------------*/

        __HAL_RCC_I2C1_CLK_ENABLE ();

        i2cHandle.Instance = I2C1;
        i2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        i2cHandle.Init.OwnAddress1 = 0x00;
        i2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
        i2cHandle.Init.OwnAddress2 = 0x00;
        i2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        i2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
        i2cHandle.Init.Timing = 0x00E0D3FF;

        if (HAL_I2C_Init (&i2cHandle) != HAL_OK) {
                /* Initialization Error */
                Error_Handler ();
        }

        /*---------------------------------------------------------------------------*/
#define DOT_TRIANGLE 1
        uint8_t txBuffer[] = {
                // 0xc8, 0x00, 0x00, 0xbe | DOT_TRIANGLE,  0x06, 0x7c, 0x5e, 0xc6,
                0xc8, 0x00, 0x00, 0xda | DOT_TRIANGLE,  0xfa, 0x0e, 0xfe, 0xde,
        };

#define ADDRESS_WRITE 0x70

        while (HAL_I2C_Master_Transmit (&i2cHandle, (uint8_t)ADDRESS_WRITE, (uint8_t *)txBuffer, sizeof (txBuffer), 10000) != HAL_OK) {
                /* Error_Handler() function is called when Timeout error occurs.
                 When Acknowledge failure occurs (Slave don't acknowledge it's address)
                 Master restarts communication */
                if (HAL_I2C_GetError (&i2cHandle) != HAL_I2C_ERROR_AF) {
                        Error_Handler ();
                }
        }

//        uint8_t txBuffer2[] = {
//                //0x80, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//                0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//        };

//        while (HAL_I2C_Master_Transmit (&i2cHandle, (uint8_t)ADDRESS_WRITE, (uint8_t *)txBuffer2, sizeof (txBuffer2), 10000) != HAL_OK) {
//                /* Error_Handler() function is called when Timeout error occurs.
//                 When Acknowledge failure occurs (Slave don't acknowledge it's address)
//                 Master restarts communication */
//                if (HAL_I2C_GetError (&i2cHandle) != HAL_I2C_ERROR_AF) {
//                        Error_Handler ();
//                }
//        }

#if 0
        // Backlight
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_1;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init (GPIOA, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1, 0);

        __HAL_RCC_GPIOC_CLK_ENABLE ();
        RCC->BDCR &= ~RCC_BDCR_LSEON;
        gpioInitStruct.Pin = GPIO_PIN_15;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init (GPIOC, &gpioInitStruct);
        HAL_GPIO_WritePin (GPIOC, GPIO_PIN_15, 0);

        /*---------------------------------------------------------------------------*/

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
                if (beep) {
                        beep = false;
                        //                        GPIOA->BSRR |= GPIO_PIN_1;
                        GPIOC->BSRR |= GPIO_PIN_15;
                        HAL_Delay (100);
                        GPIOA->BSRR |= GPIO_PIN_1 << 16;
                        //                        GPIOC->BSRR |= GPIO_PIN_15 << 16;
                }
        }
#endif

        while (1)
                ;
}

#if 0
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

void SystemClock_Config (void)
{

        RCC_OscInitTypeDef RCC_OscInitStruct;
        /* Select HSI48 Oscillator as PLL source */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
        RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
        RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
        RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;

        if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK) {
                Error_Handler ();
        }

        RCC_ClkInitTypeDef RCC_ClkInitStruct;
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
