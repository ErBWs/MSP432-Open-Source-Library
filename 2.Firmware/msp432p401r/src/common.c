/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "common.h"

/*!
 * @brief   Check for Little-Endian or Big-Endian
 *
 * @param   void
 * @return  0 for Big-Endian
 *          1 for Little-Endian
 */
int CheckEndianness()
{
    unsigned int x = 1;
    char *c = (char *) &x;
    return (int) *c;
}