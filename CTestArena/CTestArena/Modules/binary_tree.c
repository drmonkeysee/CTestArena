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

static binary_tree *find_child_slot(binary_tree parent, int value)
{
    binary_tree *slot_to_check = parent->value > value ? &parent->left : &parent->right;
    if (!(*slot_to_check) || (*slot_to_check)->value == value)
        return slot_to_check;
    return find_child_slot(*slot_to_check, value);
}

static binary_tree minimum_child(binary_tree tree)
{
    binary_tree minimum_child = tree;
    while (minimum_child->left)
        minimum_child = minimum_child->left;
    return minimum_child;
}

static binary_tree remove_node(binary_tree tree, int value)
{
    binary_tree *removed_node_slot = find_child_slot(tree, value);
    binary_tree removed_node = *removed_node_slot;
    
    if (!removed_node)
        return BT_EMPTY;
    
    if (removed_node->left && removed_node->right) {
        binary_tree successor = minimum_child(removed_node->right);
        removed_node->value = successor->value;
        bt_remove(removed_node->right, successor->value);
    } else if (removed_node->left) {
        // this may be a bug, setting remove_node->left may blow away left child of newly moved node
        *removed_node_slot = removed_node->left;
        removed_node->left = BT_EMPTY;
        bt_free(removed_node);
    } else if (removed_node->right) {
        *removed_node_slot = removed_node->right;
        removed_node->right = BT_EMPTY;
        bt_free(removed_node);
    } else {
        *removed_node_slot = BT_EMPTY;
        bt_free(removed_node);
    }
    
    return *removed_node_slot;
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
        bt_insert(&new_tree, va_arg(args, int));
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

_Bool bt_is_empty(binary_tree tree)
{
    return tree == BT_EMPTY;
}

void bt_insert(binary_tree *tree, int value)
{
    if (!tree)
        return;
    
    if (!*tree)
        *tree = create_node(value);
    else if ((*tree)->value > value)
        bt_insert(&(*tree)->left, value);
    else if ((*tree)->value < value)
        bt_insert(&(*tree)->right, value);
}

binary_tree bt_remove(binary_tree tree, int value)
{
    if (!tree || tree->value == value) {
        bt_free(tree);
        return BT_EMPTY;
    }
    
    return remove_node(tree, value);
}