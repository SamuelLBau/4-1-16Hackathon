#ifndef Touchpad_h
#define Touchpad_h

#include "mpr121.h"
#include <Wire.h>
#include "Arduino.h"

#define True 1
#define False 0
class Touchpad
{
    public:
        Touchpad();
        void begin();
        void updateData();
        void setPW(String);
        String getPW();
        boolean compareToPW(String);
        boolean isPWAccepted();
        void setPWAcceptedFalse();
        void setPWAcceptedTrue();

        String getString();
    
    private:
        bool checkInterrupt();
        void set_register(int, unsigned char, unsigned char);
        void mpr121_setup(void);
        int irqpin;  // Digital 2
        boolean touchStates[12]; //to keep track of the previous touch states
        String stringone;
        String num;
        String pass;
        boolean pwaccepted;
        void shortBuzz();
    
    
};






#endif
