/**
 * @file tmc5160.c
 * @brief TMC5160 Schrittmotortreiber-Implementierung
 */
#include "tmc5160.h"
/**
 * @brief Initialisiert den TMC5160 Motortreiber
 */
void TMC5160_SetCurrents(uint8_t iRun, uint8_t iHold, uint8_t holdDelay) {
    // I_HOLD_IRUN: IHOLD(4..0)=iHold, IRUN(12..8)=iRun, IHOLDDELAY(19..16)=holdDelay
    uint32_t value = ((uint32_t)iHold & 0x1F) |
                    (((uint32_t)iRun & 0x1F) << 8) |
                    (((uint32_t)holdDelay & 0x0F) << 16);
    SPI_WriteRegister(TMC5160_IHOLD_IRUN, value);
}
void TMC5160_SetVelocityMode(void) {
    SPI_WriteRegister(TMC5160_RAMPMODE, TMC5160_MODE_VELOCITY);
}

/**
 * @brief Setzt den TMC5160 in den Positionsmodus
 */
void TMC5160_SetPositionMode(void) {
    SPI_WriteRegister(TMC5160_RAMPMODE, TMC5160_MODE_POSITION);
}


void TMC5160_SetSpeed(int32_t speed) {
    SPI_WriteRegister(TMC5160_VMAX, abs(speed));

    // Für negative Geschwindigkeit den Velocitymodus negativ setzen
    if (speed < 0) {
        SPI_WriteRegister(TMC5160_RAMPMODE, TMC5160_MODE_VELOCITY + 1); // Negative Richtung
    } else {
        SPI_WriteRegister(TMC5160_RAMPMODE, TMC5160_MODE_VELOCITY); // Positive Richtung
    }
}

void TMC5160_SetAcceleration(uint32_t accel) {
    SPI_WriteRegister(TMC5160_AMAX, accel);
    SPI_WriteRegister(TMC5160_DMAX, accel); // Verzögerung gleich Beschleunigung
}

void TMC5160_MoveTo(int32_t position) {
    TMC5160_SetPositionMode();
    SPI_WriteRegister(TMC5160_XTARGET, position);
}

int32_t TMC5160_GetPosition(void) {
    return (int32_t)SPI_ReadRegister(TMC5160_XACTUAL);
}

uint32_t TMC5160_GetStatus(void) {
    return SPI_ReadRegister(TMC5160_GSTAT);
}
void TMC5160_Init(void) {
    // SPI initialisieren
    SPI_Init();

    HAL_Delay(200); // Warten auf Hochfahren des TMC5160

    uint32_t status= SPI_ReadRegister(TMC5160_GSTAT);
    if (status != 0xFFFFFFFF) { // Wenn gültige Daten zurückkommen
            // Grundkonfiguration
            SPI_WriteRegister(TMC5160_GCONF, 0x00000004);  // EN_PWM_MODE aktiviere
    // Motorstrom konfigurieren (Standard)
    TMC5160_SetCurrents(16, 8, 10); // iRun=16, iHold=8, holdDelay=10

    // Rampenparameter
    SPI_WriteRegister(TMC5160_TPOWERDOWN, 10);     // Power down time: ~10ms
    SPI_WriteRegister(TMC5160_A1, 1000);           // Beschleunigung 1
    SPI_WriteRegister(TMC5160_V1, 50000);          // Geschwindigkeit 1
    SPI_WriteRegister(TMC5160_AMAX, 500);          // Max. Beschleunigung
    SPI_WriteRegister(TMC5160_VMAX, 100000);       // Max. Geschwindigkeit
    SPI_WriteRegister(TMC5160_DMAX, 700);          // Max. Verzögerung
    SPI_WriteRegister(TMC5160_D1, 1400);           // Verzögerung 1
    SPI_WriteRegister(TMC5160_VSTOP, 10);          // Stop-Geschwindigkeit

    // Chopconf für StealthChop
    SPI_WriteRegister(TMC5160_CHOPCONF, 0x000100C3); // TOFF=3, HSTRT=4, HEND=0, TBL=2

    // PWM-Konfiguration für StealthChop
    SPI_WriteRegister(TMC5160_PWMCONF, 0x000401C8);  // PWM_FREQ=1, AUTO_GRAD, PWM_GRAD=200, PWM_OFS=200

    // Position zurücksetzen
    SPI_WriteRegister(TMC5160_XACTUAL, 0);
    SPI_WriteRegister(TMC5160_XTARGET, 0);

    // Positionsmodus aktivieren
    TMC5160_SetPositionMode();
}
}
