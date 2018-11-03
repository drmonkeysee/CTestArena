//
//  aliasing.c
//  CTestArena
//
//  Created by Brandon Stansbury on 9/2/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stddef.h>
#include <stdio.h>

struct ints {
    int v, *p;
};

struct pair {
    int a, b;
};

// i aliases with c->v and c->p
struct pair with_ints(struct ints * restrict c, int * restrict i)
{
    int *v_ref = &c->v; // restrict c forbids aliasing c->v with i
    int *p_ref = c->p;  // restrict i forbids aliasing with c->p
    *v_ref = 5;
    *p_ref = 7;
    *i = 11;
    return (struct pair){*v_ref, *p_ref};
}

// i aliases with c->p
struct pair with_ints_val(struct ints c, int * restrict i)
{
    int *v_ref = &c.v;  // c.v is by-value in scope so no possible aliasing
    int *p_ref = c.p;   // restrict i optimizes aliasing with c.p
    *v_ref = 5;
    *p_ref = 7;
    *i = 11;
    return (struct pair){*v_ref, *p_ref};
}

// this works identically to with_ints
// vp can alias either c->v or c->p
struct pair with_voids(struct ints * restrict c, void * restrict vp)
{
    int *v_ref = &c->v;
    int *p_ref = c->p;
    int *i = vp;
    *v_ref = 5;
    *p_ref = 7;
    *i = 11;
    return (struct pair){*v_ref, *p_ref};
}

// any of the chars alias with c
struct pair with_str_array(struct ints * restrict c, char *strings[])
{
    int *v_ref = &c->v;
    int *p_ref = c->p;
    char *ch = strings[0];
    *v_ref = 5;
    *p_ref = 7;
    *ch = 11;
    return (struct pair){*v_ref, *p_ref};
}

struct one {
    int a;
};

struct two {
    int a;
};

struct three {
    char a;
};

struct four {
    float a;
};

enum mine {
    MINE_FOO = 65000
};

// these do not alias
struct pair two_structs(struct one *o, struct two *t)
{
    o->a = 1;
    t->a = 3;
    return (struct pair){o->a, t-> a};
}

// these alias at o->a
struct pair struct_enum(struct one *o, enum mine *e)
{
    o->a = 1;
    *e = 3;
    return (struct pair){o->a, *e};
}

struct pair char_struct_enum(struct three *t, enum mine *e)
{
    t->a = 'a';
    *e = 3;
    return (struct pair){t->a, *e};
}

struct pair float_struct_enum(struct four * restrict f, enum mine * restrict e)
{
    f->a = 1.2;
    *e = 3;
    return (struct pair){f->a, *e};
}

// char aliases
struct pair multiple_types(int *ip, double *dp, char * restrict cp)
{
    *ip = 5;
    *dp = 1.2;
    *cp = 3;
    return (struct pair){*ip, *dp};
}

// these alias
int mixedints(int *a, unsigned int *b)
{
    *a = 2;
    *b = 5;
    return *a;
}

// these alias
int mixed_explicit_ints(signed int *a, unsigned int *b)
{
    *a = 2;
    *b = 5;
    return *a;
}

// these do not
int mixedsizes(int *a, long *b)
{
    *a = 2;
    *b = 5;
    return *a;
}

// these do not
int mixednums(int *a, double *b)
{
    *a = 2;
    *b = 1.2;
    return *a;
}

// enums seem to alias with all int types
int mixedenums(short *a, enum mine *e)
{
    *a = 2;
    *e = 5;
    return *a;
}

// enums seem to alias with everything
int floatenums(float *a, enum mine *e)
{
    *a = 2.0;
    *e = 5;
    return *a;
}

// these do not
int mixedfsizes(double *a, long double *b)
{
    *a = 2.0;
    *b = 1.2;
    return *a;
}

int use_int(int i)
{
    int a = i + 3;
    return a;
}

// restrict ip has an effect but restrict *ipp does not
// regardless of order of stores and loads between *ipp and ip
int pointer_and_pointer_to_pointer(int **ipp, int *ip)
{
    int *p = *ipp;
    *p = 5;
    *ip = 10;
    return **ipp;
}

// restrict has no effect anywhere here including:
// pointer to pointer args, pointer args, and pointer locals
int pointers_to_pointers(int **ipp, int **ipp2)
{
    int *p = *ipp;
    int *p2 = *ipp2;
    *p = 5;
    *p2 = 10;
    return **ipp;
}

// restrict has no effect on *numbers, probably for same reason
// it had no effect on *ipp above
int pointer_array(int *numbers[], size_t n)
{
    if (n < 2) return 0;
    
    int *first = numbers[0];
    *first = 10;
    *(numbers[1]) = 5;
    return *first;
}

// restrict has no effect here
// no writes, no need for reloads
int const_restrict(const int *a, const int *b)
{
    int r1 = use_int(*a);
    int r2 = use_int(*b);
    return r1 + r2 + *a + *b;
}

// restrict has a HUGE effect here
// crossing a translation unit boundary causes reloads if not restrict
int const_restrict_ext_call(const int * restrict a, const int * restrict b)
{
    int r1 = *a;
    int r2 = *b;
    printf("%d:%d", 1, 2);
    return r1 + r2 + *a + *b;
}

