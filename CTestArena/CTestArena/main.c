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

void binarytrees()
{
    binary_tree mytree = bt_create_with_values(5, 4, 8, -3, -1, 7);
    
    printf("Is binary tree empty? %s\n", bt_is_empty(mytree) ? "True" : "False");
    
//    bt_print(mytree);
    
    bt_free(mytree);
}

void compare_sizeof()
{
    struct foo {
        int bar;
        char baz;
        void *bort;
        double boot;
    };
    typedef struct foo *foo_ref;
    struct foo myfoo;
    foo_ref myref;
    
    printf("Size of struct foo: %lu\n", sizeof(struct foo));
    printf("Size of foo_ref: %lu\n", sizeof(foo_ref));
    printf("Size of myfoo: %lu\n", sizeof myfoo);
    printf("Size of myref: %lu\n", sizeof myref);
    printf("Size of dereference myref: %lu\n", sizeof *myref);
}

int main(int argc, const char *argv[])
{
    compare_sizeof();
    
    return EXIT_SUCCESS;
}

