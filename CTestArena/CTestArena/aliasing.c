//
//  aliasing.c
//  CTestArena
//
//  Created by Brandon Stansbury on 9/2/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stddef.h>

#define RESTRICT_KW restrict

void one_write(int * RESTRICT_KW a, const int * RESTRICT_KW b, const int * RESTRICT_KW c, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        a[i] = b[i] + c[i];
    }
}

// restrict omits a movl
void sametype_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, int * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}

// restrict has no effect
void mixedtype_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, short * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}

// restrict omits a movl
void void_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, void * RESTRICT_KW val)
{
    int *int_val = val;
    *a += *int_val;
    *b += *int_val;
}

// restrict omits a movsbl
void char_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, char * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}