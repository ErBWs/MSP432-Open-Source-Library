/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void func_int_to_str (char *str, int32_t number);
void func_uint_to_str (char *str, uint32_t number);
void func_float_to_str (char *str, float number, uint8_t point_bit);

#ifdef __cplusplus
}
#endif

#endif
