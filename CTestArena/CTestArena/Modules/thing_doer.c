//
//  thing_doer.c
//  CTestArena
//
//  Created by Brandon Stansbury on 4/1/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

#include "thing_doer.h"
#include "thing_factory.h"
#include "thing_display.h"

void do_a_thing(void)
{
    struct thing my_thing = create_thing();
    display_thing(my_thing);
}
