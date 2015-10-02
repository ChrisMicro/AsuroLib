/*******************************************************************************
*
* Description: Asuro IR-Detektor Testprogramm
*
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

static unsigned char ocr2 = 0x91;

void InitIRDetect(void)
{  
  UCSRB = 0;
  DDRD |= (1 << DDD1);	// Port D1 als Ausgang
  PORTD &= ~(1 << PD1);	// PD1 auf LOW
  OCR2 = ocr2;
}

void InitUart(void)
{
  OCR2  = 0x91;         // duty cycle fuer 36kHz
}

int main(void)
{

  unsigned char sw;

  Init();
  
  DDRD |= (1 << DDD1);	// Port D1 als Ausgang
  PORTD &= ~(1 << PD1);	// PD1 auf LOW

//  InitIRDetect();
  while (1)
  {
    UCSRB = 0;
    OCR2 = 0xFE;

    if (PIND & (1 << PD0))
      StatusLED(GREEN);
    else
      StatusLED(RED);

    sw = PollSwitch();
    if (sw & 0x01)
      ocr2  = 0xFE;	//Pulsbreite 1
    if (sw & 0x02)
      ocr2  = 0xFD;	//Pulsbreite 2
    if (sw & 0x04)
      ocr2  = 0xFB;	//Pulsbreite 4
    if (sw & 0x08)
      ocr2  = 0xF7;	//Pulsbreite 8
    if (sw & 0x10)
      ocr2  = 0xEF;	//Pulsbreite 16
    if (sw & 0x20)
      ocr2  = 0x90;	//Pulsbreite 110

    if (sw)
    {  
      OCR2 = 0x91;
      PrintInt(sw); 
      SerPrint(" ");
      PrintInt(ocr2); 
      SerPrint("\r\n");
    }
//   Msleep(100);
  }
  return 0;
}
