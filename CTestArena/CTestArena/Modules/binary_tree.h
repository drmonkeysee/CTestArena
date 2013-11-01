//
//  binary_tree.h
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#ifndef CTestArena_binary_tree_h
#define CTestArena_binary_tree_h

/* Binary tree reference type. */
typedef struct bt_node *binary_tree;

/* Create an empty binary tree. */
binary_tree bt_create(void);

/* Create a binary tree with the given values.
 * The values are inserted in the order they are passed.
 * This may result in a wildly imbalanced tree.
 * Use bt_rebalance() to fix-up the tree after creation. */
binary_tree bt_create_with_values(unsigned int, ...);

/* Free a binary tree. */
void bt_free(binary_tree);

/* Is the binary tree empty? */
_Bool bt_is_empty(binary_tree);

/* Insert value into binary tree. */
void bt_insert(binary_tree *, int);

/* Remove value from binary tree. */
void bt_remove(binary_tree *, int);

/* Does tree contain value? */
_Bool bt_contains(binary_tree, int);

/* Convert the existing tree into a balanced tree (what happens to original tree?) */
void bt_rebalance(binary_tree *);

/* The number of elements contained in the binary tree. */
unsigned int bt_size(binary_tree);

/* The maximum depth of the binary tree. */
unsigned int bt_depth(binary_tree);

/* print the tree */
void bt_print(binary_tree);

#endif
