/*******************************************************************************
*
* File Name:   main.c
* Project  :   SelfTest + Demo
*
* Description:
*
* Ver.     Date         Author           Comments
* -------  ----------   --------------   ------------------------------
* 1.00	   14.08.2003   Jan Grewe		 build
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
#include "SelfTest.h"
#include "Demo.h"

int main (void)
{
//  unsigned int  i,data[2];
//  unsigned char count = 0,flag = FALSE;
  Init();
/*
  for (i = 0; i < 0x1FFF; i++)
  {
    OdometrieData(data);
    if ((data[0] <  200) && (flag == TRUE))
    {
      count ++;
      flag = FALSE;
    }
    if (data[0] >= 600) flag = TRUE;
  }
  if (count > 10) Demo();
*/
  while (1)
  {  
    if (PollSwitch())
    {
      while (PollSwitch());
      Demo();
    }
    SelfTest();
  }
  return 0;
}
