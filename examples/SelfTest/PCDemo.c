/*******************************************************************************
*
* File Name:   PCDemo.c
* Project  :   Demo
*
* Description: This file contains PCDemo (ASURO can be controlled over IR-Transceiver)
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
#include <stdlib.h>

#define OFFSET	0x3F
#define STEP	5

#define RWD_KEY   '2'
#define FWD_KEY   '8'
#define LEFT_KEY  '4'
#define RIGHT_KEY '6'
#define STOP_KEY  '5'
#define ESC_KEY   0x1B   // Programm Exit mit Escape Taste



//volatile unsigned char switchPressed;
int speedLeft,speedRight;
/*
SIGNAL (SIG_INTERRUPT1)
{
  unsigned int i;

  DDRD |= SWITCHES;				// Switches as Output
  SWITCH_ON;						// Output HIGH for measurement
  ADMUX = (1 << REFS0) | SWITCH;	// AVCC reference with external capacitor
  for (i = 0; i < 0xFE; i++);

  ADCSRA |= (1 << ADSC);			// Start conversion
  while (!(ADCSRA & (1 << ADIF)));	// wait for conversion complete
  ADCSRA |= (1 << ADIF);			// clear ADCIF
  i = ADCL + (ADCH << 8);

  // und ab gehts --- fahr zurück
  MotorDir(RWD,RWD);
  MotorSpeed(200,200);
  FrontLED(ON);
  BackLED(ON,ON);
  for (i = 0; i < 0xFFFD; i++);   // Sleep does not work here

  switchPressed = TRUE;
  SWITCH_OFF;
  DDRD &= ~SWITCHES;					// Switches as Input => ext. Int 1
}
*/
void PCFwd(void)
{
  speedRight += STEP;
  speedLeft  += STEP;
  if (speedLeft < 0 && speedLeft >= -OFFSET) speedLeft = 1;
  if (speedRight < 0 && speedRight >= -OFFSET) speedRight = 1;
  FrontLED(ON);
  BackLED(OFF,OFF);
}

void PCRwd(void)
{
  speedRight -= STEP;
  speedLeft  -= STEP;
  if (speedRight > 0 && speedRight <= OFFSET)  speedRight = -1;
  if (speedLeft > 0 && speedLeft <= OFFSET)  speedLeft = -1;
  FrontLED(OFF);
  BackLED(ON,ON);
}

void PCLeft (void)
{
  speedLeft  -= STEP;
  if (speedLeft > 0 && speedLeft <= OFFSET) speedLeft = -1;
  speedRight += STEP;
  if (speedRight < 0 && speedRight >= -OFFSET) speedRight = 1;
  FrontLED(OFF);
  BackLED(ON,OFF);
}

void PCRight (void)
{
  speedLeft  += STEP;
  if (speedLeft < 0 && speedLeft >= -OFFSET) speedLeft = 1;
  speedRight -= STEP;
  if (speedRight > 0 && speedRight <= OFFSET) speedRight = -1;
  FrontLED(OFF);
  BackLED(OFF,ON);
}


void PCStop(void)
{
  speedRight = speedLeft = 0;
  FrontLED(OFF);
  BackLED(OFF,OFF);
}


void PCDemo(void)
{
  unsigned char cmd;
  unsigned char leftDir = FWD, rightDir = FWD;

  Init();
  SerPrint("PCDemo\r\n");
  StartSwitch();
  sei();
  for (;;)
  {
    cmd = 0;
    SerRead(&cmd,1,0xFFFE);
    switch (cmd)
    {
    case RWD_KEY :
      PCRwd();
      break;
    case FWD_KEY :
      PCFwd();
      break;
    case LEFT_KEY :
      PCLeft();
      break;
    case RIGHT_KEY :
      PCRight();
      break;
    case STOP_KEY :
      PCStop();
      break;
    case ESC_KEY :
      return;
      break;
    }
    if (speedLeft > 0 && speedLeft <  OFFSET) speedLeft += OFFSET;
    if (speedLeft < 0 && speedLeft > -OFFSET) speedLeft -= OFFSET;
    if (speedRight > 0 && speedRight <  OFFSET) speedRight += OFFSET;
    if (speedRight < 0 && speedRight > -OFFSET) speedRight -= OFFSET;

    if (switched)
    {
      speedLeft  = 0;
      speedRight = 0;
      switched = FALSE;
  // und ab gehts --- fahr zurück
      MotorDir(RWD,RWD);
      MotorSpeed(200,200);
      FrontLED(ON);
      BackLED(ON,ON);
      Msleep(1000);
    }

    leftDir = rightDir = FWD;
    if (speedLeft < 0)  leftDir = RWD;
    if (speedRight < 0) rightDir = RWD;

    if (speedLeft >   255) speedLeft  =  255;
    if (speedLeft <  -255) speedLeft  = -255;
    if (speedRight >  255) speedRight =  255;
    if (speedRight < -255) speedRight = -255;

    MotorDir(leftDir,rightDir);
    MotorSpeed(abs(speedLeft),abs(speedRight));
  }
}

#ifdef STAND_ALONE
int main(void)
{
  Init();
  while(1)
  {  
    PCDemo();
  }
  return 0;
}
#endif

