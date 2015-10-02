/*******************************************************************************
*
* File Name:   IRDemo.c
* Project  :   Demo
*
* Description: This file contains IRDemo features
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
* 2.00     22.10.2003   Jan Grewe        angepasst auf asuro.c Ver.2.10
*
* Copyright (c) 2003 DLR Robotics & Mechatronics
*****************************************************************************/
/*!
  /file 	IRDemo.c
  /brief 	Routinen fuer die Dekodierung von RC5-Fernbedienungs-Codes
  /author 	Benjamin Benz (bbe@heise.de), m.a.r.v.i.n

  /version      V001 - 14.08.2003 - Jan Grewe
                initial build
		V002 - 22.10.2003 - Jan Grewe
                angepasst auf asuro.c Ver.2.10
                V003 - 11.02.2007 - m.a.r.v.i.n
		c't-Bot RC5 Code portiert fuer den ASURO
*/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"
#include "rc5.h"
#include <stdlib.h>

#define DIARWD   0x1008
#define DIAFWD   0x1002
#define DIALEFT  0x1004
#define DIARIGHT 0x1006
#define DIASTOP  0x1029
#define DIAPOWER 0x103D


#define TUNERRWD   0x1021
#define TUNERFWD   0x1020
#define TUNERLEFT  0x1011
#define TUNERRIGHT 0x1010
#define TUNERSTOP  0x1025
#define TUNERPOWER 0x100C

#define OFFSET	0x3F
#define STEP	5

int speedLeft,speedRight;

void IRFwd(void)
{
  speedRight += STEP;
  speedLeft  += STEP;
  if (speedLeft < 0 && speedLeft >= -OFFSET) speedLeft = 1;
  if (speedRight < 0 && speedRight >= -OFFSET) speedRight = 1;
  FrontLED(ON);
  BackLED(OFF,OFF);
}

void IRRwd(void)
{
  speedRight -= STEP;
  speedLeft  -= STEP;
  if (speedRight > 0 && speedRight <= OFFSET)  speedRight = -1;
  if (speedLeft > 0 && speedLeft <= OFFSET)  speedLeft = -1;
  FrontLED(OFF);
  BackLED(ON,ON);
}

void IRLeft (void)
{
  speedLeft  -= STEP;
  if (speedLeft > 0 && speedLeft <= OFFSET) speedLeft = -1;
  speedRight += STEP;
  if (speedRight < 0 && speedRight >= -OFFSET) speedRight = 1;
  FrontLED(OFF);
  BackLED(ON,OFF);
}

void IRRight (void)
{
  speedLeft  += STEP;
  if (speedLeft < 0 && speedLeft >= -OFFSET) speedLeft = 1;
  speedRight -= STEP;
  if (speedRight > 0 && speedRight <= OFFSET) speedRight = -1;
  FrontLED(OFF);
  BackLED(OFF,ON);
}


void IRStop(void)
{
  speedRight = speedLeft = 0;
  FrontLED(OFF);
  BackLED(OFF,OFF);
}

int IRDemo(void)
{

  static unsigned int cmd;
  unsigned char leftDir = FWD, rightDir = FWD;
  char text[7];

  Init();
  InitRC5();

  SerPrint("RC5 Test\r\n");
  while (1)
  {
    cmd = ReadRC5();
    if (cmd)
    {
      cmd &= RC5_MASK;
      itoa(cmd, text, 16);
      SerPrint(text);
      SerPrint("\r\n");

      switch (cmd)
      {
      case TUNERRWD :
      case DIARWD :
        IRRwd();
        break;
      case TUNERFWD :
      case DIAFWD :
        IRFwd();
        break;
      case TUNERLEFT :
      case DIALEFT:
        IRLeft();
        break;
      case TUNERRIGHT :
      case DIARIGHT:
        IRRight();
        break;
      case TUNERSTOP :
      case DIASTOP :
        IRStop();
        break;
      case TUNERPOWER :
      case DIAPOWER :
        return 0;
        break;
      }
    }
    if (speedLeft > 0 && speedLeft <  OFFSET) speedLeft += OFFSET;
    if (speedLeft < 0 && speedLeft > -OFFSET) speedLeft -= OFFSET;
    if (speedRight > 0 && speedRight <  OFFSET) speedRight += OFFSET;
    if (speedRight < 0 && speedRight > -OFFSET) speedRight -= OFFSET;

    leftDir = rightDir = FWD;
    if (speedLeft < 0)  leftDir = RWD;
    if (speedRight < 0) rightDir = RWD;

    if (speedLeft >   255) speedLeft  =  255;
    if (speedLeft <  -255) speedLeft  = -255;
    if (speedRight >  255) speedRight =  255;
    if (speedRight < -255) speedRight = -255;

    MotorDir(leftDir,rightDir);
    MotorSpeed(abs(speedLeft),abs(speedRight));
    Msleep(100);
  }
  return 0;
}

#ifdef STAND_ALONE
int main(void)
{
  Init();
  while(1)
  {  
    IRDemo();
  }
  return 0;
}
#endif

