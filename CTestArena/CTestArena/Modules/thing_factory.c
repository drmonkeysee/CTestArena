//
//  thing_factory.c
//  CTestArena
//
//  Created by Brandon Stansbury on 4/1/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include "thing_factory.h"

struct thing create_thing(void)
{
    return (struct thing){ "real thing", 84 };
}