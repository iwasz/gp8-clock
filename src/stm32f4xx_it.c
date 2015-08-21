/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"
#include "config.h"
#include "sim908_gsm.h"
#include "config.h"
#include "obd/usartCommunication.h"
#include "obd/logic.h"
#include <stdio.h>

#include "obd/stn1110ResponseParser.h"
extern ObdData obdData;
extern PCD_HandleTypeDef hpcd;

/* UART handler declared in "usbd_cdc_interface.c" file */
extern UART_HandleTypeDef UartHandle;

/* TIM handler declared in "usbd_cdc_interface.c" file */
extern TIM_HandleTypeDef TimHandle;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler (void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler (void)
{
        /* Go to infinite loop when Hard Fault exception occurs */
        while (1) {
        }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler (void)
{
        /* Go to infinite loop when Memory Manage exception occurs */
        while (1) {
        }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler (void)
{
        /* Go to infinite loop when Bus Fault exception occurs */
        while (1) {
        }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler (void)
{
        /* Go to infinite loop when Usage Fault exception occurs */
        while (1) {
        }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler (void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler (void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler (void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler (void)
{
        HAL_IncTick ();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
 * @brief  This function handles USB-On-The-Go FS global interrupt request.
 * @param  None
 * @retval None
 */
#ifdef USE_USB_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler (void)
#endif
{
        HAL_PCD_IRQHandler (&hpcd);
}

/**
 * @brief  This function handles DMA interrupt request.
 * @param  None
 * @retval None
 */
void GPS_USART_DMA_TX_IRQHandler (void)
{
        HAL_DMA_IRQHandler (gpsUartHandle.hdmatx);
}

/**
 * @brief  This function handles UART interrupt request.
 * @param  None
 * @retval None
 */
void GPS_USART_IRQHandler (void)
{
        HAL_UART_IRQHandler (&gpsUartHandle);


//        cdcItfTransmit (".", 1);
//
//        // Byte t
//        if (gpsUartHandle.Instance->SR & USART_FLAG_TXE) {
//                cdcItfTransmit ("t", 1);
//        }
//
//        // Transmission completed?
//        if (gpsUartHandle.Instance->SR & USART_FLAG_TC) {
//                cdcItfTransmit ("c", 1);
//        }
//
//        // Byte received
//        if (gpsUartHandle.Instance->SR & USART_FLAG_RXNE) {
//                cdcItfTransmit ("r", 1);
////                        char c = gpsUartHandle.Instance->DR & 0xff;
////                        cdcItfTransmit (&c, 1);
//        }
//
//        // Idle detected
//        if (gpsUartHandle.Instance->SR & USART_FLAG_IDLE) {
//                cdcItfTransmit ("i", 1);
//        }
//
//        // Overrun error
//        if (gpsUartHandle.Instance->SR & USART_FLAG_ORE) {
//                cdcItfTransmit ("o", 1);
//        }
//
//        // Noise error
//        if (gpsUartHandle.Instance->SR & USART_FLAG_NE) {
//                cdcItfTransmit ("n", 1);
//        }
//
//        // Framing error
//        if (gpsUartHandle.Instance->SR & USART_FLAG_FE) {
//                cdcItfTransmit ("f", 1);
//        }
//
//        // Parity error
//        if (gpsUartHandle.Instance->SR & USART_FLAG_PE) {
//                cdcItfTransmit ("p", 1);
//        }
}

#include "squeue.h"
extern uint8_t rxBuffer[SQUEUE_BUFFER_SIZE];
extern uint16_t rxBufferPosObd;

void OBD_USART_IRQHandler ()
{
#if 0
//        1.
//        HAL_UART_IRQHandler (&obdUartHandle);
#endif

#if 0
//        2.
        if (obdUartHandle.Instance->SR & USART_FLAG_ORE) {
                cdcItfTransmit ("!", 1);
        }

        uint8_t c = (uint8_t)(obdUartHandle.Instance->DR & (uint8_t)0x00FF);
        cdcItfTransmit (&c, 1);
        cdcItfTransmit ("\n", 1);
#endif

//        3.
#if 1
        if (obdUartHandle.Instance->SR & USART_FLAG_ORE) {
//                cdcItfTransmit ("!", 1);
        }

        rxBuffer[rxBufferPosObd] = (uint8_t)(obdUartHandle.Instance->DR & (uint8_t)0x00FF);

        if (rxBufferPosObd >= 1 &&
            rxBuffer[rxBufferPosObd] == '\r') {

                rxBuffer[rxBufferPosObd] = '\0';

                // Nie wrzucamy na kolejkę odpowiedzi, które zawierają tylko \r\n
                if (rxBufferPosObd > 1) {
                        printf ("{%s}\n", rxBuffer);
                        // Nie powino być żadnych znaków powyżej 127
//                                stateMachineRun ((char *)rxBuffer);
                        obdDataParse ((const char *)rxBuffer, &obdData);
                }

                rxBufferPosObd = 0;
        }
        else {
                ++rxBufferPosObd;

                if (rxBufferPosObd >= SQUEUE_BUFFER_SIZE) {
                        printf ("[GSM] UART buffer full, rolling back.");
                        rxBufferPosObd = 0;
                }
        }
#endif
}

/**
 * @brief  This function handles TIM interrupt request.
 * @param  None
 * @retval None
 */
void TIM3_IRQHandler (void)
{
        HAL_TIM_IRQHandler (&TimHandle);
}

// Procedura obsługi. Miedzy innymi dla BLE sygnał RDYN - ale teraz chyba wyłącznie.
void EXTI4_IRQHandler (void)
{
    HAL_GPIO_EXTI_IRQHandler (GPIO_PIN_ACI_RDYN);
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
