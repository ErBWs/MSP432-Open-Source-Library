/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "debug.h"

static volatile uint8_t assertEnable = 1;

/*!
 * @brief       Enable Assert
 *
 * @param       None
 * @return      None
 */
void EnableAssert(void)
{
    assertEnable = 1;
}


/*!
 * @brief       Disable Assert
 *
 * @param       None
 * @return      None
 */
void DisableAssert(void)
{
    assertEnable = 0;
}


/*!
 * @brief       Assert handler
 *
 * @param       logic       Input logical value to decide whether trigger assert or not
 * @param       *file       File name where wrong assert is triggered
 * @param       line        Number of line where wrong assert is triggered
 * @return      None
 *
 * @note        Use the definition in debug.h
 */
void AssertHandler(uint8_t logic, char *file, int line)
{
    if (logic || !assertEnable)
        return;

    while (1)
    {
        // Trap the program in this infinite loop
        // and output error message on screen if screen is connected

    }
}