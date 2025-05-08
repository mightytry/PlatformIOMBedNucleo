#include "HSAnalogIn.h"


#define BDC_CR1_OVRIE 0
#define BDC_CR1_RES 0b00   //12-bit (TCONV = 12 BDCgCLK cycles)
#define BDC_CR1_AWDEN 0    //Analog watchdog disabled on regular channels
#define BDC_CR1_JAWDEN 0   // Analog watchdog disabled on injected channels
#define BDC_CR1_PDI 0      //The BDCg is powered up when waiting for a start event
#define BDC_CR1_PDD 0      //The BDCg is powered up during the delay
#define BDC_CR1_DISCNUM 0b000  // 1 channel
#define BDC_CR1_JDISCEN 0  //Discontinuous mode on injected channels disabled
#define BDC_CR1_DISCEN 0   //Discontinuous mode on regular channels disabled
#define BDC_CR1_JAUTO 0    // Automatic injected group conversion disabled
#define BDC_CR1_AWDSGL 0   //Analog watchdog enabled on all channels
#define BDC_CR1_SCAN 0     //Scan mode disabled
#define BDC_CR1_JEOCIE 0   //JEOC interrupt disabled
#define BDC_CR1_AWDIE 0    // Analog watchdog interrupt disabled
#define BDC_CR1_EOCIE 0    //EOC interrupt disabled
#define BDC_CR1_AWDCH 0b00000  //BDCg analog input BDC_IN0



#define BDC_CR2_SWSTART 0
#define BDC_CR2_EXTEN 0b00
#define BDC_CR2_EXTSEL 0b0000
#define BDC_CR2_JSWSTART 0
#define BDC_CR2_JEXTEN 0b00
#define BDC_CR2_JEXTSEL 0b0000
#define BDC_CR2_ALIGN 1
#define BDC_CR2_EOCS 0      //EOC set at End of each conversion
#define BDC_CR2_DDS 0      //No DMA  request
#define BDC_CR2_DMA 0      //DMA disabled
#define BDC_CR2_DELS 0b001 //Until the converted data have been read (DR read or EOC=0 for regular conversions)
#define BDC_CR2_BDC_CFG 0  //Bank A selected for channels BDCgg_IN0..31
#define BDC_CR2_CONT 0     // Single conversion mode
#define BDC_CR2_ADON 1     // Enable BDCgg: conversions can start as soon as a start event (hardware or software) is received.




    HSAnalogIn::HSAnalogIn(int Pin)
    {
       //Analog init
       
        myPin=Pin;
        RCC->APB2ENR|=(1<<9);
        RCC->AHBENR|=0b111;
        RCC->CR|=1; //HSI On
        while ((RCC->CR&0b10)==0);

        ADC1->CR1= (BDC_CR1_OVRIE<<26)+(BDC_CR1_RES<<24)+(BDC_CR1_AWDEN<<23)+(BDC_CR1_JAWDEN<<22)+(BDC_CR1_PDI<<17)+(BDC_CR1_PDD<<16)+(BDC_CR1_DISCNUM<<13)+(BDC_CR1_JDISCEN<<12)+(BDC_CR1_DISCEN<<11)+(BDC_CR1_JAUTO<<10)+(BDC_CR1_AWDSGL<<9)+(BDC_CR1_SCAN<<8)+(BDC_CR1_JEOCIE<<7)+(BDC_CR1_AWDIE<<6)+(BDC_CR1_EOCIE<<5)+(BDC_CR1_AWDCH);
 
        ADC1->CR2=(BDC_CR2_SWSTART<<30)+(BDC_CR2_EXTEN<<28)+(BDC_CR2_EXTSEL<<24)+(BDC_CR2_JSWSTART<<22)+(BDC_CR2_JEXTEN<<20)+(BDC_CR2_JEXTSEL<<16)+(BDC_CR2_ALIGN<<11)+(BDC_CR2_EOCS<<10)+(BDC_CR2_DDS<<9)+(BDC_CR2_DMA<<8)+(BDC_CR2_DELS<<4)+(BDC_CR2_BDC_CFG<<2)+(BDC_CR2_CONT<<1)+(BDC_CR2_ADON);
        switch ((int)Pin)  //0-15 PA, 16-31 PB, 32-47 PC
        {
            case 0: BDCin=0;  GPIOA->MODER|=0b11; break;//PA_0 .. PA_7
            case 1: BDCin=1;  GPIOA->MODER|=0b11<<2; break;
            case 2: BDCin=2;  GPIOA->MODER|=0b11<<4; break;
            case 3: BDCin=3;  GPIOA->MODER|=0b11<<6; break;
            case 4: BDCin=4;  GPIOA->MODER|=0b11<<8; break;
            case 5: BDCin=5;  GPIOA->MODER|=0b11<<10; break;
            case 6: BDCin=6;  GPIOA->MODER|=0b11<<12; break;
            case 7: BDCin=7;  GPIOA->MODER|=0b11<<14; break;
            case 16: //PB_0
                BDCin=8; GPIOB->MODER|=0b11; break;
            case 17: //PB_1
                BDCin=9; GPIOB->MODER|=0b11<<2; break;
            case 18: //PB_2
                BDCin=0; GPIOB->MODER|=0b11<<4; gruppe=1; break;
            case 28: //PB_12
                BDCin=18; GPIOB->MODER|=0b11<<24; break;
            case 29: //PB_13
                BDCin=19; GPIOB->MODER|=0b11<<26; break;
            case 30: //PB_14
                BDCin=20; GPIOB->MODER|=0b11<<28; break;
            case 31: //PB_15
                BDCin=21; GPIOB->MODER|=0b11<<30; break;
            case 32: //PC_0
                BDCin=10; GPIOC->MODER|=0b11; break;
            case 33: //PC_1
                BDCin=11; GPIOC->MODER|=0b11<<2; break;
            case 34: //PC_2
                BDCin=12; GPIOC->MODER|=0b11<<4; break;
            case 35: //PC_3
                BDCin=13; GPIOC->MODER|=0b11<<6; break;
            case 36: //PC_4
                BDCin=14; GPIOC->MODER|=0b11<<8; break;
            case 37: //PC_5
                BDCin=15; GPIOC->MODER|=0b11<<10; break;
        };

    };

    float HSAnalogIn::read()
    {
/*
    RCC->APB2ENR|=(1<<9);
    RCC->AHBENR|=0b111;
    RCC->CR|=1; //HSI On
    while ((RCC->CR&0b10)==0);
    ADC1->CR1= (BDC_CR1_OVRIE<<26)+(BDC_CR1_RES<<24)+(BDC_CR1_AWDEN<<23)+(BDC_CR1_JAWDEN<<22)+(BDC_CR1_PDI<<17)+(BDC_CR1_PDD<<16)+(BDC_CR1_DISCNUM<<13)+(BDC_CR1_JDISCEN<<12)+(BDC_CR1_DISCEN<<11)+(BDC_CR1_JAUTO<<10)+(BDC_CR1_AWDSGL<<9)+(BDC_CR1_SCAN<<8)+(BDC_CR1_JEOCIE<<7)+(BDC_CR1_AWDIE<<6)+(BDC_CR1_EOCIE<<5)+(BDC_CR1_AWDCH);
    ADC1->CR2=(BDC_CR2_SWSTART<<30)+(BDC_CR2_EXTEN<<28)+(BDC_CR2_EXTSEL<<24)+(BDC_CR2_JSWSTART<<22)+(BDC_CR2_JEXTEN<<20)+(BDC_CR2_JEXTSEL<<16)+(BDC_CR2_ALIGN<<11)+(BDC_CR2_EOCS<<10)+(BDC_CR2_DDS<<9)+(BDC_CR2_DMA<<8)+(BDC_CR2_DELS<<4)+(BDC_CR2_BDC_CFG<<2)+(BDC_CR2_CONT<<1)+(BDC_CR2_ADON);
    switch ((int)myPin)  //0-15 PA, 16-31 PB, 32-47 PC
        {
            case 0: BDCin=0;  GPIOA->MODER|=0b11; break;//PA_0 .. PA_7
            case 1: BDCin=1;  GPIOA->MODER|=0b11<<2; break;
            case 2: BDCin=2;  GPIOA->MODER|=0b11<<4; break;
            case 3: BDCin=3;  GPIOA->MODER|=0b11<<6; break;
            case 4: BDCin=4;  GPIOA->MODER|=0b11<<8; break;
            case 5: BDCin=5;  GPIOA->MODER|=0b11<<10; break;
            case 6: BDCin=6;  GPIOA->MODER|=0b11<<12; break;
            case 7: BDCin=7;  GPIOA->MODER|=0b11<<14; break;
            case 16: //PB_0
                BDCin=8; GPIOB->MODER|=0b11; break;
            case 17: //PB_1
                BDCin=9; GPIOB->MODER|=0b11<<2; break;
            case 18: //PB_2
                BDCin=0; GPIOB->MODER|=0b11<<4; gruppe=1; break;
            case 28: //PB_12
                BDCin=18; GPIOB->MODER|=0b11<<24; break;
            case 29: //PB_13
                BDCin=19; GPIOB->MODER|=0b11<<26; break;
            case 30: //PB_14
                BDCin=20; GPIOB->MODER|=0b11<<28; break;
            case 31: //PB_15
                BDCin=21; GPIOB->MODER|=0b11<<30; break;
            case 32: //PC_0
                BDCin=10; GPIOC->MODER|=0b11; break;
            case 33: //PC_1
                BDCin=11; GPIOC->MODER|=0b11<<2; break;
            case 34: //PC_2
                BDCin=12; GPIOC->MODER|=0b11<<4; break;
            case 35: //PC_3
                BDCin=13; GPIOC->MODER|=0b11<<6; break;
            case 36: //PC_4
                BDCin=14; GPIOC->MODER|=0b11<<8; break;
            case 37: //PC_5
                BDCin=15; GPIOC->MODER|=0b11<<10; break;
        };
 */
    
    ADC1->SQR5=BDCin;
    if (gruppe==1) ADC1->CR2|= (1<<2); //gruppe
    else ADC1->CR2&=~(1<<2);

    ADC1->CR2|=(1<<30); //SWStart


    while ((ADC1->SR & 0b10)==0);
    //warte(1000);

    return (float)ADC1->DR/65535;
    };

    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalized to a 16-bit value
     */
     
    unsigned short HSAnalogIn::read_u16()
    {
        
    ADC1->SQR5=BDCin;
    if (gruppe==1) ADC1->CR2|= (1<<2); //gruppe
    else ADC1->CR2&=~(1<<2);

    ADC1->CR2|=(1<<30); //SWStart


    while ((ADC1->SR & 0b10)==0);
    return (unsigned short)ADC1->DR;
    
    };

