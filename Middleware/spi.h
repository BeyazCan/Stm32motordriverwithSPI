/**
 * @file spi.h
 * @brief SPI-Kommunikationsbibliothek für STM32F4xx
 */
#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_hal.h"

// Pin-Definitionen
#define MOSI_PIN            GPIO_PIN_14
#define MOSI_PORT           GPIOE
#define MISO_PIN            GPIO_PIN_13
#define MISO_PORT           GPIOE
#define SCK_PIN             GPIO_PIN_15
#define SCK_PORT            GPIOE
#define CS_PIN              GPIO_PIN_12
#define CS_PORT             GPIOD

// SPI-Kommunikationsfunktionen
void SPI_Init(void);
uint8_t SPI_Transfer(uint8_t data);
uint32_t SPI_ReadWrite(uint8_t addr, uint32_t data, uint8_t read);
void SPI_WriteRegister(uint8_t addr, uint32_t data);
uint32_t SPI_ReadRegister(uint8_t addr);

#endif // SPI_H
