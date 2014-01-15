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
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    bt_free(tree);
    
    [super tearDown];
}

- (void)test_btcreate_CreatesEmptyTree
{
    tree = bt_create();
    
    XCTAssertTrue(bt_is_empty(tree));
}

@end
