/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"
#include "ultrasonic.h"

int abstand=0;

int main(void)
{
  Init();
  SerPrint("\r\n  --- ultrasonic test ---");
  Msleep(1000);
 
  do
  {
    abstand = Chirp();
    SerPrint("\r\n distanz in cm: ");
    Msleep(500);
    PrintInt(abstand);
  }
  while(1);
  return 0;
} 


