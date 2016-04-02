#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LCDisplay::LCDisplay()
{
    begin();
}
void LCSDisplay::begin()
{
    LiquidCrystal_I2C  temp_lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
    lcd=temp_lcd;
    
    lcd.begin (16,2); //  <<----- My LCD was 16x2

    // Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home (); // go home
}

void LCDisplay::writerow1(String val)
{
	lcd.setCursor (0,0); 
	lcd.print(val);
	row1String = val;
}

void LCDisplay::writerow2(String val)
{
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
