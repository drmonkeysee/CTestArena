//
//  binary_tree.c
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "binary_tree.h"

#define BT_EMPTY NULL

struct bt_node {
    int value;
    binary_tree left;
    binary_tree right;
};

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
    binary_tree *child_slot = parent->value > value ? &parent->left : &parent->right;
    if (!(*child_slot) || (*child_slot)->value == value)
        return child_slot;
    return find_child_slot(*child_slot, value);
}

static binary_tree minimum_child(binary_tree tree)
{
    binary_tree minimum_child = tree;
    while (minimum_child->left)
        minimum_child = minimum_child->left;
    return minimum_child;
}

static void remove_node(binary_tree tree, int value)
{
    binary_tree *node_slot = find_child_slot(tree, value);
    binary_tree node = *node_slot;
    
    if (!node)
        return;
    
    if (node->left && node->right) {
        binary_tree successor = minimum_child(node->right);
        node->value = successor->value;
        bt_remove(&node->right, successor->value);
    } else if (node->left) {
        *node_slot = node->left;
        node->left = BT_EMPTY;
        bt_free(node);
    } else if (node->right) {
        *node_slot = node->right;
        node->right = BT_EMPTY;
        bt_free(node);
    } else {
        *node_slot = BT_EMPTY;
        bt_free(node);
    }
}

static void print_tree(binary_tree tree, unsigned int indent, char label)
{
    if (!tree)
        return;
    
    for (unsigned int indent_count = indent; indent_count > 0; --indent_count)
        printf("\t");
    printf("%c%d\n", label, tree->value);
    print_tree(tree->left, indent + 1, 'L');
    print_tree(tree->right, indent + 1, 'R');
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

void bt_remove(binary_tree *tree, int value)
{
    if (!tree)
        return;
    
    if (!*tree || (*tree)->value == value) {
        bt_free(*tree);
        *tree = BT_EMPTY;
    }
    
    remove_node(*tree, value);
}

void bt_print(binary_tree tree)
{
    print_tree(tree, 0, 'T');
}

unsigned int bt_size(binary_tree tree)
{
    unsigned int size = 0;
    if (tree) {
        ++size;
        size += bt_size(tree->left);
        size += bt_size(tree->right);
    }
    return size;
}

unsigned int bt_depth(binary_tree tree)
{
    if (!tree)
        return 0;
    
    unsigned int left_depth = bt_depth(tree->left);
    unsigned int right_depth = bt_depth(tree->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}