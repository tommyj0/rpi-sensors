#include "tcs.h"

int main(){
  uint16_t clear;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  float lux;

  get_data(&clear,&red, &green, &blue);

  lux = (-0.32466) * (red) + (1.57837) * (green) + (-0.73191) * (blue);
  if (lux < 0)
    lux = 0;
  
  // Output data to screen
  printf ("Red color : %d lux \n", red);
  printf ("Green color : %d lux \n", green);
  printf ("Blue color : %d lux \n", blue);
  printf ("IR : %d lux \n", clear);
  printf ("Ambient Light : %.2f lux \n", lux);

  return 0;
}