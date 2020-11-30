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

struct alt_ints {
    int v, *p;
};

struct doubles {
    double v, *p;
};

struct pair {
    int a, b;
};

// i aliases with c->v and c->p
struct pair with_ints(struct ints *restrict c, int *restrict i)
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

//
// cases verified through godbolt
//

// char aliases (even when const!) but a and d don't alias with each other
struct pair multiple_types(int * a, double * d, const char *restrict s)
{
    int c = *s;
    *d = c + 1.2;
    *a = 3;
    return (struct pair){*a, *s};
}

// restrict on *a doesn't do anything but restrict on b does work
struct pair double_pointers(int **a, int *restrict b)
{
    int c = *b;
    **a = c + 10;
    return (struct pair){**a, *b};
}

// enum e acts like char * here, it aliases with a and d
struct pair scalars_and_enums(int * a, double * d, enum mine *restrict e)
{
    int c = *e;
    *a = 10;
    *d = c + 1.5;
    return (struct pair){*a, *e};
}

// s aliases with p but nothing within p
struct pair struct_and_char(struct pair *p, const char *restrict s)
{
    int c = *s;
    p->a = 10;
    p->b = c + 3;
    // doing this shuffles the instructions a bit but is otherwise the same
    // *p = (struct pair){10, c + 3};
    return (struct pair){p->a, *s};
}

// i and b->p both alias and retrict on only one param isn't sufficient for full optimization
// (NOTE: in this case i is an int * but a char * would also alias)
// (NOTE: more distressingly, if i were double * then restrict on b still has an effect, though not on i)
// (is restrict optimization treating structs as opaque objects for the purposes of aliasing?)
// NOTE: ANSWER BELOW
struct pair struct_and_pointer(struct ints *restrict b, int *restrict i)
{
    int c = *i;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *i};
}

// *b->p is aliasing with b->v (!)
// see parameters as (int *b_v, int **b_p) and *b_p is aliasing with b_v
// struct ints *restrict b is *like* (int *restrict b_v, int **restrict b_p)
// where first restrict is actually preventing aliasing
// redefining struct ints to {int v, *restrict p} does not help
// {int v; double *p} will *NOT* alias itself but {int v; char *p} will
struct pair struct_itself(struct ints *restrict b)
{
    int c = *b->p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *b->p};
}

// b->n and f->n alias each other!
struct pair struct_pointer_fields(struct ints *restrict b, struct alt_ints *restrict f)
{
    int c = *f->p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *f->p};
}

// b->n and bv.n alias each other! (NOTE: b->v does not alias with anything)
struct pair same_struct_fields(struct ints *restrict b, struct ints bv)
{
    int c = *bv.p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *bv.p};
}

// restrict on b has an effect here!
// is restrict on ANY write-through of a struct field potentially useful?
struct pair struct_diff_fields(struct ints *restrict b, struct doubles *f)
{
    double c = *f->p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *f->p};
}

//
// additional cases
//

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

struct pointer_one {
    int *a;
};

struct pointer_two {
    int *a;
};

// restrict has no effect here (nor in the struct definitions)
// looks like it reloads one->a from memory either way
// it's probably a bit like int** and int** case
int struct_p_members(struct pointer_one *one, struct pointer_two *two)
{
    *(one->a) = 5;
    *(two->a) = 10;
    return *(one->a);
}
