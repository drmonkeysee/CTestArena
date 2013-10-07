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
    binary_tree mytree = bt_create_with_values(5, 4, 8, -3, -1, 7);

    printf("Is binary tree empty? %s\n", bt_is_empty(mytree) ? "True" : "False");
    
    bt_print(mytree);
    
    bt_free(mytree);
    
    return EXIT_SUCCESS;
}

