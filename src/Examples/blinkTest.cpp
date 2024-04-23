/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#if 0
#include "mbed.h"



#define WAIT_TIME_MS 500 
DigitalOut led1(PC_0);

int main()
{


    while (true)
    {
        led1 = !led1;
        HAL_Delay(WAIT_TIME_MS);
    }
}

#endif