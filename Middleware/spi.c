/**
 * @file spi.c
 * @brief SPI-Kommunikationsimplementierung für STM32F4xx
 */
#include "spi.h"

/**
 * @brief Initialisiert die SPI-Schnittstelle via Bit-Banging
 */
void SPI_Init(void) {
    // GPIO Clock aktivieren
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // MOSI und SCK
    GPIO_InitStruct.Pin = MOSI_PIN | SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOSI_PORT, &GPIO_InitStruct);

    // MISO
    GPIO_InitStruct.Pin = MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(MISO_PORT, &GPIO_InitStruct);

    // CS
    GPIO_InitStruct.Pin = CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CS_PORT, &GPIO_InitStruct);

    // Ausgangszustand setzen
    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET); // CS inaktiv (high)
}

/**
 * @brief Überträgt ein Byte über SPI (Bit-Banging)
 * @param data Das zu sendende Byte
 * @return Das empfangene Byte
 */
uint8_t SPI_Transfer(uint8_t data) {
    uint8_t received = 0;

    for (int i = 7; i >= 0; i--) {
        // Bit setzen
        if (data & (1 << i)) {
            HAL_GPIO_WritePin(MOSI_PORT, MOSI_PIN, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(MOSI_PORT, MOSI_PIN, GPIO_PIN_RESET);
        }

        // Kurze Verzögerung
        for (volatile int j = 0; j < 100; j++);

        // Clock high
        HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);

        // Bit lesen
        if (HAL_GPIO_ReadPin(MISO_PORT, MISO_PIN) == GPIO_PIN_SET) {
            received |= (1 << i);
        }

        // Kurze Verzögerung
        for (volatile int j = 0; j < 100; j++);

        // Clock low
        HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
    }

    return received;
}

/**
 * @brief Liest oder schreibt ein Register über SPI
 * @param addr Die Adresse des Registers
 * @param data Die zu schreibenden Daten (für Lesevorgänge ignoriert)
 * @param read 1 für Lesevorgang, 0 für Schreibvorgang
 * @return Die gelesenen Daten oder 0 bei Schreibvorgang
 */
uint32_t SPI_ReadWrite(uint8_t addr, uint32_t data, uint8_t read) {
    uint32_t response = 0;

    // CS aktivieren (Low)
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

    // Adresse senden (bei Lesevorgang Bit 7 setzen)
    SPI_Transfer(addr | (read ? 0x80 : 0x00));

    // Daten senden/empfangen (4 Bytes)
    response |= (uint32_t)SPI_Transfer((data >> 24) & 0xFF) << 24;
    response |= (uint32_t)SPI_Transfer((data >> 16) & 0xFF) << 16;
    response |= (uint32_t)SPI_Transfer((data >> 8) & 0xFF) << 8;
    response |= (uint32_t)SPI_Transfer(data & 0xFF);

    // CS deaktivieren (High)
    HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);

    return response;
}

/**
 * @brief Schreibt einen Wert in ein Register
 * @param addr Die Adresse des Registers
 * @param data Die zu schreibenden Daten
 */
void SPI_WriteRegister(uint8_t addr, uint32_t data) {
    SPI_ReadWrite(addr, data, 0);
}

/**
 * @brief Liest einen Wert aus einem Register
 * @param addr Die Adresse des Registers
 * @return Der gelesene Wert
 */
uint32_t SPI_ReadRegister(uint8_t addr) {
    return SPI_ReadWrite(addr, 0, 1);
}
