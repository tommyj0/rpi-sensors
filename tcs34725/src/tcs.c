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
uint8_t reg[1] = { 0x94 };
uint8_t data[8] = { 0 };
uint8_t buff[2];
int cData;
int red;
int green;
int blue;

void
init ()
{
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

  if (write (fd, buff, 2) != 2)
    {
      printf ("ENABLE INITIATION FAILED\r\n");
      exit (EXIT_FAILURE);
    }

  buff[0] = ATIME;
  buff[1] = 0x00;

  if (write (fd, buff, 2) != 2)
    {
      printf ("ATIME INITIATION FAILED\r\n");
      exit (EXIT_FAILURE);
    }

  buff[0] = WTIME;
  buff[1] = 0xFF;

  if (write (fd, buff, 2) != 2)
    {
      printf ("WAIT TIME INITIATION FAILED\r\n");
      exit (EXIT_FAILURE);
    }

  buff[0] = CONTROL;
  buff[1] = 0x00;

  if (write (fd, buff, 2) != 2)
    {
      printf ("CONTROL INITIATION FAILED\r\n");
      exit (EXIT_FAILURE);
    }
}
uint8_t
get_data ()
{
  for (int i; i < 500; ++i)
    {
      write (fd, reg, 1);

      if (read (fd, data, 8) != 8)
        {
          printf ("Erorr : Input/output Erorr \n");
          exit (EXIT_FAILURE);
        }

      cData = ((data[1] << 8) | data[0]);
      red = ((data[3] << 8) | data[2]);
      green = ((data[5] << 8) | data[4]);
      blue = ((data[7] << 8) | data[6]);

      // Calculate lux
      float lux
          = (-0.32466) * (red) + (1.57837) * (green) + (-0.73191) * (blue);
      if (lux < 0)
        {
          lux = 0;
        }

      // Output data to screen
      printf ("Red color : %d lux \n", red);
      printf ("Green color : %d lux \n", green);
      printf ("Blue color : %d lux \n", blue);
      printf ("IR : %d lux \n", cData);
      printf ("Ambient Light : %.2f lux \n", lux);
      usleep (500000);
    }

  close (fd);

  exit (EXIT_SUCCESS);
}