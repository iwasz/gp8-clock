#include <stm32f4xx_hal.h>
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"
#include "config.h"
#include "7segmentLed.h"

static void SystemClock_Config (void);
USBD_HandleTypeDef USBD_Device;


static TIM_HandleTypeDef stopWatchTimHandle;



int main (void)
{
        HAL_Init ();
        SystemClock_Config ();
        segment7Init ();

/**
 * Stop-watch
 */

        // Timer for multiplexing displays
        stopWatchTimHandle.Instance = TIM5; // APB1 (wolniejsza max 42MHz)

        // 10kHz
        stopWatchTimHandle.Init.Period = 100;
        stopWatchTimHandle.Init.Prescaler = (uint32_t)((HAL_RCC_GetHCLKFreq () / 2) / 10000) - 1;
        stopWatchTimHandle.Init.ClockDivision = 0;
        stopWatchTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

        if (HAL_TIM_Base_Init (&stopWatchTimHandle) != HAL_OK) {
            Error_Handler();
        }

        __HAL_RCC_TIM5_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIM5_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ (TIM5_IRQn);

        if (HAL_TIM_Base_Start_IT (&stopWatchTimHandle) != HAL_OK) {
            Error_Handler();
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

void TIM5_IRQHandler (void)
{
        __HAL_TIM_CLEAR_IT (&stopWatchTimHandle, TIM_IT_UPDATE);
        static uint16_t cnt = 0;
        segment7SetDecimalNumber (++cnt);
}

static void SystemClock_Config (void)
{
        __HAL_RCC_PWR_CLK_ENABLE ();
        __HAL_PWR_VOLTAGESCALING_CONFIG (PWR_REGULATOR_VOLTAGE_SCALE1);

        RCC_OscInitTypeDef rccOscInitStruct;
        rccOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // HSE, HSI, LSE, LSI, NONE
        rccOscInitStruct.HSEState = RCC_HSE_ON;               // ON, OFF, BYPASS
        rccOscInitStruct.HSIState = RCC_HSI_OFF;
        rccOscInitStruct.LSEState = RCC_LSE_OFF;
        rccOscInitStruct.LSIState = RCC_LSI_OFF;
        rccOscInitStruct.PLL.PLLState = RCC_PLL_ON;               // On / Off
        rccOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;       // HSE or HSI
        rccOscInitStruct.PLL.PLLM = 16;                      // Between 0 and 63
        rccOscInitStruct.PLL.PLLN = 336;                   // Betwen 192 and 432
        rccOscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // RCC_PLLP_DIV2, RCC_PLLP_DIV4, RCC_PLLP_DIV6, RCC_PLLP_DIV8
        rccOscInitStruct.PLL.PLLQ = 7;                      // Between 4 and 15.

        if (HAL_RCC_OscConfig (&rccOscInitStruct) != HAL_OK) {
                Error_Handler ();
        }

        RCC_ClkInitTypeDef rccClkInitStruct;

        // ClockType mówi które zegary konfigurujemy. W tym przypadku konfigurujemy wszytskie.
        rccClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
        rccClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // HSI, HSE lub PLL
        rccClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        rccClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        rccClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

        if (HAL_RCC_ClockConfig (&rccClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
                Error_Handler ();
        }
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
