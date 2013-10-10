//
//  binary_tree.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdlib.h>
#include <stdarg.h>

#include "binary_tree.h"

struct bt_node {
    int value;
    binary_tree left;
    binary_tree right;
};

#define BT_EMPTY NULL

static binary_tree create_node(int value)
{
    binary_tree new_node = malloc(sizeof *new_node);
    new_node->value = value;
    new_node->left = BT_EMPTY;
    new_node->right = BT_EMPTY;
    return new_node;
}

static binary_tree insert_new_node(binary_tree tree, int value)
{
    binary_tree inserted_node;
    
    if (tree->value == value)
        inserted_node = tree;
    else if (tree->value > value) {
        inserted_node = bt_insert(tree->left, value);
        if (!tree->left)
            tree->left = inserted_node;
    } else {
        inserted_node = bt_insert(tree->right, value);
        if (!tree->right)
            tree->right = inserted_node;
    }
    
    return inserted_node;
}

binary_tree bt_create(void)
{
    return BT_EMPTY;
}

binary_tree bt_create_with_values(unsigned int count, ...)
{
    binary_tree new_tree = bt_create();
    
    va_list args;
    va_start(args, count);
    for (unsigned int i = 0; i < count; ++i)
        bt_insert(new_tree, va_arg(args, int));
    va_end(args);
    
    return new_tree;
}

void bt_free(binary_tree tree)
{
    if (tree) {
        bt_free(tree->left);
        bt_free(tree->right);
    }
    free(tree);
}

_Bool bt_is_empty(binary_tree const tree)
{
    return tree == BT_EMPTY;
}

binary_tree bt_insert(binary_tree tree, int value)
{
    if (!tree)
        return create_node(value);
    
    return insert_new_node(tree, value);
}