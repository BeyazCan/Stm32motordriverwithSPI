# TMC5160 Motordriver with SKR2 via SPI

This project implements an interface for controlling a TMC5160 motor driver via SPI (Serial Peripheral Interface) on a BigTreeTech SKR2 board with an STM32F4xx microcontroller. The communication is handled through a bit-banging SPI implementation.

## Features

- Bit-banging SPI implementation for STM32F4xx
- Complete control of the TMC5160 motor driver
- Support for position and velocity modes
- Configuration of current, acceleration, and speed
- StealthChop support for quiet operation

## Hardware Requirements

- BigTreeTech SKR2 Board (STM32F4xx microcontroller)
- TMC5160 Stepper Motor Driver
- Stepper motor

## Pin Configuration

The SPI communication uses the following pins:

| Signal | Pin        | Description        |
|--------|------------|--------------------|
| MOSI   | GPIOE_PIN14| Master Out Slave In |
| MISO   | GPIOE_PIN13| Master In Slave Out |
| SCK    | GPIOE_PIN15| Serial Clock        |
| CS     | GPIOD_PIN12| Chip Select         |

## Software Components

### SPI Library (`spi.c` / `spi.h`)

Implements the bit-banging SPI communication with the following functions:

- `SPI_Init()`: Initializes the SPI interface
- `SPI_Transfer()`: Transfers a byte over SPI
- `SPI_ReadWrite()`: Reads or writes a register via SPI
- `SPI_WriteRegister()`: Writes a value to a register
- `SPI_ReadRegister()`: Reads a value from a register

### TMC5160 Driver (`tmc5160.c` / `tmc5160.h`)

Implements the specific functions for the TMC5160 motor driver:

- `TMC5160_Init()`: Initializes the TMC5160 motor driver
- `TMC5160_SetCurrents()`: Configures the motor current
- `TMC5160_SetVelocityMode()`: Sets the driver to velocity mode
- `TMC5160_SetPositionMode()`: Sets the driver to position mode
- `TMC5160_SetSpeed()`: Sets the motor speed
- `TMC5160_SetAcceleration()`: Sets the acceleration and deceleration
- `TMC5160_MoveTo()`: Moves the motor to a specific position
- `TMC5160_GetPosition()`: Reads the current motor position
- `TMC5160_GetStatus()`: Reads the status of the motor driver

## Usage

### Motor Driver Initialization

```c
// Initialize SPI and TMC5160
TMC5160_Init();
```

### Setting Motor Current

```c
// Parameters: iRun (0-31), iHold (0-31), holdDelay (0-15)
TMC5160_SetCurrents(16, 8, 10);
```

### Using Position Mode

```c
// Set acceleration (value depends on motor parameters)
TMC5160_SetAcceleration(500);

// Move to absolute position
TMC5160_MoveTo(10000); // 10000 steps forward

// Read current position
int32_t currentPos = TMC5160_GetPosition();
```

### Using Velocity Mode

```c
// Switch to velocity mode
TMC5160_SetVelocityMode();

// Set acceleration
TMC5160_SetAcceleration(500);

// Set speed (positive = forward, negative = backward)
TMC5160_SetSpeed(50000); // Forward at 50000 µSteps/s
TMC5160_SetSpeed(-30000); // Backward at 30000 µSteps/s
```

## Implementation Notes

- The SPI communication is implemented as bit-banging, which offers flexibility in pin selection but may not be as performant as hardware SPI.
- The implementation supports the StealthChop mode of the TMC5160 for quiet operation.
- The delays in the SPI implementation (`for (volatile int j = 0; j < 100; j++);`) can be adjusted depending on the system clock to ensure stable communication.

## Possible Enhancements

- Implementation of hardware SPI for better performance
- Support for additional TMC5160 features such as CoolStep or StallGuard
- Multi-motor support through additional CS pins

## License

[Insert your preferred license here]
