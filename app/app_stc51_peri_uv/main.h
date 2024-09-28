/*
 * main.h:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5.
 */
#ifndef __MAIN_H_
#define __MAIN_H_

#include <reg52.h>

#ifndef __cplusplus /* In C++, 'bool', 'true' and 'false' and keywords */
#define bool char
#define true 1
#define TRUE true
#define false 0
#define FALSE false

#define uint8_t unsigned char
#define uint16_t unsigned short int
#define uint32_t unsigned int 

#define int8_t signed char
#define int16_t short int
#define int32_t int

#else
#ifdef __GNUC__
/* GNU C++ supports direct inclusion of stdbool.h to provide C99
        compatibility by defining _Bool */
#define _Bool bool
#endif
#endif

#endif /* __MAIN_H_ */
