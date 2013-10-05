//
//  binary_tree.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

struct bt_node {
    int value;
    struct bt_node *left;
    struct bt_node *right;
};

static int foo(void)
{
    return 8;
}

binary_tree bt_make_tree(void)
{
    int butt = foo();
    printf("Called make tree %d", butt);
    return NULL;
}
