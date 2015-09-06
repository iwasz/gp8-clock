#if 0
/**
 ******************************************************************************
 * @file    USB_Device/CDC_Standalone/Src/usbd_cdc_interface.c
 * @author  MCD Application Team
 * @version V1.2.0
 * @date    26-December-2014
 * @brief   Source file for USBD CDC interface
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

#include "stm32f4xx_hal.h"
#include "usbd_cdc_interface.h"
#include "config.h"
#include <string.h>

USBD_CDC_LineCodingTypeDef LineCoding = {
        115200, /* baud rate */
        0x00,   /* stop bits-1 */
        0x00,   /* parity - none */
        0x08    /* nb. of bits 8 */
};

//uint8_t UserRxBuffer[CDC_RX_DATA_SIZE]; // Received Data over USB are stored in this buffer
uint8_t txBuffer[CDC_TX_DATA_SIZE]; // Data to be sent by the USB-CDC.

uint16_t offsetIn = 0;  // Increment this pointer (or roll it back to start address) when data are received over USART.
uint16_t offsetOut = 0; // Increment this pointer (or roll it back to start address) when data are sent over USB.

/* TIM handler declaration */
TIM_HandleTypeDef usbTimHandle;
/* USB handler declaration */
extern USBD_HandleTypeDef USBD_Device;

/* Private function prototypes -----------------------------------------------*/
static int8_t CDC_Itf_Init (void);
static int8_t CDC_Itf_DeInit (void);
static int8_t CDC_Itf_Control (uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Itf_Receive (uint8_t *pbuf, uint32_t *Len);
static void ComPort_Config (void);
static void TIM_Config (void);

USBD_CDC_ItfTypeDef USBD_CDC_fops = { CDC_Itf_Init, CDC_Itf_DeInit, CDC_Itf_Control, CDC_Itf_Receive };

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the CDC media low layer
 * @param  None
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Itf_Init (void)
{
        TIM_Config ();
        USBD_CDC_SetTxBuffer (&USBD_Device, txBuffer, 0);
        USBD_CDC_SetRxBuffer (&USBD_Device, NULL);
        return (USBD_OK);
}

/**
 * @brief  CDC_Itf_DeInit
 *         DeInitializes the CDC media low layer
 * @param  None
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Itf_DeInit (void)
{
        /* DeInitialize the UART peripheral */
        //        if (HAL_UART_DeInit (&UartHandle) != HAL_OK) {
        //                /* Initialization Error */
        //                Error_Handler ();
        //        }
        return (USBD_OK);
}

/**
 * @brief  CDC_Itf_Control
 *         Manage the CDC class requests
 * @param  Cmd: Command code
 * @param  Buf: Buffer containing command data (request parameters)
 * @param  Len: Number of data to be sent (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Itf_Control (uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
        switch (cmd) {
        case CDC_SEND_ENCAPSULATED_COMMAND:
                /* Add your code here */
                break;

        case CDC_GET_ENCAPSULATED_RESPONSE:
                /* Add your code here */
                break;

        case CDC_SET_COMM_FEATURE:
                /* Add your code here */
                break;

        case CDC_GET_COMM_FEATURE:
                /* Add your code here */
                break;

        case CDC_CLEAR_COMM_FEATURE:
                /* Add your code here */
                break;

        case CDC_SET_LINE_CODING:
                LineCoding.bitrate = (uint32_t)(pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24));
                LineCoding.format = pbuf[4];
                LineCoding.paritytype = pbuf[5];
                LineCoding.datatype = pbuf[6];

                /* Set the new configuration */
                ComPort_Config ();
                break;

        case CDC_GET_LINE_CODING:
                pbuf[0] = (uint8_t)(LineCoding.bitrate);
                pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
                pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
                pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
                pbuf[4] = LineCoding.format;
                pbuf[5] = LineCoding.paritytype;
                pbuf[6] = LineCoding.datatype;
                break;

        case CDC_SET_CONTROL_LINE_STATE:
                /* Add your code here */
                break;

        case CDC_SEND_BREAK:
                /* Add your code here */
                break;

        default:
                break;
        }

        return (USBD_OK);
}

/**
 * Procedura (no taki callback wołany z procedury ISR) obsługi przerwania zgłaszanego
 * przez timer. To się wykonuje 100 lub 200 razy na sek i wysyła bufory przez USB-CDC
 * i opróżnia je.
 */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
        __disable_irq ();
        //        uint8_t *buf = squeueGetFirstFull (&squeue);
        //
        //        if (buf) {
        //                squeuePopFront (&squeue);
        //                printf ("[%s]\n", buf);
        //        }

        uint16_t len;
        uint16_t offsetInCopy = offsetIn;
        __enable_irq ();

        if (offsetOut < offsetInCopy) {
                len = offsetInCopy - offsetOut;

                /*
                 * Ustawia wewnętrzny bufor :
                 *   USBD_Device->pClassData->TxBuffer = UserTxBuffer + UserTxBufPtrOut
                 * i jego długość :
                 *   USBD_Device->pClassData->TxLength = buffsize
                 */
                USBD_CDC_SetTxBuffer (&USBD_Device, txBuffer + offsetOut, len);

                // Wysyła z wewnętrznego bufora USBD_Device->pClassData->TxBuffer paczkę danych o długości USBD_Device->pClassData->TxLength
                if (USBD_CDC_TransmitPacket (&USBD_Device) == USBD_OK) {
                        offsetOut = (offsetOut + len) % CDC_RX_DATA_SIZE;
                }
        }
        else if (offsetOut > offsetInCopy) {
                len = CDC_RX_DATA_SIZE - offsetOut;
                USBD_CDC_SetTxBuffer (&USBD_Device, txBuffer + offsetOut, len);

                if (USBD_CDC_TransmitPacket (&USBD_Device) == USBD_OK) {
                        offsetOut = 0;
                }

                len = offsetInCopy - offsetOut;
                USBD_CDC_SetTxBuffer (&USBD_Device, txBuffer, len);

                if (USBD_CDC_TransmitPacket (&USBD_Device) == USBD_OK) {
                        offsetOut = (offsetOut + len) % CDC_RX_DATA_SIZE;
                }
        }
}

void cdcItfTransmit (uint8_t *buf, size_t len)
{
        if (len > CDC_RX_DATA_SIZE) {
                Error_Handler ();
        }

        if (offsetIn + len < CDC_RX_DATA_SIZE) {
                memcpy (txBuffer + offsetIn, buf, len);
                offsetIn += len;
        }
        else {
                // Kopiuj od offsetIn do końca bufora a następnie.
                size_t tempLen = CDC_RX_DATA_SIZE - offsetIn;
                memcpy (txBuffer + offsetIn, buf, tempLen);

                offsetIn = 0;
                memcpy (txBuffer + offsetIn, buf + tempLen, len - tempLen);
                offsetIn += len - tempLen;
        }
}

/**
 * @brief  CDC_Itf_DataRx
 *         Data received over USB OUT endpoint are sent over CDC interface
 *         through this function.
 * @param  Buf: Buffer of data to be transmitted
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CDC_Itf_Receive (uint8_t *Buf, uint32_t *Len)
{
        //        HAL_UART_Transmit_DMA (&UartHandle, Buf, *Len);
        return (USBD_OK);
}

/**
 * @brief  ComPort_Config
 *         Configure the COM Port with the parameters received from host.
 * @param  None.
 * @retval None
 * @note   When a configuration is not supported, a default value is used.
 */
static void ComPort_Config (void)
{
        //        if (HAL_UART_DeInit (&UartHandle) != HAL_OK) {
        //                /* Initialization Error */
        //                Error_Handler ();
        //        }
        //
        //        /* set the Stop bit */
        //        switch (LineCoding.format) {
        //        case 0:
        //                UartHandle.Init.StopBits = UART_STOPBITS_1;
        //                break;
        //        case 2:
        //                UartHandle.Init.StopBits = UART_STOPBITS_2;
        //                break;
        //        default:
        //                UartHandle.Init.StopBits = UART_STOPBITS_1;
        //                break;
        //        }
        //
        //        /* set the parity bit*/
        //        switch (LineCoding.paritytype) {
        //        case 0:
        //                UartHandle.Init.Parity = UART_PARITY_NONE;
        //                break;
        //        case 1:
        //                UartHandle.Init.Parity = UART_PARITY_ODD;
        //                break;
        //        case 2:
        //                UartHandle.Init.Parity = UART_PARITY_EVEN;
        //                break;
        //        default:
        //                UartHandle.Init.Parity = UART_PARITY_NONE;
        //                break;
        //        }
        //
        //        /*set the data type : only 8bits and 9bits is supported */
        //        switch (LineCoding.datatype) {
        //        case 0x07:
        //                /* With this configuration a parity (Even or Odd) must be set */
        //                UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        //                break;
        //        case 0x08:
        //                if (UartHandle.Init.Parity == UART_PARITY_NONE) {
        //                        UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        //                }
        //                else {
        //                        UartHandle.Init.WordLength = UART_WORDLENGTH_9B;
        //                }
        //
        //                break;
        //        default:
        //                UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
        //                break;
        //        }
        //
        //        UartHandle.Init.BaudRate = LineCoding.bitrate;
        //        UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        //        UartHandle.Init.Mode = UART_MODE_TX_RX;
        //        UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
        //
        //        if (HAL_UART_Init (&UartHandle) != HAL_OK) {
        //                /* Initialization Error */
        //                Error_Handler ();
        //        }
        //
        //        /* Start reception: provide the buffer pointer with offset and the buffer size */
        //        HAL_UART_Receive_IT (&UartHandle, (uint8_t *) (UserTxBuffer + UserTxBufPtrIn), 1);
}

/**
 * @brief  TIM_Config: Configure TIM_CDC timer
 * @param  None.
 * @retval None
 */
static void TIM_Config (void)
{
        /* Set TIM_CDC instance */
        usbTimHandle.Instance = TIM_CDC;

        /* Initialize TIM3 peripheral as follows:
         + Period = (CDC_POLLING_INTERVAL * 10000) - 1
         + Prescaler = ((APB1 frequency / 1000000) - 1)
         + ClockDivision = 0
         + Counter direction = Up  */
        usbTimHandle.Init.Period = (CDC_POLLING_INTERVAL * 1000) - 1;
        usbTimHandle.Init.Prescaler = 84 - 1;
        usbTimHandle.Init.ClockDivision = 0;
        usbTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;

        if (HAL_TIM_Base_Init (&usbTimHandle) != HAL_OK) {
                /* Initialization Error */
                Error_Handler ();
        }

        /* TIM_CDC Peripheral clock enable */
        TIM_CDC_CLK_ENABLE ();

        /*##-2- Configure the NVIC for TIM_CDC ########################################*/
        /* Set the TIM_CDC priority */
        HAL_NVIC_SetPriority (TIM_CDC_IRQn, 6, 1);

        /* Enable the TIM_CDC global Interrupt */
        HAL_NVIC_EnableIRQ (TIM_CDC_IRQn);

        if (HAL_TIM_Base_Start_IT (&usbTimHandle) != HAL_OK) {
                Error_Handler ();
        }
}
#endif
