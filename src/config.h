/*
 * config.h
 *
 *  Created on: Mar 18, 2015
 *      Author: iwasz
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

extern void Error_Handler (void);

/*---------------------------------------------------------------------------*/
/* USART GSM                                                                 */
/*---------------------------------------------------------------------------*/

#define GPS_USART                           USART2
#define GPS_USART_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                   __HAL_RCC_DMA1_CLK_ENABLE()
#define GPS_USART_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define GPS_USART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define GPS_USART_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define GPS_USART_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for GPS_USART Pins */
#define GPS_USART_TX_PIN                    GPIO_PIN_2
#define GPS_USART_TX_GPIO_PORT              GPIOA
#define GPS_USART_TX_AF                     GPIO_AF7_USART2
#define GPS_USART_RX_PIN                    GPIO_PIN_3
#define GPS_USART_RX_GPIO_PORT              GPIOA
#define GPS_USART_RX_AF                     GPIO_AF7_USART2

/* Definition for GPS_USART's NVIC: used for receiving data over Rx pin */
#define GPS_USART_IRQn                      USART2_IRQn
#define GPS_USART_IRQHandler                USART2_IRQHandler

/* Definition for GPS_USART's DMA: used for transmitting data over Tx pin */
#define GPS_USART_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define GPS_USART_TX_DMA_STREAM             DMA1_Stream6
#define GPS_USART_DMA_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define GPS_USART_DMA_TX_IRQn               DMA1_Stream6_IRQn

//#define GPS_RX_DATA_SIZE  512
//#define GPS_TX_DATA_SIZE  512

/*---------------------------------------------------------------------------*/
/* STN 1110 USART                                                            */
/*---------------------------------------------------------------------------*/

#define OBD_USART                           USART3
#define OBD_USART_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
//#define OBD_USART_DMA_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()
#define OBD_USART_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define OBD_USART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define OBD_USART_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define OBD_USART_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for OBD_USART Pins */
#define OBD_USART_TX_PIN                    GPIO_PIN_10
#define OBD_USART_TX_GPIO_PORT              GPIOB
#define OBD_USART_TX_AF                     GPIO_AF7_USART3
#define OBD_USART_RX_PIN                    GPIO_PIN_11
#define OBD_USART_RX_GPIO_PORT              GPIOB
#define OBD_USART_RX_AF                     GPIO_AF7_USART3

/* Definition for OBD_USART's NVIC: used for receiving data over Rx pin */
#define OBD_USART_IRQn                      USART3_IRQn
#define OBD_USART_IRQHandler                USART3_IRQHandler

/* Definition for OBD_USART's DMA: used for transmitting data over Tx pin */
//#define OBD_USART_TX_DMA_CHANNEL            DMA_CHANNEL_4
//#define OBD_USART_TX_DMA_STREAM             DMA2_Stream7
//#define OBD_USART_DMA_TX_IRQHandler         DMA2_Stream7_IRQHandler
//#define OBD_USART_DMA_TX_IRQn               DMA2_Stream7_IRQn

#define OBD_RX_DATA_SIZE  512
#define OBD_TX_DATA_SIZE  512


#define OBD_RESET_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define OBD_RESET_PIN GPIO_PIN_6
#define OBD_RESET_PORT GPIOC
/*---------------------------------------------------------------------------*/
/* Power GSM & power sensing                                                 */
/*---------------------------------------------------------------------------*/

#define SIM908_STATUS_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SIM908_STATUS_PIN                    GPIO_PIN_0
#define SIM908_STATUS_GPIO_PORT              GPIOA

#define SIM908_PWRKEY_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SIM908_PWRKEY_PIN                    GPIO_PIN_1
#define SIM908_PWRKEY_GPIO_PORT              GPIOA

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

// RDYN - ready pin PC4
#define __HAL_RCC_ACI_RDYN_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define GPIO_PIN_ACI_RDYN GPIO_PIN_4
#define GPIO_ACI_RDYN GPIOC
#define EXTI_ACI_RDYN_IRQn EXTI4_IRQn

// RESET - reset pin PC5
#define __HAL_RCC_ACI_RESET_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define GPIO_PIN_ACI_RESET GPIO_PIN_5
#define GPIO_ACI_RESET GPIOC

// REQN - chip select pin PA4
#define __HAL_RCC_ACI_REQN_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE
#define GPIO_PIN_ACI_REQN GPIO_PIN_4
#define GPIO_ACI_REQN GPIOA

#define SPIx                             SPI1
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_AF                      GPIO_AF5_SPI1
#define SPIx_MISO_PIN                    GPIO_PIN_6
#define SPIx_MISO_GPIO_PORT              GPIOA
#define SPIx_MISO_AF                     GPIO_AF5_SPI1
#define SPIx_MOSI_PIN                    GPIO_PIN_7
#define SPIx_MOSI_GPIO_PORT              GPIOA
#define SPIx_MOSI_AF                     GPIO_AF5_SPI1

/*---------------------------------------------------------------------------*/
/* Diody do debugu                                                           */
/*---------------------------------------------------------------------------*/

// D2 PB7
#define __HAL_RCC_LED_D2_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_LED_D2 GPIO_PIN_7
#define GPIO_LED_D2 GPIOB

// D3 PB6
#define __HAL_RCC_LED_D3_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_LED_D3 GPIO_PIN_6
#define GPIO_LED_D3 GPIOB

// D4 PB5
#define __HAL_RCC_LED_D4_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_LED_D4 GPIO_PIN_5
#define GPIO_LED_D4 GPIOB

// D5 PB4
#define __HAL_RCC_LED_D5_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#define GPIO_PIN_LED_D5 GPIO_PIN_4
#define GPIO_LED_D5 GPIOB

#endif /* SRC_CONFIG_H_ */
