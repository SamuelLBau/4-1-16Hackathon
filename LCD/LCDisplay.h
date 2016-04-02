#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7


class LCDisplay
{
	public:
        LCDisplay();
        void begin();
        int writerow1();
        int writerow2();
        int getrow1();
        int getrow2();
	
	private:
        String row1String;
        String row2String;
        LiquidCrystal_I2C  lcd;
	
};
#endif
