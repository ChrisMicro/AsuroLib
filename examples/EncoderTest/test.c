/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"

int main(void)
{
  int diff,weg;
  Init();
  EncoderInit();
  StatusLED(OFF);
  MotorDir(FWD,FWD);
  MotorSpeed(175,175);
  StartSwitch();
  unsigned long endtime=Gettime()+8000;
  while (!switched && Gettime()<endtime)
  {
    diff=encoder[RIGHT]-encoder[LEFT];
    MotorSpeed(175+diff,175-diff);
  }
  weg=encoder[0];
  EncoderSet(0,0);
  MotorDir(RWD,RWD);
  MotorSpeed(200,200);
  Msleep(100);
  MotorDir(RWD,FWD);
  weg-=encoder[0];
  EncoderSet(0,0);
  while (encoder[1]<90)
  {
    Msleep(50);
  }
  MotorDir(FWD,FWD);
  EncoderSet(0,0);
  while (encoder[0]<weg)
  {
    diff=encoder[RIGHT]-encoder[LEFT];
    MotorSpeed(175+diff,175-diff);
  }
  MotorSpeed(0,0);
  if (weg>600) StatusLED(GREEN);
  else if (weg>300) StatusLED(YELLOW);
  else StatusLED(RED);
  while (1);
  return 0;
}
