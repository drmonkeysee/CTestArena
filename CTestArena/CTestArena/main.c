//
//  main.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdio.h>

#include "binary_tree.h"

#define B_TO_S(b) (b ? "True" : "False")

int main(int argc, const char *argv[])
{
    binary_tree mytree = bt_create_tree();
    _Bool empty = bt_is_empty(mytree);
    printf("Is binary tree empty? %s\n", B_TO_S(empty));
    printf("Hello, World!\n");
    return 0;
}

