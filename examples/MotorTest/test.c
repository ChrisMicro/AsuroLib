/*****************************************************************************/
/*!
  /file 	Test.c
  /brief 	Test Routinen fuer die Motorfunktionen Go und Turn
  /author stochri, m.a.r.v.i.n

  /version      V001 - 29.07.2005 - stochri\n
                Initial Release
  /version      V002 - 19.12.2005 - m.a.r.v.i.n\n
                speed parameter for go function added
  /version      V003 - 20.12.2005 - m.a.r.v.i.n\n
                speed parameter for turn function and variable Wheelspeed added
  /version      V004 - 18.08.2007 - m.a.r.v.i.n\n
                SerPrint verwenden anstelle von SerWrite
*/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"

unsigned char Wheelspeed[2];

#define aus MotorDir(BREAK,BREAK)
void testfahrt(void)
{
  unsigned char s1=100,s2=100;

  MotorSpeed(150,150);
  MotorDir(FWD,FWD);

  while (1)
  {
    if (Wheelspeed[0]<150)s1++;
    if (Wheelspeed[0]>160)s1--;
    if (Wheelspeed[1]<150)s2++;
    if (Wheelspeed[1]>160)s2--;

    Msleep(2);
    MotorSpeed(s1,s2);

    SerPrint("\n\r  speed Left,Right ");

    PrintInt(Wheelspeed[0]);
    PrintInt(Wheelspeed[1]);
  }
}
void treasure(void)
{
  Go(350,150);
  Go(-50,150);
  Msleep(1000);

  Turn(90,150);
  Go(100,150);
  Turn(-90,150);
  Go(170,150);
  Turn(-90,150);
  Go(100,150);
  Turn(-90,150);

  Go(470,150);
  Go(-50,150);

  Msleep(1000);
  Turn(90,150);
  Go(100,150);
  Turn(-90,150);
  Go(170,150);
  Turn(-90,150);
  Go(100,150);
  Turn(-90,150);
}

int main(void)
{
  int n;

  Init();
  EncoderInit();
  StatusLED(OFF);
  SerPrint("\n\r motor calibration V0.1 \n\r");
  while (1)
  {
    n=PollSwitch ();
    if (n==8)
    {
      SerPrint("\n\r testfahrt \n\r");
      Msleep(3000);
      testfahrt();
    }
    if (n==16)
    {
      SerPrint("\n\r treasure \n\r");
      Msleep(3000);
      treasure();
    }

    StatusLED(RED);
    Msleep(500);
    StatusLED(GREEN);
    Msleep(500);
  }
  return 0;
}
