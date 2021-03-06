//
//  aliasing.c
//  CTestArena
//
//  Created by Brandon Stansbury on 9/2/14.
//  Copyright (c) 2014 Brandon Stansbury. All rights reserved.
//

#include <stddef.h>
#include <stdio.h>

struct pair {
    int a, b;
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

struct ints {
    int v, *p;
};

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
// analogous to a scope like (int *b_v, int **b_p) and *b_p is aliasing with b_v
// struct ints *restrict b is *like* (int *restrict b_v, int **restrict b_p)
// where first restrict is actually preventing aliasing
// redefining struct ints to {int v, *restrict p} does not help
// {int v; double *p} will *NOT* alias itself but {int v; char *p} will
struct pair struct_itself(struct ints *restrict b)
{
    int c = b->v;
    *b->p = c + 10;
    return (struct pair){b->v, *b->p};
}

// this generates identical code to struct_itself
// NOTE: int *restrict *p and int **restrict p have no effect
struct pair unrolled_struct(int *restrict v, int **p)
{
    int c = *v;
    **p = c + 10;
    return (struct pair){*v, **p};
}

struct two_ints {
    int a, b;
};

// note a pointer to a struct is still a pointer to a single object;
// if the struct itself contains no pointer fields all storage is accounted for
// in the single pointer and it's impossible for anything to alias here.
// specifically it is *NOT* analogous to the aliasable scope (int *v_a, int *v_b)
int only_values(struct two_ints *v)
{
    int i = v->a;
    v->b = i + 10;
    return v->a;
}

struct alt_ints {
    int v, *p;
};

// b and f have no aliasing here BUT b->v and *b->p are aliasing
struct pair struct_pointer_fields(struct ints *restrict b, struct alt_ints *f)
{
    int c = *f->p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *f->p};
}

// here b->v and *f->p are aliasing, this shows the operations in the function
// are relevant for aliasing concerns (obviously, in hindsight)
struct pair cross_struct_aliasing(struct ints *restrict b, struct alt_ints *f)
{
    int c = *f->p;
    b->v = c + 10;
    return (struct pair){b->v, *f->p};
}

// b and bv have no aliasing here BUT b->v and *b->p are aliasing
struct pair same_struct_fields(struct ints *restrict b, struct ints bv)
{
    int c = *bv.p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *bv.p};
}

struct doubles {
    double v, *p;
};

// b and f have no aliasing here BUT b->v and *b->p are aliasing
struct pair struct_diff_fields(struct ints *restrict b, struct doubles *f)
{
    double c = *f->p;
    b->v = 10;
    *b->p = c + 3;
    return (struct pair){b->v, *f->p};
}

// in this case adding restrict *ADDS* an additional mov instruction
char strings_and_buffers(const char *restrict s, char **b)
{
    printf("foo: %c", *s);
    (*b)[0] = 'a';
    return *s;
}

struct vector {
    size_t s;
    short a[];
};

// restrict has HUGE effect here, restrict can turn this loop into a memcpy
// restrict on either v or b has the same effect
// if vector is redefined to use short *a then restrict b has same memcpy effect
// but restrict on v has NO effect (because as-if short **restrict v_a which does not address aliasing)
// changing a[] to *restrict a has no effect
void struct_array_and_pointer(struct vector *v, size_t n, short b[restrict n])
{
    for (size_t i = 0; i < n; ++i) {
        b[i] = v->a[i];
    }
}

struct array_list {
    size_t s;
    short a[];
};

// NOTE: turns out aliasing analysis deals mostly in lvalues, not types or variables
// in this case l->a[i] and v->a[i] are both int lvalues and therefore compilers
// may infer they alias even thought the encompassing aggregate types l and a
// cannot alias; technically the compiler could reason this out but in practice
// they only consider lvalue expressions in isolation.

// NOTE: actually i'm not sure i understand this one, the array member is part
// of the struct object and two different struct types shouldn't alias,
// it would imply v and l are pointing at the same underlying object ???

// restrict has huge effect here for same reason
// there are effectively two short * parameters
// again replacing a[] with a * restrict has no optimization effect
// short **restrict v_a, short **restrict l_a doesn't help with optimizing
// reads/writes through **v_a and **l_a
// changing array_list to have an int[] or double[] member removes restrict
// optimization opportunities but not due to aliasing analysis, it's because
// you can't memcpy from a short buffer to an int or double buffer (exactly because they *don't* alias)
void struct_array_members(struct vector *restrict v, struct array_list *restrict l)
{
    for (size_t i = 0; i < l->s; ++i) {
        l->a[i] = v->a[i];
    }
}

// NOTE: again i don't get this, the two structs shouldn't be aliasing (SEE ABOVE)

// restrict has an effect here because v->s aliases l->s (e.g. size_t *v_s, size_t *l_s)
// since there is a write followed by a read, restrict presents optimization opportunities
size_t struct_scalar_members(struct vector * v, struct array_list *restrict l)
{
    l->s = v->s;
    return v->s;
}

struct {
    int *ip;
} GlobalInt;

// restrict on parameter has an effect but restrict on GlobalInt.ip does not
// seems like it should? maybe compilers just don't consider it
int global_with_pointer(int *restrict c)
{
    int n = *GlobalInt.ip;
    *c += n;
    return *GlobalInt.ip;
}


const char *const GlobalStr = "Foobar";

// restrict has no effect here, looks like compiler inlines the char literal
// from the string data rather than using the pointer variable at all
char global_string(char * c)
{
    int n = *GlobalStr;
    *c += n;
    return *GlobalStr;
}

int *restrict AInt;
int *restrict BInt;

// all of these restricts have an effect depending on the order things are done in
int global_ints(int *restrict c)
{
    // *BInt += *AInt;
    *c += *AInt;
    return *AInt;
}

// restrict helps here if v is cast to int * but not double *
int type_and_void(int *i, void *v)
{
    double n = *(double *)v;
    *i += n;
    return *(double *)v;
}

struct intp {
    int *restrict a;
};

// only restrict that optimizes here is on the struct field
int struct_reference_vs_value(struct intp **ref, struct intp v)
{
    int i = *(*ref)->a;
    *v.a = i + 10;
    return *(*ref)->a;
}


//
// additional cases
//

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
