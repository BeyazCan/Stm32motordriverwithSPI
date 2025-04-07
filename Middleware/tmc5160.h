/**
 * @file tmc5160.h
 * @brief TMC5160 Schrittmotortreiber-Bibliothek
 */
#ifndef TMC5160_H
#define TMC5160_H

#include "spi.h"
#include "stm32f4xx_hal.h"

// TMC5160 Register
#define TMC5160_GCONF            0x00
#define TMC5160_GSTAT            0x01
#define TMC5160_IOIN             0x04
#define TMC5160_IHOLD_IRUN       0x10
#define TMC5160_TPOWERDOWN       0x11
#define TMC5160_TSTEP            0x12
#define TMC5160_TPWMTHRS         0x13
#define TMC5160_TCOOLTHRS        0x14
#define TMC5160_THIGH            0x15
#define TMC5160_RAMPMODE         0x20
#define TMC5160_XACTUAL          0x21
#define TMC5160_VACTUAL          0x22
#define TMC5160_VSTART           0x23
#define TMC5160_A1               0x24
#define TMC5160_V1               0x25
#define TMC5160_AMAX             0x26
#define TMC5160_VMAX             0x27
#define TMC5160_DMAX             0x28
#define TMC5160_D1               0x2A
#define TMC5160_VSTOP            0x2B
#define TMC5160_TZEROWAIT        0x2C
#define TMC5160_XTARGET          0x2D
#define TMC5160_CHOPCONF         0x6C
#define TMC5160_COOLCONF         0x6D
#define TMC5160_PWMCONF          0x70

// Rampen-Modi
#define TMC5160_MODE_POSITION    0
#define TMC5160_MODE_VELOCITY    1
#define TMC5160_MODE_HOLD        2

// TMC5160 Funktionen
void TMC5160_Init(void);
void TMC5160_SetCurrents(uint8_t iRun, uint8_t iHold, uint8_t holdDelay);
void TMC5160_SetVelocityMode(void);
void TMC5160_SetPositionMode(void);
void TMC5160_SetSpeed(int32_t speed);
void TMC5160_SetAcceleration(uint32_t accel);
void TMC5160_MoveTo(int32_t position);
int32_t TMC5160_GetPosition(void);
uint32_t TMC5160_GetStatus(void);

#endif // TMC5160_H
