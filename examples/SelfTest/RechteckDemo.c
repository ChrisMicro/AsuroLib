/*******************************************************************************
*
* File Name:   RechteckDemo.c
* Project  :   Demo
*
* Description: This file contains RechteckDemo
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
* 2.00     22.10.2003   Jan Grewe    angepasst auf asuro.c Ver.2.10
* 2.70     06.04.2007   m.a.r.v.i.n  angepaﬂt an AsuroLib V2.7.0 
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

#define LEFT 0
#define RIGHT 1
#define LINE 0
#define EDGE 1
/*
SIGNAL (SIG_ADC)
{
  static unsigned char tmp[2],flag[2],toggle;
  static unsigned char state = LINE, posFlag[2] =
                                 {
                                   FALSE,FALSE
                                 };
  static unsigned char pos[2] =
    {
      0,0
    };
  static unsigned char rightSpeed = 200, leftSpeed = 200;

  tmp[toggle]= ADCH;

  if (toggle)	ADMUX = (1 <<ADLAR) | (1 <<REFS0) | WHEEL_RIGHT;
  else ADMUX = (1 <<ADLAR) | (1 <<REFS0) | WHEEL_LEFT;

  if ( (tmp[toggle] < 128) && (flag[toggle] == TRUE))
  {
    pos[toggle] ++;
    flag[toggle] = FALSE;
  }
  if ( (tmp[toggle] > 128) && (flag[toggle] == FALSE))
  {
    pos[toggle] ++;
    flag[toggle] = TRUE;
  }
  toggle ^= 1;

  if (state == LINE)
  {
    if (pos[LEFT]  > 100)
    {
      leftSpeed = 0;
      pos[LEFT] = 0;
      posFlag[LEFT] = TRUE;
    }
    if (pos[RIGHT] > 100)
    {
      rightSpeed = 0;
      pos[RIGHT] = 0;
      posFlag[RIGHT] = TRUE;
    }
    if (posFlag[RIGHT] == TRUE && posFlag[LEFT] == TRUE)
    {
      state = EDGE;
      leftSpeed = 180;
    }
  }
  if (state == EDGE)
  {
    if (pos[LEFT]  > 50)
    {
      leftSpeed = 0;
      pos[LEFT] = 0;
      posFlag[LEFT] = posFlag[RIGHT] = FALSE;
      state = LINE;
      leftSpeed = rightSpeed = 200;
    }
  }
  MotorSpeed(leftSpeed,rightSpeed);
}
*/

void RechteckDemo(void)
{
  int i;

  Init();
  EncoderInit();

  SerPrint("RechteckDemo\r\n");
  for(i=0; i<4; i++)
  {	  
    Go(200, 200);
    Turn(90,200);
  }
  return;	  
}

/*  
  cli();
  MotorSpeed(200,200);
  DDRC &= ~ ((1<<PC0) | (1<<PC1)); // Input => no break LED
  ODOMETRIE_LED_ON;
  ADCSRA = (1<<ADEN) | (1<<ADFR) | (1<<ADIE) | (1<<ADSC) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); // clk/128
  ADMUX = (1<<ADLAR) | (1<<REFS0) | WHEEL_LEFT; // AVCC reference with external capacitor
  sei();
  for (;;);
}
*/

#ifdef STAND_ALONE
int main(void)
{
  Init();
  while(1)
  {  
    ReckteckDemo();
  }
  return 0;
}
#endif

