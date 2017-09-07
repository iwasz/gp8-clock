#include "usbd_cdc_interface.h"
#include <stm32f0xx_hal.h>
#include <usbd_def.h>

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

extern PCD_HandleTypeDef hpcd;
extern USBD_HandleTypeDef usbdDevice;
/* TIM handler declared in "usbd_cdc_interface.c" file */
extern TIM_HandleTypeDef usbTimHandle;

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler (void) {}

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
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler (void) {}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler (void) {}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler (void) { HAL_IncTick (); }

/**
  * @brief  This function handles USB Handler.
  * @param  None
  * @retval None
  */
void USB_IRQHandler (void) { HAL_PCD_IRQHandler (&hpcd); }

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIMx_IRQHandler (void) { HAL_TIM_IRQHandler (&usbTimHandle); }
