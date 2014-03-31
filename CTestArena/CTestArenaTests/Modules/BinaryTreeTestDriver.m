//
//  BinaryTreeTestDriver.m
//  CTestArena
//
//  Created by Brandon Stansbury on 1/14/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

int binary_tree_tests_main(void);

@interface BinaryTreeTestDriver : XCTestCase

@end

@implementation BinaryTreeTestDriver

- (void)test_binarytree_Suite
{
    XCTAssertEqual(0, binary_tree_tests_main());
}

@end
