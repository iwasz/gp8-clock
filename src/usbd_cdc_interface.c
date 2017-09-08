/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/usbd_cdc_interface.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    04-November-2016
  * @brief   Source file for USBD CDC interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_interface.h"
#include "ErrorHandler.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CDC
  * @brief usbd core module
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define APP_RX_DATA_SIZE 128
#define APP_TX_DATA_SIZE 2048

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USBD_CDC_LineCodingTypeDef LineCoding = {
        115200, /* baud rate*/
        0x00,   /* stop bits-1*/
        0x00,   /* parity - none*/
        0x08    /* nb. of bits 8*/
};

uint8_t usbTxBuffer[APP_TX_DATA_SIZE];
uint8_t usbRxBuffer[APP_RX_DATA_SIZE];

uint32_t usbTxBufPtrIn = 0;  /* Increment this pointer or roll it back to
                                 start address when data are received over USART */
uint32_t usbTxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over USB */

/* TIM handler declaration */
TIM_HandleTypeDef usbTimHandle;
/* USB handler declaration */
extern USBD_HandleTypeDef usbdDevice;

/* Private function prototypes -----------------------------------------------*/
static int8_t CDC_Itf_Init (void);
static int8_t CDC_Itf_DeInit (void);
static int8_t CDC_Itf_Control (uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Itf_Receive (uint8_t *pbuf, uint32_t *Len);

void Error_Handler (void);
// static void ComPort_Config (void);
static void TIM_Config (void);

USBD_CDC_ItfTypeDef USBD_CDC_fops = { CDC_Itf_Init, CDC_Itf_DeInit, CDC_Itf_Control, CDC_Itf_Receive };

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  CDC_Itf_Init
  *         Initializes the CDC media low layer
  * @param  None
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Init (void)
{
        TIM_Config ();

        /*##-4- Start the TIM Base generation in interrupt mode ####################*/
        /* Start Channel1 */
        if (HAL_TIM_Base_Start_IT (&usbTimHandle) != HAL_OK) {
                /* Starting Error */
                Error_Handler ();
        }

        /*##-5- Set Application Buffers ############################################*/
        USBD_CDC_SetTxBuffer (&usbdDevice, usbTxBuffer, 0);
        USBD_CDC_SetRxBuffer (&usbdDevice, usbRxBuffer);

        return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit (void)
{
        HAL_NVIC_DisableIRQ (TIMx_IRQn);
        return USBD_OK;
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control (uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
        switch (cmd) {
        case CDC_SET_LINE_CODING:
                break;

        case CDC_GET_LINE_CODING:
                pbuf[0] = (uint8_t) (LineCoding.bitrate);
                pbuf[1] = (uint8_t) (LineCoding.bitrate >> 8);
                pbuf[2] = (uint8_t) (LineCoding.bitrate >> 16);
                pbuf[3] = (uint8_t) (LineCoding.bitrate >> 24);
                pbuf[4] = LineCoding.format;
                pbuf[5] = LineCoding.paritytype;
                pbuf[6] = LineCoding.datatype;
                break;

        default:
                break;
        }

        return (USBD_OK);
}

/**
  * @brief  TIM period elapsed callback
  * @param  htim: TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
        uint32_t buffptr;
        uint32_t buffsize;

        if (usbTxBufPtrOut != usbTxBufPtrIn) {
                if (usbTxBufPtrOut > usbTxBufPtrIn) /* rollback */
                {
                        buffsize = APP_TX_DATA_SIZE - usbTxBufPtrOut;
                }
                else {
                        buffsize = usbTxBufPtrIn - usbTxBufPtrOut;
                }

                buffptr = usbTxBufPtrOut;

                USBD_CDC_SetTxBuffer (&usbdDevice, (uint8_t *)&usbTxBuffer[buffptr], buffsize);

                if (USBD_CDC_TransmitPacket (&usbdDevice) == USBD_OK) {
                        usbTxBufPtrOut += buffsize;
                        if (usbTxBufPtrOut >= APP_TX_DATA_SIZE) {
                                usbTxBufPtrOut = 0;
                        }
                }
        }
}

/**
 * @brief usbWrite
 * @param buf
 * @param len
 */
void usbWrite (const char *buf, size_t len)
{
        if (usbTxBufPtrIn + len <= APP_TX_DATA_SIZE) {
                strncpy ((char *)(usbTxBuffer + usbTxBufPtrIn), buf, len);
                usbTxBufPtrIn += len;
        }
        else {
                size_t head = usbTxBufPtrIn + len - APP_TX_DATA_SIZE ;
                size_t tail = len - head;

                strncpy ((char *)(usbTxBuffer + usbTxBufPtrIn), buf, tail);
                strncpy ((char *)(usbTxBuffer), buf + tail, head);
                usbTxBufPtrIn = head;
        }
}

///**
//  * @brief  Rx Transfer completed callback
//  * @param  huart: UART handle
//  * @retval None
//  */
// void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
//{
//        /* Increment Index for buffer writing */
//        UserTxBufPtrIn++;

//        /* To avoid buffer overflow */
//        if (UserTxBufPtrIn == APP_RX_DATA_SIZE) {
//                UserTxBufPtrIn = 0;
//        }

//        /* Start another reception: provide the buffer pointer with offset and the buffer size */
//        HAL_UART_Receive_IT (huart, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
//}

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the opeartion: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Receive (uint8_t *Buf, uint32_t *Len) { return (USBD_OK); }

/**
  * @brief  Tx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
// void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart)
//{
//        /* Initiate next USB packet transfer once UART completes transfer (transmitting data over Tx line) */
//        USBD_CDC_ReceivePacket (&USBD_Device);
//}

/**
  * @brief  TIM_Config: Configure TIMx timer
  * @param  None.
  * @retval None.
  */
static void TIM_Config (void)
{
        /* Set TIMx instance */
        usbTimHandle.Instance = TIMx;

        /* Initialize TIM3 peripheral as follow:
             + Period = 10000 - 1
             + Prescaler = ((SystemCoreClock/2)/10000) - 1
             + ClockDivision = 0
             + Counter direction = Up
        */
        usbTimHandle.Init.Period = (CDC_POLLING_INTERVAL * 1000) - 1;
        usbTimHandle.Init.Prescaler = 84 - 1;
        usbTimHandle.Init.ClockDivision = 0;
        usbTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
        usbTimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

        TIMx_CLK_ENABLE ();
        HAL_NVIC_SetPriority (TIMx_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ (TIMx_IRQn);

        if (HAL_TIM_Base_Init (&usbTimHandle) != HAL_OK) {
                /* Initialization Error */
                Error_Handler ();
        }
}

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @retval None
  */
void HAL_UART_ErrorCallback (UART_HandleTypeDef *UartHandle)
{
        /* Transfer error occured in reception and/or transmission process */
        Error_Handler ();
}
