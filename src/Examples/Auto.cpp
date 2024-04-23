/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#if 0
#include "mbed.h"
#include "LCD.h"

#define MOTORLINKSPIN PC_6
#define MOTORRECHTSPIN PC_7

AnalogIn speedPoti(PA_0);

lcd mylcd;

PwmOut motorLinks(MOTORLINKSPIN);
PwmOut motorRechts(MOTORRECHTSPIN);

float speed = 0.0f;

Thread thread;


void init()
{
    mylcd.clear();
	mylcd.cursorpos(0);
    mylcd.printf("Speed:");
    motorLinks.period(0.01f);
    motorRechts.period(0.01f);
    motorLinks = 0;
    motorRechts = 0;
}

void updateDisplay(){
    while(1){
	    mylcd.cursorpos(7);
        char buf[16];
        sprintf(buf, "%3d%%", (int)(speed*100));
        mylcd.printf(buf);
        ThisThread::sleep_for(10ms);
    }
}

int main()
{
    init();
    thread.start(updateDisplay);
    while (1)
    {
        speed = speedPoti;
        motorLinks = speed;
        motorRechts = speed;
    }
}

#endif