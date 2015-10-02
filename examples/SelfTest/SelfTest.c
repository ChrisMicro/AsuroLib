/*******************************************************************************
*
* File Name:   SelfTest.c
* Project  :   SelfTest
*
* Description:
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
* 2.00     22.10.2003   Jan Grewe        angepasst auf asuro.c Ver.2.10
*
* Copyright (c) 2003 DLR Robotics & Mechatronics
*****************************************************************************/
/*****************************************************************************/
/*!
  /file 	SelfTest.c
  /brief 	SelfTest Routinen fuer den Asuro
  /author Jan Grewe, m.a.r.v.i.n

  /version      V001 - 14.08.2003 - Jan Grewe\n
                Initial Release
  /version      V002 - 22.10.2003   Jan Grewe\n
                angepasst auf asuro.c Ver.2.10
  /version      V003 - 18.08.2007 - m.a.r.v.i.n\n
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
#include "test.h"

void SelfTest (void)
{
  unsigned int i;
  Init();
//  for (;;)
  {
    SerPrint("\n\r-- ASURO Testing --\n\r");

    SerPrint("LED Test\n\r");
    LEDTest();

    SerPrint("Line Test\n\r");
    StatusLED(GREEN);
    for (i = 0; i < 0xFE00; i++)
      LineTest();
    StatusLED(OFF);

    SerPrint("Switch Test\n\r");
    for (i = 0; i < 0xFE00; i++)
      SwitchTest();
    Init();
    StatusLED(OFF);

    SerPrint("Odometrie Test\n\r");
    FrontLED(ON);
    for (i = 0; i < 0xFFF0; i++)
      OdometrieTest();
    StatusLED(OFF);
    FrontLED(OFF);

    SerPrint("Motor Test\n\r");
    BackLED(ON,ON);
    MotorTest();
    BackLED(OFF,OFF);

    SerPrint("Serial Test\n\r");
    SerialTest();
  }
}

