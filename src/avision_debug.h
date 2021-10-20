/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Serial debug
*
* Created by       :        Arnold Velzel
* Created on       :        08-09-2021
*
*******************************************************************************/
#include "avision_system.h"

#ifndef __DEBUG_H__
#define __DEBUG_H__

#define SERIAL_BAUDRATE 115200 // 921600 - programming baudrate

void dbg(String s);
void dbgln(String s);
void initDebug(bool active);

#endif
