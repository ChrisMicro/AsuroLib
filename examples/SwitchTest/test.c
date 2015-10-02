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
  unsigned int sw;
  char text[10];
  Init();

  SerPrint("\r\nSwitch Test\r\n"); 
  while (1)
  {
    if (PollSwitch())
    {  
      sw = PollSwitch();
      SerPrint("\r\nSwitch= ");
      itoa (sw, text, 2);

      SerPrint(text);
    }
    Msleep(500);
  }  
  return 0;
}
