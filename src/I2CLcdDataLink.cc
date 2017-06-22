/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "I2CLcdDataLink.h"
#include "ErrorHandler.h"
#include <stm32f0xx_hal.h>

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
