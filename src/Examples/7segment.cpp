//mit if 1=aktivieren, if 0=deaktivieren
#if 0

#include "mbed.h"
#include "LCD.h"

DigitalOut myLed(PC_0);
DigitalIn mySwitch(PB_0);
AnalogIn myPoti(PA_0);
PortOut myPort(PortC);

Thread thread;

lcd mylcd;
bool onOff = false;
// 7-Segmentanzeige hgfe dcba because the 7-segment display is connected to the port in reverse order
uint8_t nubers[] = {0x3F, 0x30, 0x5B, 0x79, 0x74, 0x6D, 0x6F, 0x38, 0x7F, 0x7D};

uint8_t currentNumber = 0;

void init()
{
    mylcd.clear();
	mylcd.cursorpos(0);
	mylcd.printf("Hello World!");
	mySwitch.mode(PullDown);
    onOff = !mySwitch;
}

uint16_t getNumber(uint16_t number, uint8_t segments, bool point = false)
{
    return nubers[number] | (point << 7) | (segments << 11);
}
void loop(){
    currentNumber = (uint16_t)(myPoti.read() * 99);
    
    if (onOff != mySwitch)
    {
        onOff = mySwitch;
        mylcd.cursorpos(0x40);
        if(mySwitch ==true) mylcd.printf("myLed AN ");
        else	mylcd.printf("myLed AUS");
    }
}

void updateSegmentDisplay()
{
    while(1)
    {
        myPort = getNumber((uint16_t)currentNumber/10, 0b01);
        ThisThread::sleep_for(1ms);
        myPort = getNumber((uint16_t)currentNumber%10, 0b10);
        ThisThread::sleep_for(1ms);
    }
}

int main()
{
    init();
    
    thread.start(updateSegmentDisplay);

    while(1)
    {
        loop();
        ThisThread::sleep_for(10ms);
    }
}

#endif