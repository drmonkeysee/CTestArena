//
//  binary_tree_tests.c
//  CTestArena
//
//  Created by Brandon Stansbury on 3/30/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

#include <stdlib.h>
#include "binary_tree.h"

static void setup(void **state)
{
    binary_tree tree = bt_create();
    *state = tree;
}

static void teardown(void **state)
{
    free(*state);
}

static void btcreate_CreatesEmptyTree(void **state)
{
    binary_tree tree = *state;
    
    assert_true(bt_is_empty(tree));
}

static void btsize_ReturnsZero_IfEmptyTree(void **state)
{
    binary_tree tree = *state;
    
    assert_int_equal(0lu, bt_size(tree));
}

static void btdepth_ReturnsZero_IfEmptyTree(void **state)
{
    binary_tree tree = *state;
    
    assert_int_equal(0lu, bt_depth(tree));
}

static void btinsert_InsertsValueIntoTree(void **state)
{
    binary_tree tree = *state;
    
    bt_insert(&tree, 4);
    
    assert_int_equal(1lu, bt_size(tree));
}

static void btinsert_InsertsZeroIntoTree(void **state)
{
    binary_tree tree = *state;
    
    bt_insert(&tree, 0);
    
    assert_int_equal(1lu, bt_size(tree));
}

static void btinsert_InsertsMultipleValues(void **state)
{
    binary_tree tree = *state;
    
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, 10);
    
    assert_int_equal(3lu, bt_size(tree));
}

static void btcreatewithvalues_CreatesTreeWithGivenValues(void **state)
{
    int numbers[] = { 1, 2, 3, 4, 5 };
    const size_t count = sizeof numbers / sizeof numbers[0];
    
    binary_tree tree = bt_create_with_values(count, 1, 2, 3, 4, 5);
    
    assert_false(bt_is_empty(tree));
    assert_int_equal(count, bt_size(tree));
    for (size_t i = 0; i < count; ++i) {
        assert_true(bt_contains(tree, numbers[i]));
    }
    free(tree);
}

static void btcreatewithvalues_InsertsValuesInOrder(void **state)
{
    const size_t count = 5;
    
    binary_tree tree = bt_create_with_values(count, 1, 2, 3, 4, 5);
    
    assert_int_equal(count, bt_depth(tree));
    free(tree);
}

static void btcontains_ReturnsTrue_IfValuePresent(void **state)
{
    binary_tree tree = *state;
    int expected_value = 8;
    
    bt_insert(&tree, expected_value);
    
    assert_true(bt_contains(tree, expected_value));
}

static void btcontains_ReturnsFalse_IfValueNotPresent(void **state)
{
    binary_tree tree = *state;
    int expected_value = 8;
    
    bt_insert(&tree, 10);
    
    assert_false(bt_contains(tree, expected_value));
}

static void btcontains_SupportsZero(void **state)
{
    binary_tree tree = *state;
    int expected_value = 0;
    
    bt_insert(&tree, expected_value);
    
    assert_true(bt_contains(tree, expected_value));
}

static void btcontains_ReturnsTrue_IfValuePresentAmongOtherValues(void **state)
{
    binary_tree tree = *state;
    int expectedValue = 8;
    
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, expectedValue);
    bt_insert(&tree, 10);
    
    assert_true(bt_contains(tree, expectedValue));
}

static void btinsert_CreatesTreeStructure(void **state)
{
    binary_tree tree = *state;
    
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, 8);
    bt_insert(&tree, 10);
    bt_insert(&tree, 1);
    
    assert_int_equal(5lu, bt_size(tree));
    assert_int_equal(3lu, bt_depth(tree));
}

static void btrebalance_RebalancesTree(void **state)
{
    const size_t count = 10;
    binary_tree tree = bt_create_with_values(count, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    assert_int_equal(count, bt_depth(tree));
    
    bt_rebalance(&tree);
    
    assert_int_equal(4lu, bt_depth(tree));
    free(tree);
}

static void btrebalance_RebalancesEmptyTree(void **state)
{
    binary_tree tree = *state;
    
    bt_rebalance(&tree);
    
    assert_true(bt_is_empty(tree));
}

static void btrebalance_RebalancesTreeWithOneElement(void **state)
{
    binary_tree tree = *state;
    bt_insert(&tree, 12);
    
    bt_rebalance(&tree);
    
    assert_int_equal(1lu, bt_size(tree));
}

int binary_tree_tests_main(void)
{
    // ct_create_fixture and ct_create_suite?
    // ct_fixture_setup(f_ptr)
    // ct_setup(function_ptr)
    // ct_test_suite(f_ptr, f_ptr, f_ptr, f_ptr)
    // ct_teardown(function_ptr)
    // ct_fixture_teardown(f_ptr)
    // ct_run_suite(name:, array_of_f_ptr) use function name if no suite name defined?
    // ct_make_suite(setup, array_of_f_ptr, teardown)
    // ct_make_fixture(setup, suite, teardown)
    // ct_run_suite(suite)
    // ct_run_fixture(fixture)
    
    const UnitTest tests[] = {
        unit_test_setup_teardown(btcreate_CreatesEmptyTree, setup, teardown),
        unit_test_setup_teardown(btsize_ReturnsZero_IfEmptyTree, setup, teardown),
        unit_test_setup_teardown(btdepth_ReturnsZero_IfEmptyTree, setup, teardown),
        unit_test_setup_teardown(btinsert_InsertsValueIntoTree, setup, teardown),
        unit_test_setup_teardown(btinsert_InsertsZeroIntoTree, setup, teardown),
        unit_test_setup_teardown(btinsert_InsertsMultipleValues, setup, teardown),
        unit_test_teardown(btcreatewithvalues_CreatesTreeWithGivenValues, teardown),
        unit_test_teardown(btcreatewithvalues_InsertsValuesInOrder, teardown),
        unit_test_setup_teardown(btcontains_ReturnsTrue_IfValuePresent, setup, teardown),
        unit_test_setup_teardown(btcontains_ReturnsFalse_IfValueNotPresent, setup, teardown),
        unit_test_setup_teardown(btcontains_SupportsZero, setup, teardown),
        unit_test_setup_teardown(btcontains_ReturnsTrue_IfValuePresentAmongOtherValues, setup, teardown),
        unit_test_setup_teardown(btinsert_CreatesTreeStructure, setup, teardown),
        unit_test_teardown(btrebalance_RebalancesTree, teardown),
        unit_test_setup_teardown(btrebalance_RebalancesEmptyTree, setup, teardown),
        unit_test_setup_teardown(btrebalance_RebalancesTreeWithOneElement, setup, teardown),
    };
    
    return run_tests(tests);
}