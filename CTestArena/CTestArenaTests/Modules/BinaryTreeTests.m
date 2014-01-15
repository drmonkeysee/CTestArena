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

@end
