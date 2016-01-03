#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
#include "config.h"
#include "7segmentLed.h"

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

#define PLATES_NUM 4
#define SEGMENTS_PER_PLATE_NUM 12

// Tells which segments in given plate are lit and which are not.
//static uint16_t plate[PLATES_NUM] = { 0xffff, 0xffff, 0xffff, 0xffff };
static uint16_t plate[PLATES_NUM] = { 0xffff, 0xffff, 0xffff, 0xffff };

static GPIO_TypeDef *platePort[PLATES_NUM] = { GPIOB, GPIOB, GPIOB, GPIOB };

static uint16_t platePin[PLATES_NUM] = { GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12 };

static GPIO_TypeDef *segmentPort[SEGMENTS_PER_PLATE_NUM] = { GPIOB, GPIOB, GPIOB, GPIOA,
                                                             GPIOA, GPIOA, GPIOA, GPIOA,
                                                             GPIOA, GPIOB, GPIOB, GPIOB };

static uint16_t segmentPin[SEGMENTS_PER_PLATE_NUM] = { GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_8,
                                                       GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_13, GPIO_PIN_14,
                                                       GPIO_PIN_15, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5 };

/*****************************************************************************/

int main (void)
{
        HAL_Init ();
        SystemClock_Config ();
        //        segment7Init ();

        __HAL_RCC_GPIOB_CLK_ENABLE (); // Włączenie zegara.
        __HAL_RCC_GPIOA_CLK_ENABLE (); // Włączenie zegara.
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        gpioInitStruct.Pull = GPIO_NOPULL;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;
//        HAL_GPIO_Init (GPIOB, &gpioInitStruct);

        for (int i = 0; i < PLATES_NUM; ++i) {
                gpioInitStruct.Pin = platePin[i];
                HAL_GPIO_Init (platePort[i], &gpioInitStruct);
        }

        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                gpioInitStruct.Pin = segmentPin[i];
                HAL_GPIO_Init (segmentPort[i], &gpioInitStruct);
        }

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

        //        /**
        //         * Stop-watch
        //         */
        //        stopWatchTimHandle.Instance = TIM14;

        //        // 100Hz
        //        stopWatchTimHandle.Init.Period = 100;
        //        stopWatchTimHandle.Init.Prescaler = (uint32_t)(HAL_RCC_GetHCLKFreq () / 10000) - 1;
        //        stopWatchTimHandle.Init.ClockDivision = 0;
        //        stopWatchTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
        //        stopWatchTimHandle.Init.RepetitionCounter = 0;

        //        // Uwaga! Zpisać to!!! Msp init jest wywoływane PRZED TIM_Base_SetConfig
        //        __HAL_RCC_TIM14_CLK_ENABLE ();
        //        HAL_NVIC_SetPriority (TIM14_IRQn, 0, 0);
        //        HAL_NVIC_EnableIRQ (TIM14_IRQn);

        //        if (HAL_TIM_Base_Init (&stopWatchTimHandle) != HAL_OK) {
        //                Error_Handler ();
        //        }

        //        if (HAL_TIM_Base_Start_IT (&stopWatchTimHandle) != HAL_OK) {
        //                Error_Handler ();
        //        }

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

                for (int p = 0; p < PLATES_NUM; ++p) {

                        platePort[p]->BSRR = platePin[p]; // Set = floating
                        platePort[p]->PUPDR &= ~((platePin[p] * platePin[p]) << 1); // No pull up / pull down on entire GPIOB


                        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                                if (plate[0] & (1 << i)) { // Segment i should be ON.
                                        segmentPort[i]->BSRR = segmentPin[i] << 16;
                                }
                                else { // Segment i should be OFF.
                                        segmentPort[i]->BSRR = segmentPin[i];
                                }
                        }

                        HAL_Delay (1);

                        platePort[p]->BSRR = platePin[p] << 16; // Reset common

                        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                                if (plate[0] & (1 << i)) {
                                        segmentPort[i]->BSRR = segmentPin[i];
                                }
                                else {
                                        segmentPort[i]->BSRR = segmentPin[i] << 16;
                                }
                        }

                        HAL_Delay (1);

                        platePort[p]->BSRR = platePin[p]; // Set = floating
                        platePort[p]->PUPDR |= ((platePin[p] * platePin[p]) << 1);

                }
//                /*---------------------------------------------------------------------------*/

//                GPIOB->OTYPER &= ~GPIO_PIN_5; // PP

//                GPIOB->BSRR = GPIO_PIN_5; // Set
//                GPIOB->BSRR = GPIO_PIN_3 << 16;
//                HAL_Delay (1);

//                GPIOB->BSRR = GPIO_PIN_5 << 16; // Reset
//                GPIOB->BSRR = GPIO_PIN_3;
//                HAL_Delay (1);

//                GPIOB->OTYPER |= GPIO_PIN_5; // OD
//                                             //                GPIOB->OTYPER |= GPIO_PIN_3; // OD
//                GPIOB->BSRR = GPIO_PIN_5;    // Set

//                /*---------------------------------------------------------------------------*/

//                GPIOB->OTYPER &= ~GPIO_PIN_6; // PP

//                GPIOB->BSRR = GPIO_PIN_6; // Set
//                GPIOB->BSRR = GPIO_PIN_3;
//                HAL_Delay (1);

//                GPIOB->BSRR = GPIO_PIN_6 << 16; // Reset
//                GPIOB->BSRR = GPIO_PIN_3 << 16;
//                HAL_Delay (1);

//                GPIOB->OTYPER |= GPIO_PIN_6; // OD
//                GPIOB->BSRR = GPIO_PIN_6;    // Set

//                /*---------------------------------------------------------------------------*/

//                GPIOB->OTYPER &= ~GPIO_PIN_7; // PP

//                GPIOB->BSRR = GPIO_PIN_7; // Set
//                GPIOB->BSRR = GPIO_PIN_3;
//                HAL_Delay (1);

//                GPIOB->BSRR = GPIO_PIN_7 << 16; // Reset
//                GPIOB->BSRR = GPIO_PIN_3 << 16;
//                HAL_Delay (1);

//                GPIOB->OTYPER |= GPIO_PIN_7; // OD
//                GPIOB->BSRR = GPIO_PIN_7;    // Set
        }
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
        segment7SetDigit (0, cntTmp % 10);
        cntTmp /= 10;
        // First digit of 1/100-s of second (0-99)
        segment7SetDigit (1, cntTmp % 10);
        cntTmp /= 10;

        // Second digit of second (0-99)
        segment7SetDigit (2, cntTmp % 10);
        cntTmp /= 10;
        // First digit of second (0-99)
        segment7SetDigit (3, cntTmp % 6);
        cntTmp /= 6;

        // One digit of miniutes
        segment7SetDigit (4, cntTmp % 10);

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
#endif
/*****************************************************************************/

static void SystemClock_Config (void)
{
        RCC_ClkInitTypeDef RCC_ClkInitStruct;
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

        /* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
        RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
                Error_Handler ();
        }
}
//static void SystemClock_Config (void)
//{
//        __HAL_RCC_PWR_CLK_ENABLE ();
//        __HAL_PWR_VOLTAGESCALING_CONFIG (PWR_REGULATOR_VOLTAGE_SCALE1);

//        RCC_OscInitTypeDef rccOscInitStruct;
//        rccOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // HSE, HSI, LSE, LSI, NONE
//        rccOscInitStruct.HSEState = RCC_HSE_ON;                   // ON, OFF, BYPASS
//        rccOscInitStruct.HSIState = RCC_HSI_OFF;
//        rccOscInitStruct.LSEState = RCC_LSE_OFF;
//        rccOscInitStruct.LSIState = RCC_LSI_OFF;
//        rccOscInitStruct.PLL.PLLState = RCC_PLL_ON;         // On / Off
//        rccOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; // HSE or HSI
//        rccOscInitStruct.PLL.PLLM = 8;                      // Between 0 and 63
//        rccOscInitStruct.PLL.PLLN = 336;                    // Betwen 192 and 432
//        rccOscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;          // RCC_PLLP_DIV2, RCC_PLLP_DIV4, RCC_PLLP_DIV6, RCC_PLLP_DIV8
//        rccOscInitStruct.PLL.PLLQ = 7;                      // Between 4 and 15.

//        if (HAL_RCC_OscConfig (&rccOscInitStruct) != HAL_OK) {
//                Error_Handler ();
//        }

//        RCC_ClkInitTypeDef rccClkInitStruct;

//        // ClockType mówi które zegary konfigurujemy. W tym przypadku konfigurujemy wszytskie.
//        rccClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//        rccClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // HSI, HSE lub PLL
//        rccClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//        rccClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//        rccClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

//        if (HAL_RCC_ClockConfig (&rccClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
//                Error_Handler ();
//        }
//}

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
