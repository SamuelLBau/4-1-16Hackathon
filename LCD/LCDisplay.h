#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>




class LCDisplay
{
	public:
	LCDisplay();
	int writerow1();
	int writerow2();
	int getrow1();
	int getrow2();
	
	private:
	I2C_ADDR     // <<----- Add your address here.  Find it from I2C Scanner
	BACKLIGHT_PIN     
	En_pin  
	Rw_pin  
	Rs_pin  
	D4_pin  
	D5_pin  
	D6_pin 
	D7_pin  
	
};
#endif
