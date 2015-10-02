/*******************************************************************************
*
* File Name:   Test.c
* Project  :   SelfTest
*
* Description: This file contains all Test functions
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
* 2.00     22.10.2003   Jan Grewe        adapted to asuro.c Ver.2.10
* 2.01     19.11.2003   Jan Grewe        Serial Test changed (data += 1)
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

/* ----------------------------------------- */
/* -------------- Serial Test -------------- */
/*   ASURO sends recieved data+1 directly    */
/* when TIMEOUT occures ASURO is sending 'T' */
/* ----------------------------------------- */
void SerialTest(void)
{
  unsigned char data;
  unsigned char i;
  for (i = 0; i < 0xFE; i++)
  {
    StatusLED(GREEN);
    SerRead(&data,1,0xFFFE);
    StatusLED(RED);
    if (data != 'T') data += 1;
    SerWrite(&data,1);
  }
}
/* END Serial Test -------------------------- */

/* ---------------------- */
/* ----- Switch Test ---- */
/* K1 -> Status LED Green */
/* K2 -> Status LED RED   */
/* K3 -> Line LED         */
/* K4 -> Break LED Left   */
/* K5 -> Break LED Rigth  */
/* K6 -> Motor Left       */
/* ---------------------- */
void SwitchTest(void)
{
  unsigned char sw,tmp;
  MotorDir(FWD,BREAK);

  sw = PollSwitch();
  if (sw)
  {
    StatusLED(OFF);
    FrontLED(OFF);
    BackLED(OFF,OFF);
    MotorSpeed(0,0);
    tmp = 0;

    if (sw & 0x01)
        MotorSpeed(200,0);
    if (sw & 0x02)
    {
        BackLED(OFF,ON);
        tmp = ON;
    }
    if (sw & 0x04)
        BackLED(ON,tmp);
    if (sw & 0x08)
        FrontLED(ON);
    if (sw & 0x10)
        RED_LED_ON;
    if (sw & 0x20)
        GREEN_LED_ON;
  }
  else
    Msleep(10);
}
/* END Switch Test ------------------------------ */

/* ---------------------------------------------- */
/* ------------ Line Sensor Test ---------------- */
/* Left Sensor -> Left Break LED ON when Light on
   Left Phototransistor bright enough             */
/* Right Sensor -> Right Break LED ON when Light on
   Right Phototransistor bright enough            */

void LineTest(void)
{
  unsigned int data[2];
  unsigned char tmp[2] = {OFF,OFF};

  LineData(data);
  if (data[0] > 400)
    tmp[0] = ON;
  if (data[1] > 400)
    tmp[1] = ON;
  BackLED(tmp[0],tmp[1]);
}
/* END Line Sensor Test ------------------------- */

/* ---------------------------------------------- */
/* ---------- Odometrie Sensor Test ------------- */
/* Left Sensor -> Status LED GREEN ON when Light on
   Left Phototransistor bright enough             */
/* Right Sensor -> Status LED RED ON when Light on
   Right Phototransistor bright enough            */
void OdometrieTest(void)
{
  unsigned int data[2];

  OdometryData(data);
  StatusLED(OFF);
  if (data[0] < 512)
    StatusLED(GREEN);
  if (data[1] < 512)
    StatusLED(RED);
}
/* END Odometrie Sensor Test ------------------- */

/* --------------------------------- */
/* ---------- Motor Test ----------- */
/* Motor Left forward to max. speed  */
/* Motor Left rewind  to max. speed  */
/* Motor Right forward to max. speed */
/* Motor Right rewind  to max. speed */
/* Both Motors forward to max. speed */
/* Both Motors rewind to max. speed  */
void MotorTestRight (void)
{
  unsigned int speed;

  MotorDir(BREAK,FWD);
  for (speed = 0; speed < 0xFF; speed ++)
  {
    MotorSpeed(0,speed);
	Msleep(10);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(0,speed);
	Msleep(10);
  }

  MotorDir(BREAK,RWD);
  for (speed = 0; speed < 0xFF; speed ++)
  {
    MotorSpeed(0,speed);
	Msleep(10);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(0,speed);
	Msleep(10);
  }
}

void MotorTestLeft (void)
{
  unsigned int speed;

  MotorDir(FWD,BREAK);
  for (speed = 0; speed < 0xFF; speed ++)
  {
	Msleep(10);
    MotorSpeed(speed,0);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(speed,0);
	Msleep(10);
  }

  MotorDir(RWD,BREAK);
  for (speed = 0; speed < 0xFF; speed ++)
  {
    MotorSpeed(speed,0);
	Msleep(10);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(speed,0);
	Msleep(10);
  }
}

void MotorTestBoth (void)
{
  unsigned int speed;

  MotorDir(FWD,FWD);
  for (speed = 0; speed < 0xFF; speed ++)
  {
    MotorSpeed(speed,speed);
	Msleep(10);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(speed,speed);
	Msleep(10);
  }

  MotorDir(RWD,RWD);
  for (speed = 0; speed < 0xFF; speed ++)
  {
    MotorSpeed(speed,speed);
	Msleep(10);
  }
  for (speed = 0xFF; speed > 0; speed --)
  {
    MotorSpeed(speed,speed);
	Msleep(10);
  }
  MotorSpeed(0,0);
}

void MotorTest(void)
{
  MotorTestLeft();
  MotorTestRight();
  MotorTestBoth();
}
/* ---------------------------------------------- */

/* ------------- LED Test ----------- */
/* Switch On and Off all visible LEDs */
/* Status LED GREEN,RED               */
/* Line LED							  */
/* Break LEDs						  */
void LEDTest (void)
{
  StatusLED(GREEN);
  BackLED(OFF,OFF);
  FrontLED(OFF);
  Msleep(3000);
  StatusLED(RED);
  Msleep(3000);
  StatusLED(OFF);
  FrontLED(ON);
  Msleep(3000);
  BackLED(ON,OFF);
  FrontLED(OFF);
  Msleep(3000);
  BackLED(OFF,ON);
  Msleep(3000);
  BackLED(ON,ON);
  StatusLED(YELLOW);
  FrontLED(ON);
  Msleep(3000);
  BackLED(OFF,OFF);
  StatusLED(OFF);
  FrontLED(OFF);
}
/* END LED Test --------------------- */

