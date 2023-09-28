#pragma once
#define I2C_DEVICE          "/dev/i2c-1"
#define TCS_ADDR            (0x29)
#define ID_REG              (0x12)
#define ENABLE              (0x80)
#define ENABLE_PON          (0x01)
#define ENABLE_AEN          (0x02)
#define ENABLE_BOTH         (0x03)
#define ATIME               (0x81)
#define WTIME               (0x83)
#define CONTROL             (0x8F)
#define DATA                (0x94)

void init(void);

uint8_t get_data(void);