#include "mbed.h"

class HSAnalogIn
{
    private:
    int BDCin;
    int myPin=0;
    int gruppe=0;
    
    void warte(int zeit)
    {
     for (int i=0;i<zeit*5;i++)
     {
      asm("nop\n\t");   
     }   
    }
    
    public:
    HSAnalogIn(int Pin);

    

    float read();

    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalized to a 16-bit value
     */
    unsigned short read_u16();

    /** An operator shorthand for read()
     *
     * The float() operator can be used as a shorthand for read() to simplify common code sequences
     *
     * Example:
     * @code
     * float x = volume.read();
     * float x = volume;
     *
     * if(volume.read() > 0.25) { ... }
     * if(volume > 0.25) { ... }
     * @endcode
     */
     
    operator float()
    {
        // Underlying call is thread safe
        return read();
    }

    virtual ~HSAnalogIn()
    {
        // Do nothing
    }
    
};
