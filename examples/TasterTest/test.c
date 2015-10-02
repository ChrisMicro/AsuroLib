/***********************************************************************
 *
 * File Name:   tastsensor.c
 * Project  :   ASURO
 *
 * Description: Test der Tastensensoren
 *
 * Ver.     Date         Author           Comments
 * -------  ----------   --------------   ------------------------------
 * 1.0      10.09.2005   m.a.r.v.i.n      initial build
 * 1.1      08.01.2006   m.a.r.v.i.n      2x PollSwitch + Vergleich, anstelle 8x PollSwitch
 *
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include <stdlib.h>
#include "asuro.h"

int main(void)
{
  uint8_t t1, t2;
  char text[16];

  Init();
  SerPrint("\r\nTastsensor Test\r\n");
  while (1)
  {
    t1 = PollSwitch();
    t2 = PollSwitch();
    if (t1 && t2 && t1 == t2)              /* irgendeine Taste gedrueckt */
    {
      itoa(t1, text, 10);     /* Tastenwert senden */
      SerPrint(text);
      SerPrint("\r\n"); /* Zeilenvorschub */
    }
    Msleep(500);
  }
}
