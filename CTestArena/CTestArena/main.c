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

void binarytrees(void)
{
    printf("-- binarytrees --\n");
}

void compare_sizeof(void)
{
    printf("-- compare_sizeof --\n");
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

void reassign_struct_member(void)
{
    printf("-- reassign_struct_member --\n");
    struct node {
        int value;
        struct node *child;
    };
    struct node a_child = { .value = 9 };
    struct node parent = { .value = 5, .child = &a_child };
    printf("Parent: %d --> %d\n", parent.value, parent.child->value);
    
    struct node **parent_child = &parent.child;
    struct node another_child = { .value = 40 };
    *parent_child = &another_child;
    printf("Parent after child reassignment: %d --> %d\n", parent.value, parent.child->value);
    
    int *parent_value = &parent.value;
    *parent_value = 12;
    printf("Parent after value reassignment: %d --> %d\n", parent.value, parent.child->value);
}

int main(int argc, const char *argv[])
{
    binarytrees();
    compare_sizeof();
    reassign_struct_member();
    
    return EXIT_SUCCESS;
}

