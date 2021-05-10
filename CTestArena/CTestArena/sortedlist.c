//
//  sortedlist.c
//  CTestArena
//
//  Created by Brandon Stansbury on 5/9/21.
//  Copyright © 2021 Brandon Stansbury. All rights reserved.
//

#include "sortedlist.h"

#include <stdbool.h>
#include <stdlib.h>

struct node {
    unsigned short min, max;
    struct node *next;
};

struct sortedvector {
    struct node *nodes;
};

static unsigned int addrs[] = {0x0, 0x800, 0x1000, 0x2000, 0x3000, 0x4000, 0x8000, 0x8200, 0x9000, 0xa000, 0xb000, 0xc000, 0xd000, 0xe000, 0xe800, 0xf000, 0x10000};

slist *slist_new(void)
{
    struct node *cur = NULL, *prev = NULL, *head = NULL;
    for (size_t i = 0; i < (sizeof addrs / sizeof addrs[0]) - 1; ++i) {
        cur = malloc(sizeof *cur);
        *cur = (struct node){
            .min = addrs[i], .max = addrs[i + 1] - 1
        };
        if (prev) {
            prev->next = cur;
        }
        prev = cur;
        if (!head) head = cur;
    }
    return head;
}

_Bool slist_search(slist *self, unsigned short a)
{
    for (struct node *n = self; n; n = n->next) {
        if (n->min <= a && a <= n->max) return true;
    }
    return false;
}

svec *svec_new(void)
{
    size_t count = (sizeof addrs / sizeof addrs[0]) - 1;
    struct sortedvector *self = malloc(sizeof *self);
    *self = (struct sortedvector){.nodes = calloc(count, sizeof *self->nodes)};
    for (size_t i = 0; i < count; ++i) {
        self->nodes[i] = (struct node){.min = addrs[i], .max = addrs[i + 1] - 1};
    }
    return self;
}

_Bool svec_search(svec *self, unsigned short a)
{
    size_t count = (sizeof addrs / sizeof addrs[0]) - 1;
    for (size_t i = 0; i < count; ++i) {
        if (self->nodes[i].min <= a && a <= self->nodes[i].max) return true;
    }
    return false;
}
