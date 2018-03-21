//
//  aliasing.c
//  CTestArena
//
//  Created by Brandon Stansbury on 9/2/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stddef.h>

#define RESTRICT_KW restrict

struct ints {
    int v, *p;
};

struct pair {
    int a, b;
};

struct pair with_ints(struct ints * RESTRICT_KW c, int * RESTRICT_KW i)
{
    int *v_ref = &c->v; // restrict c forbids aliasing c->v with i
    int *p_ref = c->p;  // restrict i forbids aliasing with c->p
    *v_ref = 5;
    *p_ref = 7;
    *i = 11;
    return (struct pair){*v_ref, *p_ref};
}

struct pair with_ints_val(struct ints c, int * RESTRICT_KW i)
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
struct pair with_voids(struct ints * RESTRICT_KW c, void * RESTRICT_KW vp)
{
    int *v_ref = &c->v;
    int *p_ref = c->p;
    int *i = vp;
    *v_ref = 5;
    *p_ref = 7;
    *i = 11;
    return (struct pair){*v_ref, *p_ref};
}

struct pair with_str_array(struct ints * RESTRICT_KW c, char *strings[])
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

enum mine {
    MINE_FOO
};

struct pair two_structs(struct one *o, struct two *t)
{
    o->a = 1;
    t->a = 3;
    return (struct pair){ o->a, t-> a};
}

struct pair struct_enum(struct one * restrict o, enum mine * restrict e)
{
    o->a = 1;
    *e = 3;
    return (struct pair){ o->a, *e};
}

void one_write(int * RESTRICT_KW a, const int * RESTRICT_KW b, const int * RESTRICT_KW c, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        a[i] = b[i] + c[i];
    }
}

// restrict omits a movl
void sametype_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, int * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}

// restrict has no effect
void mixedtype_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, short * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}

// restrict omits a movl
void void_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, void * RESTRICT_KW val)
{
    int *int_val = val;
    *a += *int_val;
    *b += *int_val;
}

// restrict omits a movsbl
void char_aliasing(int * RESTRICT_KW a, int * RESTRICT_KW b, char * RESTRICT_KW val)
{
    *a += *val;
    *b += *val;
}

struct pair multiple_types(int *ip, double *dp, char * RESTRICT_KW cp)
{
    *ip = 5;
    *dp = 1.2;
    *cp = 3;
    return (struct pair){ *ip, *dp };
}
