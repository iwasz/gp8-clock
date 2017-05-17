#include "Debug.h"
#include "config.h"
#include <cstring>

Debug *Debug::singleton ()
{
        static Debug instance;
        return &instance;
}

/*****************************************************************************/

void Debug::init (uint32_t speed)
{
        __HAL_RCC_GPIOA_CLK_ENABLE ();
        GPIO_InitTypeDef gpioInitStruct;
        gpioInitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        gpioInitStruct.Mode = GPIO_MODE_AF_PP;
        gpioInitStruct.Pull = GPIO_PULLUP;
        gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpioInitStruct.Alternate = GPIO_AF1_USART1;
        HAL_GPIO_Init (GPIOA, &gpioInitStruct);

        __HAL_RCC_USART1_CLK_ENABLE ();
        huart.Instance = USART1;
        huart.Init.BaudRate = speed;
        huart.Init.WordLength = UART_WORDLENGTH_8B;
        huart.Init.StopBits = UART_STOPBITS_1;
        huart.Init.Parity = UART_PARITY_NONE;
        huart.Init.Mode = UART_MODE_TX_RX;
        huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart.Init.OverSampling = UART_OVERSAMPLING_16;
        huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

        if (HAL_UART_Init (&huart) != HAL_OK) {
                Error_Handler ();
        }

        //        HAL_NVIC_SetPriority (USART1_IRQn, 1, 0);
        //        HAL_NVIC_EnableIRQ (USART1_IRQn);

        //        if (HAL_UART_Receive_IT (&huart, (uint8_t *)rxBufferObd, 1) != HAL_OK) {
        //                /* Transfer error in reception process */
        //                Error_Handler ();
        //        }

        //        /* Enable the UART Parity Error Interrupt */
        //        __HAL_UART_ENABLE_IT (&huart, UART_IT_PE);

        //        /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
        //        __HAL_UART_ENABLE_IT (&huart, UART_IT_ERR);

        //        /* Enable the UART Data Register not empty Interrupt */
        //        __HAL_UART_ENABLE_IT (&huart, UART_IT_RXNE);
}

/*****************************************************************************/

void Debug::print (const char *str)
{
        // TODO DMA
        HAL_UART_Transmit (&huart, (uint8_t *)str, strlen (str), 5000);
}

/*****************************************************************************/

void Debug::print (uint8_t *data, size_t len)
{
        // TODO DMA
        HAL_UART_Transmit (&huart, data, len, 5000);
}

/* reverse:  reverse string s in place */
static void reverse (char s[])
{
        int i, j;
        char c;

        for (i = 0, j = strlen (s) - 1; i < j; i++, j--) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}

/* itoa:  convert n to characters in s */
void itoa (int n, char s[])
{
        int i, sign;

        if ((sign = n) < 0) /* record sign */
                n = -n;     /* make n positive */
        i = 0;
        do {                           /* generate digits in reverse order */
                s[i++] = n % 10 + '0'; /* get next digit */
        } while ((n /= 10) > 0);       /* delete it */
        if (sign < 0) s[i++] = '-';
        s[i] = '\0';
        reverse (s);
}

void Debug::print (int i)
{
        char buf[11];
        itoa (i, buf);
        print (buf);
}
