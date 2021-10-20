/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Buzzer functions
*
* Created by       :        Arnold Velzel
* Created on       :        24-09-2021
*
*******************************************************************************/

#include "avision_debug.h"
#include "avision_beep.h"

void beep(unsigned int frequency, int milliseconds, int pause)
{
    if (milliseconds)
    {
        tone(BEEP_BUZZER, frequency, milliseconds);
    }
    if (pause)
    {
        delay(milliseconds + pause);
        noTone(BEEP_BUZZER);
        digitalWrite(BEEP_BUZZER, LOW);
    }
}
void beep(int milliseconds, int pause = 0)
{
    beep(BEEP_FREQUENCY, milliseconds, pause);
}

void initBeep()
{
    pinMode(BEEP_BUZZER, OUTPUT);
    digitalWrite(BEEP_BUZZER, LOW);
    dbgln("Beep initialised");
}
