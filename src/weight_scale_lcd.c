/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <stdint.h>
#include <stm32f0xx_hal.h>
#include "weight_scale_lcd.h"
#include "config.h"

// Tells which segments in given plate are lit and which are not.
static uint16_t plate[PLATES_NUM] = { 0, 0, 0, 0 };

static uint16_t digit[10][PLATES_NUM] = {
        { 0x000c, 0x0008, 0x000c, 0x0004 },
        { 0x0000, 0x0008, 0x0008, 0x0000 },
        { 0x0008, 0x000c, 0x0004, 0x0004 },
        { 0x0008, 0x000c, 0x0008, 0x0004 },
        { 0x0004, 0x000c, 0x0008, 0x0000 },
        { 0x000c, 0x0004, 0x0008, 0x0004 },
        { 0x000c, 0x0004, 0x000c, 0x0004 },
        { 0x0008, 0x0008, 0x0008, 0x0000 },
        { 0x000c, 0x000c, 0x000c, 0x0004 },
        { 0x000c, 0x000c, 0x0008, 0x0004 },
};

static GPIO_TypeDef *platePort[PLATES_NUM] = { GPIOB, GPIOB, GPIOB, GPIOB };

//static uint16_t platePin[PLATES_NUM] = { GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12 };
static uint16_t platePin[PLATES_NUM] = { GPIO_PIN_12, GPIO_PIN_11, GPIO_PIN_10, GPIO_PIN_2 };

static GPIO_TypeDef *segmentPort[SEGMENTS_PER_PLATE_NUM] = { GPIOB, GPIOB, GPIOB, GPIOA,
                                                             GPIOA, GPIOA, GPIOA, GPIOB,
                                                             GPIOB, GPIOB, GPIOB, GPIOB };

static uint16_t segmentPin[SEGMENTS_PER_PLATE_NUM] = { GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_8,
                                                       GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_15, GPIO_PIN_3,
                                                       GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7 };

static TIM_HandleTypeDef timHandle;
uint32_t noOfUpdateEventsSinceLastRise = 0;

void wslcdSetDigit (uint8_t digitNo, uint8_t d)
{
        // Multiply x2 because this LCD screen's pins are laidout in pairs.
        digitNo <<= 1;
        uint16_t seg = ~(0x000c << digitNo);
        plate[0] &= seg;
        plate[0] |= digit[d][0] << digitNo;
        plate[1] &= seg;
        plate[1] |= digit[d][1] << digitNo;
        plate[2] &= seg;
        plate[2] |= digit[d][2] << digitNo;
        plate[3] &= ~(0x0004 << digitNo);
        plate[3] |= digit[d][3] << digitNo;
}

/*****************************************************************************/

static void wslcdInitLcdPins ();
static void wslcdInitRefreshTimer ();

void wslcdInit ()
{
        wslcdInitLcdPins ();
        wslcdInitRefreshTimer ();
}

/*---------------------------------------------------------------------------*/

static void wslcdInitLcdPins ()
{
        __HAL_RCC_GPIOB_CLK_ENABLE (); // Włączenie zegara.
        __HAL_RCC_GPIOA_CLK_ENABLE (); // Włączenie zegara.
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        gpioInitStruct.Pull = GPIO_NOPULL;
        gpioInitStruct.Speed = GPIO_SPEED_LOW;

        for (int i = 0; i < PLATES_NUM; ++i) {
                gpioInitStruct.Pin = platePin[i];
                HAL_GPIO_Init (platePort[i], &gpioInitStruct);
        }

        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                gpioInitStruct.Pin = segmentPin[i];
                HAL_GPIO_Init (segmentPort[i], &gpioInitStruct);
        }
}

/*---------------------------------------------------------------------------*/

static void wslcdInitRefreshTimer ()
{
        // Timer for multiplexing displays
        timHandle.Instance = TIM3;

        timHandle.Init.Period = (uint32_t) (HAL_RCC_GetHCLKFreq () / 10000) - 1;
        timHandle.Init.Prescaler = 0;
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

        /*---------------------------------------------------------------------------*/

        // Konfigureacja kanału. Input Capture. Wejście.
        __HAL_RCC_GPIOB_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
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
}

/*****************************************************************************/

void TIM3_IRQHandler (void)
{
/*
         * I.C. ~1kHz
         * Uwaga! Makro __HAL_TIM_GET_IT_SOURCE ma mylną nazwę, bo ono sprawdza rejestr DIER, czyli
         * sprawdza, czy dane przerwanie jest WŁĄCZONE czy nie. Jeśli by nie było włączone, to byśmy
         * nigdy się nie znaleźli w ISR z powodu tego konkretnego przerwania.
         */
#if 1
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
#endif
        //        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_CC2) && __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_azsZZSSQIT_CC2)) {
        //                __HAL_TIM_CLEAR_FLAG (&timHandle, TIM_FLAG_CC2);

        //        }

        static uint8_t stage = 7;
        static uint8_t prescale = 0;

        if (__HAL_TIM_GET_FLAG (&timHandle, TIM_FLAG_UPDATE) && __HAL_TIM_GET_IT_SOURCE (&timHandle, TIM_IT_UPDATE)) {
                __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_UPDATE);

                // 10kHz
                ++noOfUpdateEventsSinceLastRise;
                if (++prescale < 10) {
                        return;
                }
                prescale = 0;

                uint8_t p = stage % 4;

                // Middle
                platePort[p]->BSRR = platePin[p]; // Set = floating
                platePort[p]->PUPDR |= ((platePin[p] * platePin[p]) << 1);

                if (++stage >= 8) {
                        stage = 0;
                }

                p = stage % 4;

                if (stage < 4) {
                        // High
                        platePort[p]->BSRR = platePin[p];                           // Set = floating
                        platePort[p]->PUPDR &= ~((platePin[p] * platePin[p]) << 1); // No pull up / pull down on entire GPIOB

                        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                                if (plate[p] & (1 << i)) { // Segment i should be DARK i.e. visible
                                        segmentPort[i]->BSRR = segmentPin[i] << 16;
                                }
                                else { // Segment i should be invisible
                                        segmentPort[i]->BSRR = segmentPin[i];
                                }
                        }
                }
                else {
                        // Low
                        platePort[p]->BSRR = platePin[p] << 16; // Reset common

                        for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                                if (plate[p] & (1 << i)) { // Segment i should be DARK i.e. visible
                                        segmentPort[i]->BSRR = segmentPin[i];
                                }
                                else { // Segment i should be invisible
                                        segmentPort[i]->BSRR = segmentPin[i] << 16;
                                }
                        }
                }
        }
}

/*****************************************************************************/
#if 0
#define DELAY_MS 1

void wslcdRefresh ()
{
        for (int p = 0; p < PLATES_NUM; ++p) {

                // High
                platePort[p]->BSRR = platePin[p];                           // Set = floating
                platePort[p]->PUPDR &= ~((platePin[p] * platePin[p]) << 1); // No pull up / pull down on entire GPIOB

                for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                        if (plate[p] & (1 << i)) { // Segment i should be DARK i.e. visible
                                segmentPort[i]->BSRR = segmentPin[i] << 16;
                        }
                        else { // Segment i should be invisible
                                segmentPort[i]->BSRR = segmentPin[i];
                        }
                }

                HAL_Delay (DELAY_MS);

                // Middle
                platePort[p]->BSRR = platePin[p]; // Set = floating
                platePort[p]->PUPDR |= ((platePin[p] * platePin[p]) << 1);
        }

        for (int p = 0; p < PLATES_NUM; ++p) {

                // Low
                platePort[p]->BSRR = platePin[p] << 16; // Reset common

                for (int i = 0; i < SEGMENTS_PER_PLATE_NUM; ++i) {
                        if (plate[p] & (1 << i)) { // Segment i should be DARK i.e. visible
                                segmentPort[i]->BSRR = segmentPin[i];
                        }
                        else { // Segment i should be invisible
                                segmentPort[i]->BSRR = segmentPin[i] << 16;
                        }
                }

                HAL_Delay (DELAY_MS);

                // Middle
                platePort[p]->BSRR = platePin[p]; // Set = floating
                platePort[p]->PUPDR |= ((platePin[p] * platePin[p]) << 1);
        }
}
#endif
