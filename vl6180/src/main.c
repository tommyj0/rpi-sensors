#include <stdio.h>
#include "tof.h"
#include <unistd.h>

int main(){
    int handle = vl6180_initialise(1);

    for (int i = 0; i < 100; ++i){
        usleep(100*1000);
        int distance = get_distance(handle);
        printf("distance is %dmm\n", distance);
    }
}
