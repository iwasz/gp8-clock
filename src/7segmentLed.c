/*
 * 7segmentLed.c
 *
 *  Created on: Aug 21, 2015
 *      Author: liwaszkiewicz
 */

#include "7segmentLed.h"
#include <stm32f4xx_hal.h>
#include <string.h>

// For brightness controll
#define CYCLES_NO 10

extern void Error_Handler (void);
static void segment7SetDisplayOn (uint8_t displayNo, bool on);

/*
 *  _      a
 * |_|   f   b
 * |_|.    g
 *       e   c   dp
 *         d
 */
#define LEDA_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDA_PIN GPIO_PIN_0
#define LEDA_PORT GPIOC

#define LEDF_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDF_PIN GPIO_PIN_3
#define LEDF_PORT GPIOC

#define LEDB_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDB_PIN GPIO_PIN_1
#define LEDB_PORT GPIOC

#define LEDG_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDG_PIN GPIO_PIN_2
#define LEDG_PORT GPIOC

#define LEDE_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDE_PIN GPIO_PIN_5
#define LEDE_PORT GPIOC

#define LEDC_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDC_PIN GPIO_PIN_7
#define LEDC_PORT GPIOC

#define LEDD_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDD_PIN GPIO_PIN_4
#define LEDD_PORT GPIOC

#define LEDDP_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LEDDP_PIN GPIO_PIN_6
#define LEDDP_PORT GPIOC

/*
 *  _   _   _   _   _
 * |_| |_| |_| |_| |_|
 * |_|.|_|.|_|.|_|.|_|.
 *
 *  0   1   2   3   4
 */

#define LED_DIGIT0_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LED_DIGIT0_PIN GPIO_PIN_8
#define LED_DIGIT0_PORT GPIOC

#define LED_DIGIT1_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LED_DIGIT1_PIN GPIO_PIN_9
#define LED_DIGIT1_PORT GPIOC

#define LED_DIGIT2_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LED_DIGIT2_PIN GPIO_PIN_10
#define LED_DIGIT2_PORT GPIOC

#define LED_DIGIT3_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LED_DIGIT3_PIN GPIO_PIN_11
#define LED_DIGIT3_PORT GPIOC

#define LED_DIGIT4_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define LED_DIGIT4_PIN GPIO_PIN_12
#define LED_DIGIT4_PORT GPIOC

/*
 *  _      a
 * |_|   f   b
 * |_|.    g
 *       e   c   dp
 *         d
 */
static uint8_t font[] = {
        SEGMENT7_A | SEGMENT7_F | SEGMENT7_B | SEGMENT7_E | SEGMENT7_C | SEGMENT7_D, // 0
        SEGMENT7_B | SEGMENT7_C, // 1
        SEGMENT7_A | SEGMENT7_B | SEGMENT7_G | SEGMENT7_E | SEGMENT7_D, // 2
        SEGMENT7_A | SEGMENT7_B | SEGMENT7_G | SEGMENT7_C | SEGMENT7_D, // 3
        SEGMENT7_F | SEGMENT7_G | SEGMENT7_B | SEGMENT7_C, // 4
        SEGMENT7_A | SEGMENT7_F | SEGMENT7_G | SEGMENT7_C | SEGMENT7_D, // 5
        SEGMENT7_A | SEGMENT7_F | SEGMENT7_G | SEGMENT7_C | SEGMENT7_E | SEGMENT7_D, // 6
        SEGMENT7_A | SEGMENT7_B | SEGMENT7_C, // 7
        SEGMENT7_A | SEGMENT7_B | SEGMENT7_C  | SEGMENT7_D | SEGMENT7_E | SEGMENT7_F | SEGMENT7_G, // 8
        SEGMENT7_A | SEGMENT7_B | SEGMENT7_C  | SEGMENT7_D | SEGMENT7_F | SEGMENT7_G, // 9
};

static uint8_t segment[DISPLAYS_NO];
static uint8_t brightness;
static bool displayOn;
static TIM_HandleTypeDef timHandle;

/*
 *
 */
void segment7Init ()
{
        GPIO_InitTypeDef gpioInitStruct;

        // 8 GPIOs for single 7-segment display (each segment has its own GPIO + dot)
        LEDA_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDA_PIN;
        gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInitStruct.Pull = GPIO_PULLDOWN;
        gpioInitStruct.Speed = GPIO_SPEED_FAST;
        HAL_GPIO_Init (LEDA_PORT, &gpioInitStruct);

        LEDF_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDF_PIN;
        HAL_GPIO_Init (LEDF_PORT, &gpioInitStruct);

        LEDB_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDB_PIN;
        HAL_GPIO_Init (LEDB_PORT, &gpioInitStruct);

        LEDG_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDG_PIN;
        HAL_GPIO_Init (LEDG_PORT, &gpioInitStruct);

        LEDE_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDE_PIN;
        HAL_GPIO_Init (LEDE_PORT, &gpioInitStruct);

        LEDC_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDC_PIN;
        HAL_GPIO_Init (LEDC_PORT, &gpioInitStruct);

        LEDD_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDD_PIN;
        HAL_GPIO_Init (LEDD_PORT, &gpioInitStruct);

        LEDDP_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LEDDP_PIN;
        HAL_GPIO_Init (LEDDP_PORT, &gpioInitStruct);

        // GPIOS for turning on/off each 7-segment display as a whole.
        LED_DIGIT0_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LED_DIGIT0_PIN;
        HAL_GPIO_Init (LED_DIGIT0_PORT, &gpioInitStruct);

        LED_DIGIT1_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LED_DIGIT1_PIN;
        HAL_GPIO_Init (LED_DIGIT1_PORT, &gpioInitStruct);

        LED_DIGIT2_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LED_DIGIT2_PIN;
        HAL_GPIO_Init (LED_DIGIT2_PORT, &gpioInitStruct);

        LED_DIGIT3_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LED_DIGIT3_PIN;
        HAL_GPIO_Init (LED_DIGIT3_PORT, &gpioInitStruct);

        LED_DIGIT4_GPIO_CLK_ENABLE ();
        gpioInitStruct.Pin = LED_DIGIT4_PIN;
        HAL_GPIO_Init (LED_DIGIT4_PORT, &gpioInitStruct);


        // Variables used by the timer
        segment7SetDisplayOn (0, 0);
        segment7SetDisplayOn (1, 0);
        segment7SetDisplayOn (2, 0);
        segment7SetDisplayOn (3, 0);
        segment7SetDisplayOn (4, 0);


        bzero (segment, DISPLAYS_NO);
        segment7SetBrightness (10);
        segment7On ();

        // Timer for multiplexing displays
        timHandle.Instance = TIM4; // APB1 (wolniejsza max 42MHz)

        // 10kHz
        timHandle.Init.Period = (uint32_t)((HAL_RCC_GetHCLKFreq () / 2) / 10000) - 1;
        timHandle.Init.Prescaler = 0;
        timHandle.Init.ClockDivision = 0;
        timHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

        if (HAL_TIM_Base_Init (&timHandle) != HAL_OK) {
            Error_Handler();
        }

        __HAL_RCC_TIM4_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIM4_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ (TIM4_IRQn);

        if (HAL_TIM_Base_Start_IT (&timHandle) != HAL_OK) {
            Error_Handler();
        }
}

/*
 * Turn on and off individual displays.
 */
static void segment7SetDisplayOn (uint8_t displayNo, bool on)
{
        switch (displayNo) {
        case 0:
                LED_DIGIT0_PORT->BSRR = LED_DIGIT0_PIN << ((on) ? (0) : (16));
                break;
        case 1:
                LED_DIGIT1_PORT->BSRR = LED_DIGIT1_PIN << ((on) ? (0) : (16));
                break;
        case 2:
                LED_DIGIT2_PORT->BSRR = LED_DIGIT2_PIN << ((on) ? (0) : (16));
                break;
        case 3:
                LED_DIGIT3_PORT->BSRR = LED_DIGIT3_PIN << ((on) ? (0) : (16));
                break;
        case 4:
                LED_DIGIT4_PORT->BSRR = LED_DIGIT4_PIN << ((on) ? (0) : (16));
                break;
        };
}

/*
 * Turn on and off individual segments.
 */
static void segment7SetSegmentsOn (uint8_t segments)
{
        LEDA_PORT->BSRR = LEDA_PIN << ((segments & SEGMENT7_A) ? (0) : (16));
        LEDF_PORT->BSRR = LEDF_PIN << ((segments & SEGMENT7_F) ? (0) : (16));
        LEDB_PORT->BSRR = LEDB_PIN << ((segments & SEGMENT7_B) ? (0) : (16));
        LEDG_PORT->BSRR = LEDG_PIN << ((segments & SEGMENT7_G) ? (0) : (16));
        LEDE_PORT->BSRR = LEDE_PIN << ((segments & SEGMENT7_E) ? (0) : (16));
        LEDC_PORT->BSRR = LEDC_PIN << ((segments & SEGMENT7_C) ? (0) : (16));
        LEDD_PORT->BSRR = LEDD_PIN << ((segments & SEGMENT7_D) ? (0) : (16));
        LEDDP_PORT->BSRR = LEDDP_PIN << ((segments & SEGMENT7_DP) ? (0) : (16));
}

/*
 *
 */
void TIM4_IRQHandler (void)
{
        __HAL_TIM_CLEAR_IT (&timHandle, TIM_IT_UPDATE);

        // From 0 to 49 (example value when DISPLAYS_NO == 5 and CYCLES_NO == 10).
        static uint8_t cnt = 0;
        // Which segment to lit up. From 0 to 4.
        uint8_t segmentNo = cnt / CYCLES_NO;
        // Previous value for determining if there was a change or not. There's no point in doing anything if nothing changed.
        static int8_t prevSegmentNo = -1;

        // From 0 to 9. For brightnes control.
        uint8_t cycleNo = cnt % CYCLES_NO;
        // Duty cycle. Or conpletely off if displayOn is false.
        bool cycleOn = (cycleNo < brightness) && displayOn;
        static bool prevCycleOn = false;

        // If nothing happened, skip this tick.
        if (cycleOn != prevCycleOn || segmentNo != prevSegmentNo) {

                if (segmentNo != prevSegmentNo) {
                        segment7SetDisplayOn (prevSegmentNo, false);
                }

                // Set individual segments to segment[segmentNo]
                segment7SetSegmentsOn (segment[segmentNo]);
                // Turn apropriate display on or off.
                segment7SetDisplayOn (segmentNo, cycleOn);
        }

        cnt = (cnt + 1) % (DISPLAYS_NO * CYCLES_NO);
        prevSegmentNo = segmentNo;
        prevCycleOn = cycleOn;
}

/*
 *
 */
void segment7Set (uint8_t displayNo, uint8_t segments)
{
        segment[displayNo] = segments;
}

/*
 *
 */
uint8_t segment7Get (uint8_t displayNo)
{
        return segment[displayNo];
}

/**
 *
 */
void segment7On ()
{
        displayOn = true;
}

/**
 *
 */
void segment7Off ()
{
        displayOn = false;
}

/**
 *
 */
bool segment7IsOn ()
{
        return displayOn;
}

/*
 *
 */
void segment7SetBrightness (uint8_t i)
{
        brightness = i;
}


/*
 *
 */
uint8_t segment7GetBrightness ()
{
        return brightness;
}

/*
 *
 */
void segment7SetDecimalNumber (uint32_t decimal)
{
        for (int i = 0; i < DISPLAYS_NO; ++i) {
                uint8_t digit = decimal % 10;
                segment7Set (i, font[digit]);
                decimal /= 10;
        }
}
