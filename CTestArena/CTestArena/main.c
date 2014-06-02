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
    printf("Empty tree size: %lu\n", bt_size(empty_tree));
    printf("Empty tree depth: %lu\n", bt_depth(empty_tree));
    printf("Empty tree contains 3?: %s\n", bt_contains(empty_tree, 3) ? "Yes" : "No");
    bt_free(empty_tree);
    
    printf("New tree:\n");
    binary_tree my_tree = bt_create_with_values(9, 8, 5, 10, 3, 4, 12, 9, 15, 2);
    bt_print(my_tree);
    printf("Tree size: %lu\n", bt_size(my_tree));
    printf("Tree depth: %lu\n", bt_depth(my_tree));
    printf("Tree contains 12?: %s\n", bt_contains(my_tree, 12) ? "Yes" : "No");
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
    printf("Final tree size: %lu\n", bt_size(my_tree));
    printf("Final tree depth: %lu\n", bt_depth(my_tree));
    printf("Final tree contains 12?: %s\n", bt_contains(my_tree, 12) ? "Yes" : "No");
    bt_free(my_tree);
    
    binary_tree wack_tree = bt_create_with_values(12, 1, 2, 3, 6, 5, 4, 10, 11, 12, 13, 14, 15);
    printf("This tree is wack:\n");
    bt_print(wack_tree);
    bt_rebalance(&wack_tree);
    printf("The wack tree has been rebalanced:\n");
    bt_print(wack_tree);
    bt_free(wack_tree);
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

typedef struct blah {
    int value;
} Blah;
void const_params(const Blah *c_blah, Blah * const cp_blah)
{
//    c_blah->value = 28;
    c_blah = NULL;
    cp_blah->value = 100;
//    cp_blah = NULL;
}
void const_typedefs(void)
{
    // these declarations are equivalent
    // effectively const pointer
    // can't do pointer to const tree but no need since tree definition is not available
//    const binary_tree ct_tree = bt_create();
//    binary_tree const tc_tree = bt_create();
//    ct_tree = bt_create();
//    tc_tree = bt_create();
    Blah v_blah = { 12 };
    const Blah *c_blah = &v_blah;
//    c_blah->value = 40; can't do this
    c_blah = NULL;
    Blah * const cp_blah = &v_blah;
    cp_blah->value = 20;
//    cp_blah = NULL; can't do this
    printf("Blah is %d\n", v_blah.value);
    const_params(&v_blah, &v_blah);
    printf("Blah is now %d\n", v_blah.value);
}

_Thread_local int p;

#define pick_thing(v) _Generic(v, int: "foobar", const int: "blarg", volatile int: "bort", _Atomic int: "food", const volatile int: "spim", const _Atomic int: "boo", volatile _Atomic int: "mood", const volatile _Atomic int: "doom")
void generic_variants(void)
{
    int b = 5;
    const char *s = pick_thing(b);
    
    const int c = 10;
    const char *s2 = pick_thing(c);
    
    volatile int d = 10;
    const char *s3 = pick_thing(d);
    
    _Atomic int e = 10;
    const char *s4 = pick_thing(e);
    
    volatile const int f = 10;
    const char *s5 = pick_thing(f);
    
    const volatile int g = 10;
    const char *s6 = pick_thing(g);
    
    const _Atomic int h = 10;
    const char *s7 = pick_thing(h);
    
    volatile _Atomic int i = 10;
    const char *s8 = pick_thing(i);
    
    const volatile _Atomic int j = 10;
    const char *s9 = pick_thing(j);
    
    extern int k;
    const char *s10 = pick_thing(k);
    
    register int l = 10;
    const char *s11 = pick_thing(l);
    
    static int m = 10;
    const char *s12 = pick_thing(m);
    
    _Alignas(long) int n = 10;
    const char *s13 = pick_thing(n);
    
    auto int o = 10;
    const char *s14 = pick_thing(o);
    
    p = 10;
    const char *s15 = pick_thing(p);
}

int main(int argc, const char *argv[])
{
    binarytrees();
    compare_sizeof();
    reassign_struct_member();
    modify_pointer_arg();
    const_typedefs();
    
    return EXIT_SUCCESS;
}

