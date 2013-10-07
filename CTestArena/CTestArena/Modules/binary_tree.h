//
//  binary_tree.h
//  CTestArena
//
//  Created by Brandon Stansbury on 10/5/13.
//  Copyright (c) 2013 Monkey Bits. All rights reserved.
//

#ifndef CTestArena_binary_tree_h
#define CTestArena_binary_tree_h

/* Binary tree type. */
typedef struct bt_node *binary_tree;

/* Create an empty binary tree. */
binary_tree bt_create(void);

/* Create a binary tree with the given elements. */
binary_tree bt_create_with_values(int count, ...);

/* Free a binary tree. */
void bt_free(binary_tree);

/* Is the binary tree empty? */
_Bool bt_is_empty(binary_tree);

/* Insert value into binary tree.
 * Returns the new node inserted into the tree.
 */
binary_tree bt_insert(binary_tree, int);

/* Remove value from binary tree.
 * Returns the tree node that replaced the element just removed.
 * If the node removed was a leaf node then the return value will be the empty binary tree.
 */
binary_tree bt_remove(binary_tree, int);

/* Does tree contain value? */
_Bool bt_contains(binary_tree, int);

/* Convert the existing tree into a balanced tree (what happens to original tree?) */
binary_tree bt_rebalance(binary_tree);

/* The number of elements contained in the binary tree. */
int bt_size(binary_tree);

/* The maximum depth of the binary tree. */
int bt_depth(binary_tree);

void bt_print(binary_tree);

#endif
