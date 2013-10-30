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
    printf("Empty tree:\n");
    binary_tree empty_tree = bt_create();
    bt_print(empty_tree);
    printf("Empty tree size: %u\n", bt_size(empty_tree));
    printf("New tree:\n");
    binary_tree my_tree = bt_create_with_values(9, 8, 5, 10, 3, 4, 12, 9, 15, 2);
    bt_print(my_tree);
    printf("Tree size: %u\n", bt_size(my_tree));
    printf("Insert 11:\n");
    bt_insert(&my_tree, 11);
    bt_print(my_tree);
    printf("Insert existing value (10):\n");
    bt_insert(&my_tree, 10);
    bt_print(my_tree);
    printf("Remove leaf node (4):\n");
    bt_remove(&my_tree, 4);
    bt_print(my_tree);
    printf("Remove node with two children (10):\n");
    bt_remove(&my_tree, 10);
    bt_print(my_tree);
    printf("Remove node with left child (3):\n");
    bt_remove(&my_tree, 3);
    bt_print(my_tree);
    printf("Remove node with right child (12):\n");
    bt_remove(&my_tree, 12);
    bt_print(my_tree);
    printf("Final tree size: %u\n", bt_size(my_tree));
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

void change_pointer(int *pointer)
{
    printf("CP: Pointer is %p\n", pointer);
    printf("CP: Pointer points to %d\n", *pointer);
    pointer = malloc(sizeof(int));
    *pointer = 8;
    printf("CP: Pointer is %p\n", pointer);
    printf("CP: Pointer points to %d\n", *pointer);
    free(pointer);
}
void change_pointedto(int *pointer)
{
    printf("CPT: Pointer is %p\n", pointer);
    printf("CPT: Pointer points to %d\n", *pointer);
    int *temp = malloc(sizeof(int));
    *temp = 12;
    printf("CPT: Temp is %p\n", temp);
    printf("CPT: Temp points to %d\n", *temp);
    *pointer = *temp;
    printf("CPT: Pointer is %p\n", pointer);
    printf("CPT: Pointer points to %d\n", *pointer);
    free(temp);
}
void modify_pointer_arg(void)
{
    printf("-- modify_pointer_arg --\n");
    int v = 4;
    int *foo = &v;
    printf("foo is %p\n", foo);
    printf("foo points to %d\n", *foo);
    printf("v is %d\n", v);
    change_pointer(foo);
    printf("foo is %p\n", foo);
    printf("foo points to %d\n", *foo);
    printf("v is %d\n", v);
    change_pointedto(foo);
    printf("foo is %p\n", foo);
    printf("foo points to %d\n", *foo);
    printf("v is %d\n", v);
    // can't do this without a ** parameter
//    foo = NULL;
//    change_pointedto(foo);
}

int main(int argc, const char *argv[])
{
    binarytrees();
    compare_sizeof();
    reassign_struct_member();
    modify_pointer_arg();
    
    return EXIT_SUCCESS;
}

