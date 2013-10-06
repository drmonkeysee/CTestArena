//
//  binary_tree.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdlib.h>

#include "binary_tree.h"

struct bt_node {
    int value;
    struct bt_node *left;
    struct bt_node *right;
};

binary_tree bt_create(void)
{
    return NULL;
}

binary_tree bt_create_with_values(int count, ...)
{
    return NULL;
}

void bt_free(binary_tree tree)
{
    if (tree) {
        bt_free(tree->left);
        bt_free(tree->right);
    }
    free(tree);
}

_Bool bt_is_empty(binary_tree tree)
{
    return tree == NULL;
}