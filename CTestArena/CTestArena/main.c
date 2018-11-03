//
//  main.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Brandon Stansbury. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "aliasing.h"

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
    struct node a_child = {.value = 9};
    struct node parent = {.value = 5, .child = &a_child};
    printf("Parent: %d --> %d\n", parent.value, parent.child->value);
    
    struct node **parent_child = &parent.child;
    struct node another_child = {.value = 40};
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
    Blah v_blah = {12};
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

#define func(f) _Generic(f, int (*)(char): "blah")

int boot(char c)
{
    return 10;
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
    
    const char *s16 = func(&boot);
//    const char *s17 = func(&const_typedefs);
}

static const char * const pstr = "barfoo";
static const char astr[] = "barfoo";

void string_memory(void)
{
    printf("--string memory--\n");
    printf("string literal is at %p\n", "barfoo");
    printf("string ptr is at %p\n", pstr);
    printf("string array is at %p\n", astr);
}

void regular_array(int foo[], int n)
{
    printf("%s has array value %p\n", __func__, foo);
    printf("%s has array size %zu\n", __func__, sizeof foo);
}

void vlc_array(int n, int foo[n])
{
    printf("%s has array value %p\n", __func__, foo);
    printf("%s has array size %zu\n", __func__, sizeof foo);
}

void static_array(int foo[static 10])
{
    printf("%s has array value %p\n", __func__, foo);
    printf("%s has array size %zu\n", __func__, sizeof foo);
}

void vlcstatic_array(int n, int foo[static n])
{
    printf("%s has array value %p\n", __func__, foo);
    printf("%s has array size %zu\n", __func__, sizeof foo);
}

void const_array(const int foo[const])
{
    //foo[1] = 5;
    //foo = (int []){1, 2, 4};
}

int *make_array(size_t size)
{
    int *foo = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; ++i) {
        foo[i] = (int)i;
    }
    return foo;
}

void array_params(void)
{
    printf("--array params--\n");
    
    int foo[5];
    regular_array(foo, 5);
    vlc_array(5, foo);
    static_array(foo);
    vlcstatic_array(5, foo);
    
    int bar[10];
    regular_array(bar, 10);
    vlc_array(2, bar);
    static_array(bar);
    vlcstatic_array(5, bar);
    
    regular_array(NULL, 0);
    vlc_array(0, NULL);
    static_array(NULL);
    vlcstatic_array(0, NULL);
    
    int baz[20];
    regular_array(baz, 20);
    vlc_array(20, baz);
    static_array(baz);
    vlcstatic_array(20, baz);
    
    int *pfoo = make_array(10);
    regular_array(pfoo, 10);
    vlc_array(10, pfoo);
    static_array(pfoo);
    vlcstatic_array(10, pfoo);
    free(pfoo);
}

typedef int butts;
struct foo { int x; };
struct bar { int y; };
union { int meter; } m;
union { int foot; } f;

void dobutts(union { int meter; } m)
{
    printf("%d", m.meter);
}

int gint(int v)
{
    printf("int is %d\n", v);
    return 10;
}

double gouble(double d, const char *foo)
{
    printf("double is %f with label %s\n", d, foo);
    return 5.5;
}

int dnothing(void)
{
    printf("nothing\n");
    return 10;
}

#define do_thing(v) _Generic(v, int: gint(v), double: gouble(v, "foo"), default: printf("default\n"))

#define another_thing(v) _Generic(v, int: gint(v), default: dnothing())

void weird_fünc(void)
{
    printf("called %s\n", __func__);
}

void 🐴_func(void)
{
    printf("called %s\n", __func__);
}

int main(int argc, const char *argv[])
{
    another_thing(5);
    another_thing("foo");
    
    double foo = do_thing(4.3);
    int b = do_thing(8);
    _Atomic int c = 9;
    do_thing(c);
    const int d = 10;
    do_thing(d);
    volatile int e = 12;
    do_thing(e);
    union { int meter; } m = {5};
    
    int nums[2] = {1, 3};
    struct foo srf = {2};
    enum { E_A, E_B, E_C } en = E_B;
    
    //dobutts(m);
    compare_sizeof();
    reassign_struct_member();
    modify_pointer_arg();
    const_typedefs();
    string_memory();
    array_params();
    
    use_int(5);
    
    weird_fünc();
    🐴_func();
    
    return EXIT_SUCCESS;
}

