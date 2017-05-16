#include <stm32f0xx_hal.h>
//#include "usbd_core.h"
//#include "usbd_desc.h"
//#include "usbd_cdc.h"
//#include "usbd_cdc_interface.h"
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

struct ILcdDataLink {
        virtual ~ILcdDataLink () {}
        virtual void send (uint8_t *data, uint8_t len) = 0;
};

class I2CLcdDataLink : public ILcdDataLink {
public:
        virtual ~I2CLcdDataLink () {}
        static I2CLcdDataLink *singleton ();
        void init ();
        void send (uint8_t *data, uint8_t len);

private:
        I2C_HandleTypeDef i2cHandle;
};

/*****************************************************************************/

I2CLcdDataLink *I2CLcdDataLink::singleton ()
{
        static I2CLcdDataLink link;
        return &link;
}

/*****************************************************************************/

void I2CLcdDataLink::init ()
{
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
}

/*****************************************************************************/

void I2CLcdDataLink::send (uint8_t *data, uint8_t len)
{
#define ADDRESS_WRITE 0x70

        while (HAL_I2C_Master_Transmit (&i2cHandle, (uint8_t)ADDRESS_WRITE, (uint8_t *)data, len, 10000) != HAL_OK) {
                /* Error_Handler() function is called when Timeout error occurs.
                 When Acknowledge failure occurs (Slave don't acknowledge it's address)
                 Master restarts communication */
                if (HAL_I2C_GetError (&i2cHandle) != HAL_I2C_ERROR_AF) {
                        Error_Handler ();
                }
        }
}

/*****************************************************************************/

struct ILcdDriver {
        virtual ~ILcdDriver () {}

        /**
         * @brief init
         * @param bias 2 == 1/2, 3 == 1/3 etc
         * @param planesNumber 1 == static operation, 2 == 2 planes, 3 == 3 planes etc
         * @param on If turned on or not
         */
        virtual void init (uint8_t bias, uint8_t planesNumber, bool on) = 0;

        /**
         * @brief sendData Sends display data
         * @param address
         * @param data
         * @param len
         */
        virtual void sendData (uint8_t address, uint8_t *data, uint8_t len) = 0;
};

/*****************************************************************************/

#define NEXT_COMMAND 0x80

#define COMMAND_MODE_SET 0x40
#define DISPLAY_ON 0x08
#define DISPLAY_OF 0x00
#define BIAS_1_2 0x04
#define BIAS_1_3 0x00
#define PLANES_1 0x01
#define PLANES_2 0x02
#define PLANES_3 0x03
#define PLANES_4 0x00

class PCF85176Driver : public ILcdDriver {
public:
        virtual ~PCF85176Driver () {}
        static PCF85176Driver *singleton ();
        void init (uint8_t bias, uint8_t planesNumber, bool on);
        void sendData (uint8_t address, uint8_t *data, uint8_t len);
        void setDataLink (ILcdDataLink *l) { link = l; }

private:
        ILcdDataLink *link = nullptr;
};

PCF85176Driver *PCF85176Driver::singleton ()
{
        static PCF85176Driver driver;
        return &driver;
}

void PCF85176Driver::init (uint8_t bias, uint8_t planesNumber, bool on)
{
        uint8_t command = NEXT_COMMAND | COMMAND_MODE_SET;
        command |= ((bias == 2) ? (BIAS_1_2) : (BIAS_1_3));
        command |= ((on) ? (DISPLAY_ON) : (DISPLAY_OF));
        command |= PLANES_4; // TODO
        link->send (&command, 1);
}

void PCF85176Driver::sendData (uint8_t address, uint8_t *data, uint8_t len)
{
        uint8_t tmp[21];
        tmp[0] = address;
        memcpy (tmp + 1, data, len);
        link->send (tmp, len + 1);
}

/*****************************************************************************/

struct IDisplay {
        virtual ~IDisplay () {}
        virtual void setDigit (uint8_t number, uint8_t setDigit) = 0;
};

/**
 * @brief The T145003 class controlls a Chinese weight scale LCD which I found on AliExpress once.
 */
class T145003 : public IDisplay {
public:
        enum Dots { DOT5 = 0x01, DOT4 = 0x02, DOT3 = 0x04, DOT2 = 0x08 };
        enum Triangles { BOTTOM_LEFT = 0x01, TOP_LEFT = 0x02, TOP_RIGHT = 0x04, MINUS = 0x08 };
        enum Batery { FRAME = 0x01, BAR0 = 0x02, BAR1 = 0x04, BAR2 = 0x08, BAR3 = 0x10 };

        virtual ~T145003 () {}
        static T145003 *singleton ();

        /**
         * @brief digit Displays a digit
         * @param position 0-4. 0 means least significant digit, 4 means most.
         * @param digit A digit.
         */
        void setDigit (uint8_t position, uint8_t setDigit);
        void setDots (uint8_t bitmask);
        void setTriangles (uint8_t bitmask);

        /**
         * @brief batteryLevel 0 : blinking frame, 1 : frame, 2 : frame & 1 bar, 3 : frame & 2 bars
         * @param level
         */
        void setBatteryLevel (uint8_t level);

        void refresh ();

        void setLcdDriver (ILcdDriver *d) { driver = d; }
private:
        ILcdDriver *driver = nullptr;
        uint8_t buffer[6];
        uint8_t digits[5] = { 0, 0, 0, 0, 0 };
        uint8_t dots = 0;
        uint8_t triangles = 0;
        uint8_t batteryLevel = 0;
        bool needsRefresh = true;

        const uint8_t font[16] = {
                0x01 | 0x02 | 0x04 | 0x10 | 0x40 | 0x80,        // 0
                0x02 | 0x04,                                    // 1
                0x01 | 0x02 | 0x20 | 0x40 | 0x80,               // 2
                0x01 | 0x02 | 0x20 | 0x04 | 0x80,               // 3
                0x10 | 0x20 | 0x02 | 0x04,                      // 4
                0x01 | 0x10 | 0x20 | 0x04 | 0x80,               // 5
                0x01 | 0x10 | 0x20 | 0x04 | 0x40 | 0x80,        // 6
                0x01 | 0x02 | 0x04,                             // 7
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40 | 0x80, // 8
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x80,        // 9
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40,        // A
                0x04 | 0x10 | 0x20 | 0x40 | 0x80,               // b
                0x01 | 0x10 | 0x40 | 0x80,                      // C
                0x04 | 0x02 | 0x20 | 0x40 | 0x80,               // d
                0x01 | 0x10 | 0x20 | 0x40 | 0x80,               // E
                0x01 | 0x10 | 0x20 | 0x40                       // F
        };

        const uint8_t batteryFont[6] = {
                0x00,                            // Empty
                0x80,                            // Frame
                0x80 | 0x08,                     // Frame & 1 bar
                0x80 | 0x08 | 0x04,              // 2 bars
                0x80 | 0x08 | 0x04 | 0x02,       // 3 bars
                0x80 | 0x08 | 0x04 | 0x02 | 0x01 // all bars

        };
};

T145003 *T145003::singleton ()
{
        static T145003 lcd;
        return &lcd;
}

void T145003::setDigit (uint8_t position, uint8_t digit)
{
        digits[position] = digit;
        needsRefresh = true;
}

void T145003::setDots (uint8_t bitmask)
{
        dots = bitmask;
        needsRefresh = true;
}

void T145003::setTriangles (uint8_t bitmask)
{
        triangles = bitmask;
        needsRefresh = true;
}

void T145003::setBatteryLevel (uint8_t level)
{
        batteryLevel = level;
        needsRefresh = true;
}

void T145003::refresh ()
{
        if (!needsRefresh) {
                return;
        }

        needsRefresh = false;
        buffer[0] = batteryFont[batteryLevel];

        for (int i = 0; i < 5; ++i) {
                buffer[i + 1] = font[digits[i]];
        }

        if (dots & DOT5) {
                buffer[2] |= 0x08;
        }

        if (dots & DOT4) {
                buffer[3] |= 0x08;
        }

        if (dots & DOT3) {
                buffer[4] |= 0x08;
        }

        if (dots & DOT2) {
                buffer[5] |= 0x08;
        }

        /*---------------------------------------------------------------------------*/

        if (triangles & TOP_RIGHT) {
                buffer[0] |= 0x40;
        }

        if (triangles & MINUS) {
                buffer[0] |= 0x20;
        }

        if (triangles & TOP_LEFT) {
                buffer[0] = 0x10;
        }

        if (triangles & BOTTOM_LEFT) {
                buffer[1] |= 0x08;
        }

        driver->sendData (0, buffer, sizeof (buffer));
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
