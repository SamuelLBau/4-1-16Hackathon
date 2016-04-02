#include "mpr121.h"
#include <Wire.h>
#include "Touchpad.h"


#define OPEN_LATCH_OUTPUT       PORT->Group[3].DIRSET.reg = PORT_PB30
#define LED1_ON_MACRO           PORT->Group[3].OUTSET.reg = PORT_PB30
#define LED1_OFF_MACRO          PORT->Group[3].OUTCLR.reg = PORT_PB30
Touchpad::Touchpad()
{
    irqpin = 2;  // Digital 2
    touchStates[12]; //to keep track of the previous touch states
    stringone = "";
    num = "";
    pass = "1337";
    pwaccepted = 0;
    
}
void Touchpad::begin()
{
    pinMode(irqpin, INPUT);
    digitalWrite(irqpin, HIGH); //enable pullup resistor
    Wire.begin();
    OPEN_LATCH_OUTPUT;

    mpr121_setup();
}
void Touchpad::setPW(String PW)
{
    pass = PW;
}
String Touchpad::getPW()
{
    return pass;
}
String Touchpad::getString()
{
  return stringone;
}
boolean Touchpad::compareToPW(String tPW)
{
    if(tPW == pass)
    {
        return True;
    }
    else
    {
        return False;
    }
}
boolean Touchpad::isPWAccepted()
{
    return pwaccepted;
}
void Touchpad::setPWAcceptedFalse()
{
    pwaccepted = False;
}
void Touchpad::setPWAcceptedTrue()
{
    pwaccepted = True;
}
void Touchpad::updateData()
{
    if(!checkInterrupt())
    {
    
        //read the touch state from the MPR121
        Wire.requestFrom(0x5A,2); 
        
        byte LSB = Wire.read();
        byte MSB = Wire.read();
        
        uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states

        
        for (int i=0; i < 12; i++)
        {  // Check what electrodes were pressed
            if(touched & (1<<i))
            {
          
                if(touchStates[i] == 0)
                {
                    //pin i was just touched
              
                  switch(i) 
                  {
                    case 0:
                    stringone = "";
                    num = "";
                    Serial.print("Cleared");
                    break;
                    case 1:
                    num = "7";
                    break;
                    case 2:
                    num = "4";
                    break;
                    case 3:
                    num = "1";
                    break;
                    case 4:
                    num = "0";
                    break;
                    case 5:
                    num = "8";
                    break;
                    case 6:
                    num = "5";
                    break;
                    case 7:
                    num = "2";
                    break;
                    case 8:
                        if(stringone == pass)
                        {
                          Serial.print("Password accepted");
                          if(pwaccepted == 1)
                          {
                            pwaccepted=0;
                          }
                          else
                          {
                            pwaccepted = 1;
                          }
                          stringone = "";
                          num = "";
                        }
                        else
                        {
                          Serial.print("Password Denied");
                          shortBuzz();
                          delay(100);
                          shortBuzz();
                          stringone = "";
                          num = "";
                        }

                    break;
                    case 9:
                    num = "9";
                    break;
                    case 10:
                    num = "6";
                    break;
                    case 11:
                    num = "3";
                    break;
                    default:
                    break;
                }
                stringone = stringone + num;
                Serial.println(stringone);
              } 
              else if(touchStates[i] == 1)
              {
              //pin i is still being touched
              }  
              touchStates[i] = 1;      
          
            } 
            else
            {
                if(touchStates[i] == 1)
                {

                  
                  //pin i is no longer being touched
                }
            touchStates[i] = 0;
            }
    } 
  } 
}
void Touchpad::mpr121_setup(void){

  set_register(0x5A, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH);
  set_register(0x5A, ELE0_R, REL_THRESH);
 
  set_register(0x5A, ELE1_T, TOU_THRESH);
  set_register(0x5A, ELE1_R, REL_THRESH);
  
  set_register(0x5A, ELE2_T, TOU_THRESH);
  set_register(0x5A, ELE2_R, REL_THRESH);
  
  set_register(0x5A, ELE3_T, TOU_THRESH);
  set_register(0x5A, ELE3_R, REL_THRESH);
  
  set_register(0x5A, ELE4_T, TOU_THRESH);
  set_register(0x5A, ELE4_R, REL_THRESH);
  
  set_register(0x5A, ELE5_T, TOU_THRESH);
  set_register(0x5A, ELE5_R, REL_THRESH);
  
  set_register(0x5A, ELE6_T, TOU_THRESH);
  set_register(0x5A, ELE6_R, REL_THRESH);
  
  set_register(0x5A, ELE7_T, TOU_THRESH);
  set_register(0x5A, ELE7_R, REL_THRESH);
  
  set_register(0x5A, ELE8_T, TOU_THRESH);
  set_register(0x5A, ELE8_R, REL_THRESH);
  
  set_register(0x5A, ELE9_T, TOU_THRESH);
  set_register(0x5A, ELE9_R, REL_THRESH);
  
  set_register(0x5A, ELE10_T, TOU_THRESH);
  set_register(0x5A, ELE10_R, REL_THRESH);
  
  set_register(0x5A, ELE11_T, TOU_THRESH);
  set_register(0x5A, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5A, ELE_CFG, 0x0C);
  
}
void Touchpad::set_register(int address, unsigned char r, unsigned char v)
{
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}
bool Touchpad::checkInterrupt()
{
  return digitalRead(irqpin);
}
void Touchpad::shortBuzz()
{
  LED1_ON_MACRO;
  delay(100);
  LED1_OFF_MACRO;
}
