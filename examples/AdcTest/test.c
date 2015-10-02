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
  unsigned int battery;
  unsigned int linedata[2];
  unsigned int ododata[2];

  Init();

  SerPrint("\r\nADC Test\r\n");
  while (1)
  {
    battery=Battery();
    SerPrint("\r\nBattery  = ");
    PrintInt(battery);
    LineData(linedata);
    SerPrint("\r\nLine     = ");
    PrintInt(linedata[0]);
    SerPrint(" ,");
    PrintInt(linedata[1]);
    OdometryData(ododata);
    SerPrint("\r\nOdometry = ");
    PrintInt(ododata[0]);
    SerPrint(" ,");
    PrintInt(ododata[1]);
    Msleep(500);
  }
  return 0;
}
