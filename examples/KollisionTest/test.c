/***************************************************************************
 *
 * File Name:   kollisiontest.c
 * Project  :   ASURO
 *
 * Description: Kollisionstest mit Hilfe der Tastensensoren
 *
 * Ver.     Date         Author               Comments
 * -------  ----------   -----------------    ------------------------------
 * 1.0      10.09.2005   m.a.r.v.i.n          initial build
 * 1.1      08.01.2006   m.a.r.v.i.n          2x PollSwitch + Vergleich,
 *                                            anstelle 8x PollSwitch
 *
 * benoetigt die modifizierte Asuro Bibliothek 'asuro.c'
 * von waste, stochri und andun. Zu finden bei www.roboternetz.de
 */
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   any later version.                                                    *
 ***************************************************************************/

#include "asuro.h"

#define FULL_L 250
#define FULL_R 220

/* Motor vorw�rts */
void MotorFwd(void)
{
  MotorDir(FWD,FWD);
  MotorSpeed(FULL_L,FULL_R);
}

/* Motor r�ckw�rts */
void MotorRwd(void)
{
  MotorDir(RWD,RWD);
  MotorSpeed(FULL_L,FULL_R);
}

/* Motor r�ckw�rts Links */
void MotorRwdL(void)
{
  MotorDir(RWD,RWD);
  MotorSpeed(FULL_L,0);
}

/* Motor r�ckw�rts Rechts */
void MotorRwdR(void)
{
  MotorDir(RWD,RWD);
  MotorSpeed(0, FULL_R);
}

/* Motor stop */
void MotorStop(void)
{
  MotorSpeed(0,0);
}

int main(void)
{
  unsigned char t1, t2;

  Init();
  while (1)
  {
    t1 = PollSwitch();
    t2 = PollSwitch();
    if (t1 == 0 && t2 == 0)         /* keine Taste */
    {
      MotorFwd();          /* vorw�rts fahren */
      FrontLED(ON);
      BackLED(OFF,OFF);
    }
    else if (t1 && t2 && t1 == t2)
    {
      MotorStop();
      if (t1 & 0x07) /* Tasten links gedr�ckt? */
      {
        MotorRwdL();       /* R�ckw�rtskurve links fahren */
        FrontLED(OFF);
        BackLED(ON,OFF);
      }
      if (t1 & 0x38) /* Tasten rechts gedr�ckt? */
      {
        MotorRwdR();       /* R�ckw�rtskurve rechts fahren */
        FrontLED(OFF);
        BackLED(OFF,ON);
      }
      Msleep(1000);        /* 1 Sekunde fahren */
    }
  }
  return 0;
}

