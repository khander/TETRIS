#include "includes.h"

//#include <LiquidCrystal_I2C.h>

class Lcd : public LiquidCrystal_I2C{
public:
void lcd_init();
};

void Lcd::lcd_init(){
    
    this->init(); 
    this->backlight();
}
/*
void lcd_start(LiquidCrystal_I2C lcd){
    lcd.clear();              // clear display
    lcd.setCursor(0, 0);      // move cursor to   (0, 0)
    lcd.print("TETRIS BY");
    lcd.setCursor(0, 1);
    lcd.print("KHANDER");
}

*/
