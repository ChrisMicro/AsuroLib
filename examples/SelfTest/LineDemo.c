/*******************************************************************************
*
* File Name:   LineDemo.c
* Project  :   Demo
*
* Description: This file contains LineDemo features
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
* 2.00     22.10.2003   Jan Grewe        angepasst auf asuro.c Ver.2.10
*
* Copyright (c) 2003 DLR Robotics & Mechatronics
*****************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/
#include "asuro.h"

#define SPEED  0x8F

int speedLeft,speedRight;
unsigned int lineData[2];
int ADOffset;

void LineLeft (void)
{
  speedLeft  += 1;
  if (speedLeft > 0xFE) speedLeft = 0xFF;
}

void LineRight (void)
{
  speedRight  += 1;
  if (speedRight > 0xFE) speedRight = 0xFF;
}

void LineDemo(void)
{
  int i;
  unsigned char j;

  Init();

  SerPrint("LineDemo\r\n");
  FrontLED(ON);
  for (j = 0; j < 0xFF; j++) LineData(lineData);
  LineData(lineData);
  ADOffset = lineData[0] - lineData[1];
  speedLeft = speedRight = SPEED;
  for (;;)
  {
    LineData(lineData);
    i = (lineData[0] - lineData[1]) - ADOffset;
    if ( i > 4)
    {
      StatusLED(GREEN);
      LineLeft();
    }
    else if ( i < -4)
    {
      StatusLED(RED);
      LineRight();
    }
    else
    {
      StatusLED(OFF);
      speedLeft = speedRight = SPEED;
    }
    MotorSpeed(speedLeft,speedRight);
    if (PollSwitch())
      return;
  }
}

#ifdef STAND_ALONE
int main(void)
{
  Init();
  while(1)
  {  
    LineDemo();
  }
  return 0;
}
#endif

