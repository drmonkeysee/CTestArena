//
//  SampleTestDriver.m
//  CTestArena
//
//  Created by Brandon Stansbury on 3/29/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

int sample_tests_main(void);

@interface SampleTestDriver : XCTestCase

@end

@implementation SampleTestDriver

- (void)test_SampleTest_Suite
{
    XCTAssertEqual(0, sample_tests_main());
}

- (void)test_FailEquality
{
    XCTAssertEqual(0, 1);
    XCTAssertEqual(2, 3, @"Lookout!");
    NSNumber *blarg = @45;
    XCTAssertNil(blarg, @"Oh no not nil");
    XCTAssertFalse(blarg, @"oh no not false");
}

- (void)test_Fail
{
    XCTFail(@"oh NO");
    XCTFail();
}

@end
