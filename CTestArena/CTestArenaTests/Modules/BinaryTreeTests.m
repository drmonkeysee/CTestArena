//
//  BinaryTreeTests.m
//  CTestArena
//
//  Created by Brandon Stansbury on 1/14/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

#include "binary_tree.h"

@interface BinaryTreeTests : XCTestCase
{
    binary_tree tree;
}
@end

@implementation BinaryTreeTests

- (void)setUp
{
    [super setUp];
    
    tree = bt_create();
}

- (void)tearDown
{
    bt_free(tree);
    
    [super tearDown];
}

- (void)test_btcreate_CreatesEmptyTree
{
    XCTAssertTrue(bt_is_empty(tree));
}

- (void)test_btsize_ReturnsZero_IfEmptyTree
{
    XCTAssertEqual(0lu, bt_size(tree));
}

- (void)test_btdepth_ReturnsZero_IfEmptyTree
{
    XCTAssertEqual(0lu, bt_depth(tree));
}

- (void)test_btinsert_InsertsValueIntoTree
{
    bt_insert(&tree, 4);
    
    XCTAssertEqual(1lu, bt_size(tree));
}

- (void)test_btinsert_InsertsZeroIntoTree
{
    bt_insert(&tree, 0);
    
    XCTAssertEqual(1lu, bt_size(tree));
}

- (void)test_btinsert_InsertsMultipleValues
{
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, 10);
    
    XCTAssertEqual(3lu, bt_size(tree));
}

- (void)test_btcreatewithvalues_CreatesTreeWithGivenValues
{
    bt_free(tree);
    int numbers[] = { 1, 2, 3, 4, 5 };
    const size_t count = sizeof numbers / sizeof numbers[0];
    
    tree = bt_create_with_values(count, 1, 2, 3, 4, 5);
    
    XCTAssertFalse(bt_is_empty(tree));
    XCTAssertEqual(count, bt_size(tree));
    for (size_t i = 0; i < count; ++i)
        XCTAssertTrue(bt_contains(tree, numbers[i]));
}

- (void)test_btcreatewithvalues_InsertsValuesInOrder
{
    bt_free(tree);
    const size_t count = 5;
    
    tree = bt_create_with_values(count, 1, 2, 3, 4, 5);
    
    XCTAssertEqual(count, bt_depth(tree));
}

- (void)test_btcontains_ReturnsTrue_IfValuePresent
{
    int expected_value = 8;
    bt_insert(&tree, expected_value);
    
    XCTAssertTrue(bt_contains(tree, expected_value));
}

- (void)test_btcontains_ReturnsFalse_IfValueNotPresent
{
    int expected_value = 8;
    bt_insert(&tree, 10);
    
    XCTAssertFalse(bt_contains(tree, expected_value));
}

- (void)test_btcontains_SupportsZero
{
    int expected_value = 0;
    bt_insert(&tree, expected_value);
    
    XCTAssertTrue(bt_contains(tree, expected_value));
}

- (void)test_btcontains_ReturnsTrue_IfValuePresentAmongOtherValues
{
    int expectedValue = 8;
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, expectedValue);
    bt_insert(&tree, 10);
    
    XCTAssertTrue(bt_contains(tree, expectedValue));
}

- (void)test_btinsert_CreatesTreeStructure
{
    bt_insert(&tree, 3);
    bt_insert(&tree, -4);
    bt_insert(&tree, 8);
    bt_insert(&tree, 10);
    bt_insert(&tree, 1);
    
    XCTAssertEqual(5lu, bt_size(tree));
    XCTAssertEqual(3lu, bt_depth(tree));
}

- (void)test_btrebalance_RebalancesTree
{
    bt_free(tree);
    const size_t count = 10;
    tree = bt_create_with_values(count, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    XCTAssertEqual(count, bt_depth(tree));
    
    bt_rebalance(&tree);
    
    XCTAssertEqual(4lu, bt_depth(tree));
}

- (void)test_btrebalance_RebalancesEmptyTree
{
    bt_rebalance(&tree);
    
    XCTAssertTrue(bt_is_empty(tree));
}

- (void)test_btrebalance_RebalancesTreeWithOneElement
{
    bt_insert(&tree, 12);
    
    bt_rebalance(&tree);
    
    XCTAssertEqual(1lu, bt_size(tree));
}

@end
