#include "tcs.h"
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

int fd;
uint8_t reg[1] = {0x94};
uint8_t data[8] = {0};
uint8_t buff[4];

void i2c_write (int fd, uint8_t buff[4], int bytes){
  if (write (fd, buff, bytes) != bytes)
  {
    printf ("FAILED TO WRITE %hhn \r\n", buff);
    exit (EXIT_FAILURE);
  }
}

void init () {
  // SETUP SHIT
  fd = open (I2C_DEVICE, O_RDWR);
  if (fd < 0)
    {
      printf ("Could not open the I2C device...\r\n");
      exit (EXIT_FAILURE);
    }

  if (ioctl (fd, I2C_SLAVE, TCS_ADDR) < 0)
    {
      printf ("Could not set I2C device address...\r\n");
      exit (EXIT_FAILURE);
    }

  buff[0] = ENABLE;
  buff[1] = ENABLE_BOTH;

  i2c_write(fd,buff,2);

  buff[0] = ATIME;
  buff[1] = 0x00;

  i2c_write(fd,buff,2);

  buff[0] = WTIME;
  buff[1] = 0xFF;

  i2c_write(fd,buff,2);

  buff[0] = CONTROL;
  buff[1] = 0x00;

  i2c_write(fd,buff,2);
}
void clean(void) {
  close(fd);
}

int get_data (uint16_t * c, uint16_t * r, uint16_t * g, uint16_t * b) {
  init();
  usleep(5);

  write (fd, reg, 1);

  if (read (fd, data, 8) != 8)
    {
      printf ("Erorr : Input/output Erorr \n");
      return -1;
    }

  *c = ((data[1] << 8) | data[0]);
  *r = ((data[3] << 8) | data[2]);
  *g = ((data[5] << 8) | data[4]);
  *b = ((data[7] << 8) | data[6]);

  clean();

  return 1;
}
