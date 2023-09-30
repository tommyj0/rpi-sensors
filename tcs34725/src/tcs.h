#pragma once
#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

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

int get_data(uint16_t*,uint16_t*, uint16_t*, uint16_t*);

void clean(void);