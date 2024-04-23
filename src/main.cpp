//mit if 1=aktivieren, if 0=deaktivieren
#if 1

#include "mbed.h"

DigitalOut myLed(PC_0);

void init()
{

}

int main()
{
    init();
    while(1)
    {
        myLed = !myLed;
        thread_sleep_for(1000);
    }
}
#endif
