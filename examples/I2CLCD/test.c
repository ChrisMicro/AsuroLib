#include "asuro.h"
#include "lcd.h"
#include "i2c.h"

#define DELAY 1500

int main(void)
{
  Init();
  InitI2C();
  InitLCD();
   
   PrintLCD("LCD Test: ", 0);
   Msleep(DELAY);
   
   while(1)
   {

      Msleep(DELAY);
      BacklightLCD(1);
     
      ClearLCD();
      PrintSetLCD(3, 0, "Set Cursor");
      Msleep(DELAY);
      ClearLCD();
      PrintSetLCD(0 , 1, "Set Line");
      Msleep(DELAY);
      ClearLCD();
      PrintSetLCD(1 , 1, "Set Cursor Line");
      Msleep(DELAY);
      ClearLCD();
      PrintSetLCD(0 , 0, "Test Int");
      SetCursorLCD(9,0);
      PrintIntLCD(10);
      Msleep(DELAY);
      ClearLCD();
      PrintAlignLCD(LEFT , 0, "LEFT");
      Msleep(DELAY);
      ClearLCD();
      PrintAlignLCD(CENTER , 0, "CENTER");
      Msleep(DELAY);
      ClearLCD();
      PrintAlignLCD(RIGHT , 0, "RIGHT");
      Msleep(DELAY);
      ClearLCD();
      SetCursorLCD(0,0);
      PrintLCD("abcdefghijklmnopqrstuvwyz1234567", 1);
      Msleep(DELAY);

    }
   
   return 0;
}

