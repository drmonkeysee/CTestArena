//
//  aliasing.c
//  CTestArena
//
//  Created by Brandon Stansbury on 9/2/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stddef.h>

void one_write(int * restrict a, const int * restrict b, const int * restrict c, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        a[i] = b[i] + c[i];
    }
}
