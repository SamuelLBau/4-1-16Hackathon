#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "LCDisplay.h"

LCDisplay::LCDisplay()
{
    //begin();
}
void LCDisplay::begin()
{
    //LiquidCrystal_I2C  temp_lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
    //lcd=temp_lcd;
    
    lcd.begin (16,2); //  <<----- My LCD was 16x2

    // Switch on the backlight
    //lcd.backlight();
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home (); // go home
    lcd.setCursor (0,0);
    /*
	while(true)
    {
       lcd.setCursor (0,0); 
       lcd.print("TestA");
       lcd.setCursor (0,1); 
       lcd.print("TestB");
       Serial.println("Printed TESTS to LCD");
       delay(500);
    }
    */
    lcd.home (); // go home
}

int LCDisplay::writerow1(String val)
{
	lcd.setCursor (0,0);
    lcd.print("                ");
    lcd.setCursor (0,0);
	lcd.print(val);
	row1String = val;
}

int LCDisplay::writerow2(String val)
{
	lcd.setCursor (0,1);
    lcd.print("                ");
    lcd.setCursor (0,1);  	
	lcd.print(val);
	row2String = val;
}

String LCDisplay::getrow1()
{
	return row1String;
}


String LCDisplay::getrow2()
{
	return row2String;
}
