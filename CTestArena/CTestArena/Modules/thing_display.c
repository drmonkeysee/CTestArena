//
//  thing_display.c
//  CTestArena
//
//  Created by Brandon Stansbury on 4/1/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stdio.h>
#include "thing_display.h"
#include "thing_factory.h"

int display_thing(struct thing a_thing)
{
    printf("displayed a thing named %s with value %d\n", a_thing.name, a_thing.value);
    return 8;
}