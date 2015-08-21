/*
 * config.h
 *
 *  Created on: Mar 18, 2015
 *      Author: iwasz
 *
 *      Do tego co było na pierwszym prototypie na breadbordzie i płytkach.
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

extern void Error_Handler (void);

/*---------------------------------------------------------------------------*/
/* USART GSM                                                                 */
/*---------------------------------------------------------------------------*/

#define GPS_USART                           USART1
#define GPS_USART_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                   __HAL_RCC_DMA2_CLK_ENABLE()
#define GPS_USART_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define GPS_USART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define GPS_USART_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define GPS_USART_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for GPS_USART Pins */
#define GPS_USART_TX_PIN                    GPIO_PIN_6
#define GPS_USART_TX_GPIO_PORT              GPIOB
#define GPS_USART_TX_AF                     GPIO_AF7_USART1
#define GPS_USART_RX_PIN                    GPIO_PIN_7
#define GPS_USART_RX_GPIO_PORT              GPIOB
#define GPS_USART_RX_AF                     GPIO_AF7_USART1

/* Definition for GPS_USART's NVIC: used for receiving data over Rx pin */
#define GPS_USART_IRQn                      USART1_IRQn
#define GPS_USART_IRQHandler                USART1_IRQHandler

/* Definition for GPS_USART's DMA: used for transmitting data over Tx pin */
#define GPS_USART_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define GPS_USART_TX_DMA_STREAM             DMA2_Stream7
#define GPS_USART_DMA_TX_IRQHandler         DMA2_Stream7_IRQHandler
#define GPS_USART_DMA_TX_IRQn               DMA2_Stream7_IRQn

#define GPS_RX_DATA_SIZE  512
#define GPS_TX_DATA_SIZE  512

/*---------------------------------------------------------------------------*/
/* STN 1110 USART                                                            */
/*---------------------------------------------------------------------------*/

#define OBD_USART                           USART2
#define OBD_USART_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
//#define OBD_USART_DMA_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()
#define OBD_USART_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define OBD_USART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define OBD_USART_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define OBD_USART_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for OBD_USART Pins */
#define OBD_USART_TX_PIN                    GPIO_PIN_2
#define OBD_USART_TX_GPIO_PORT              GPIOA
#define OBD_USART_TX_AF                     GPIO_AF7_USART2
#define OBD_USART_RX_PIN                    GPIO_PIN_3
#define OBD_USART_RX_GPIO_PORT              GPIOA
#define OBD_USART_RX_AF                     GPIO_AF7_USART2

/* Definition for OBD_USART's NVIC: used for receiving data over Rx pin */
#define OBD_USART_IRQn                      USART2_IRQn
#define OBD_USART_IRQHandler                USART2_IRQHandler

/* Definition for OBD_USART's DMA: used for transmitting data over Tx pin */
//#define OBD_USART_TX_DMA_CHANNEL            DMA_CHANNEL_4
//#define OBD_USART_TX_DMA_STREAM             DMA2_Stream7
//#define OBD_USART_DMA_TX_IRQHandler         DMA2_Stream7_IRQHandler
//#define OBD_USART_DMA_TX_IRQn               DMA2_Stream7_IRQn

#define OBD_RX_DATA_SIZE  512
#define OBD_TX_DATA_SIZE  512

/*---------------------------------------------------------------------------*/
/* Power GSM & power sensing                                                 */
/*---------------------------------------------------------------------------*/

#define SIM908_STATUS_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()
#define SIM908_STATUS_PIN                    GPIO_PIN_4
#define SIM908_STATUS_GPIO_PORT              GPIOE

#define SIM908_PWRKEY_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()
#define SIM908_PWRKEY_PIN                    GPIO_PIN_5
#define SIM908_PWRKEY_GPIO_PORT              GPIOE

/*---------------------------------------------------------------------------*/
/* CDC ACM STUFF                                                             */
/*---------------------------------------------------------------------------*/

/* Definition for TIM_CDC clock resources */
#define TIM_CDC                             TIM3
#define TIM_CDC_CLK_ENABLE                  __HAL_RCC_TIM3_CLK_ENABLE
#define TIM_CDC_FORCE_RESET()               __HAL_RCC_USART3_FORCE_RESET()
#define TIM_CDC_RELEASE_RESET()             __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for TIM_CDC's NVIC */
#define TIM_CDC_IRQn                        TIM3_IRQn
#define TIM_CDC_IRQHandler                  TIM3_IRQHandler

#define CDC_RX_DATA_SIZE  1024
#define CDC_TX_DATA_SIZE  1024

/*---------------------------------------------------------------------------*/
/* NRF8001                                                                   */
/*---------------------------------------------------------------------------*/

// RDYN - ready pin
#define __HAL_RCC_ACI_RDYN_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_ACI_RDYN GPIO_PIN_12
#define GPIO_ACI_RDYN GPIOB
#define EXTI_ACI_RDYN_IRQn EXTI15_10_IRQn

// RESET - reset pin
#define __HAL_RCC_ACI_RESET_CLK_ENABLE __HAL_RCC_GPIOE_CLK_ENABLE
#define GPIO_PIN_ACI_RESET GPIO_PIN_15
#define GPIO_ACI_RESET GPIOE

// REQN - chip select pin
#define __HAL_RCC_ACI_REQN_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_ACI_REQN GPIO_PIN_11
#define GPIO_ACI_REQN GPIOB

#define SPIx                             SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_13
#define SPIx_SCK_GPIO_PORT               GPIOB
#define SPIx_SCK_AF                      GPIO_AF5_SPI2
#define SPIx_MISO_PIN                    GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                    GPIO_PIN_15
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_AF                     GPIO_AF5_SPI2

#endif /* SRC_CONFIG_H_ */
