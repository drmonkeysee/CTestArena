//
//  CMockaDriver.m
//  CTestArena
//
//  Created by Brandon Stansbury on 3/29/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

int test_main(void);

@interface CMockaDriver : XCTestCase

@end

@implementation CMockaDriver

- (void)test_SampleTest_Suite
{
    XCTAssertEqual(0, test_main(), @"sample test suite failed");
}

@end
