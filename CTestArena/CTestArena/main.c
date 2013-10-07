//
//  main.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

int main(int argc, const char *argv[])
{
    binary_tree mytree = bt_create();

    _Bool empty = bt_is_empty(mytree);
    printf("Is binary tree empty? %s\n", empty ? "True" : "False");
    
    bt_free(mytree);
    
    return EXIT_SUCCESS;
}

