/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdint.h>

void EnableAssert();
void DisableAssert();
void AssertHandler(uint8_t logic, char *file, int line);

#define Assert(x)       (AssertHandler((x), __FILE__, __LINE__))

#endif
