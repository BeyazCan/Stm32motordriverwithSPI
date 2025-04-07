#ifndef __STM32F4XX_HAL_SPI_H
#define __STM32F4XX_HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_Exported_Types SPI Exported Types
  * @{
  */

/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
  uint32_t Mode;                   /*!< Specifies the SPI operating mode.
                                       This parameter can be a value of @ref SPI_mode */

  uint32_t Direction;              /*!< Specifies the data transmission direction.
                                       This parameter can be a value of @ref SPI_data_direction */

  uint32_t DataSize;               /*!< Specifies the data size for SPI communication.
                                       This parameter can be a value of @ref SPI_data_size */

  uint32_t CLKPolarity;            /*!< Specifies the clock polarity.
                                       This parameter can be a value of @ref SPI_Clock_Polarity */

  uint32_t CLKPhase;               /*!< Specifies the clock phase.
                                       This parameter can be a value of @ref SPI_Clock_Phase */

  uint32_t NSS;                    /*!< Specifies whether the NSS signal is used in software or hardware.
                                       This parameter can be a value of @ref SPI_NSS */

  uint32_t BaudRatePrescaler;      /*!< Specifies the Baud rate prescaler.
                                       This parameter can be a value of @ref SPI_BaudRate_Prescaler */

  uint32_t FirstBit;               /*!< Specifies whether the data is transmitted/received with the MSB or LSB first.
                                       This parameter can be a value of @ref SPI_First_Bit */

  uint32_t TIMode;                 /*!< Specifies whether the TI mode is enabled or disabled.
                                       This parameter can be a value of @ref SPI_TI_Mode */

  uint32_t CRCPolynomial;          /*!< Specifies the CRC polynomial.
                                       This parameter is used only if CRC is enabled */

} SPI_InitTypeDef;


/**
  * @brief  SPI handle Structure definition
  */
typedef struct
{
  SPI_TypeDef                *Instance;  /*!< SPI registers base address */
  SPI_InitTypeDef            Init;       /*!< SPI communication parameters */
  uint8_t                    *pTxBuffPtr; /*!< Pointer to SPI Tx buffer */
  uint8_t                    *pRxBuffPtr; /*!< Pointer to SPI Rx buffer */
  uint16_t                   TxXferSize;  /*!< Size of the transmitted data */
  uint16_t                   RxXferSize;  /*!< Size of the received data */
  uint16_t                   TxXferCount; /*!< Number of transmitted bytes */
  uint16_t                   RxXferCount; /*!< Number of received bytes */
  DMA_HandleTypeDef          *hdmatx;     /*!< DMA TX handle */
  DMA_HandleTypeDef          *hdmarx;     /*!< DMA RX handle */
  HAL_LockTypeDef            Lock;        /*!< Locking object for SPI operations */
  //__IO HAL_SPI_StateTypeDef  State;       /*!< SPI communication state */
} SPI_HandleTypeDef;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants SPI Exported Constants
  * @{
  */

/** @defgroup SPI_mode SPI Mode
  * @{
  */
#define SPI_MODE_MASTER              (0x00000000U)
#define SPI_MODE_SLAVE               (SPI_CR1_MSTR)
/**
  * @}
  */

/** @defgroup SPI_data_direction Data Direction
  * @{
  */
#define SPI_DIRECTION_2LINES         (0x00000000U)
#define SPI_DIRECTION_1LINE          (SPI_CR1_BIDIMODE)
/**
  * @}
  */

/** @defgroup SPI_data_size Data Size
  * @{
  */
#define SPI_DATASIZE_8BIT            (0x00000000U)
#define SPI_DATASIZE_16BIT           (SPI_CR1_DFF)
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity Clock Polarity
  * @{
  */
#define SPI_POLARITY_LOW             (0x00000000U)
#define SPI_POLARITY_HIGH            (SPI_CR1_CPOL)
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE              (0x00000000U)
#define SPI_PHASE_2EDGE              (SPI_CR1_CPHA)
/**
  * @}
  */

/** @defgroup SPI_NSS NSS signal management
  * @{
  */
#define SPI_NSS_SOFT                 (0x00000000U)
#define SPI_NSS_HARD                 (SPI_CR1_SSM)
/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler Baud Rate Prescaler
  * @{
  */
#define SPI_BAUDRATEPRESCALER_2      (0x00000000U)
#define SPI_BAUDRATEPRESCALER_4      (SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_8      (SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_16     (SPI_CR1_BR_0 | SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_32     (SPI_CR1_BR_2)
#define SPI_BAUDRATEPRESCALER_64     (SPI_CR1_BR_1 | SPI_CR1_BR_2)
#define SPI_BAUDRATEPRESCALER_128    (SPI_CR1_BR_0 | SPI_CR1_BR_2)
#define SPI_BAUDRATEPRESCALER_256    (SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2)
/**
  * @}
  */

/** @defgroup SPI_First_Bit First Bit
  * @{
  */
#define SPI_FIRSTBIT_MSB             (0x00000000U)
#define SPI_FIRSTBIT_LSB             (SPI_CR1_LSBFIRST)
/**
  * @}
  */

/** @defgroup SPI_TI_Mode TI Mode
  * @{
  */
#define SPI_TIMODE_DISABLE           (0x00000000U)
#define SPI_TIMODE_ENABLE            (SPI_CR1_RXONLY)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SPI_Exported_Macros SPI Exported Macros
  * @{
  */

/** @defgroup SPI_Exported_Functions SPI Exported Functions
  * @{
  */

/* SPI initialization function */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);

/* SPI transmit function */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* SPI receive function */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4XX_HAL_SPI_H */
