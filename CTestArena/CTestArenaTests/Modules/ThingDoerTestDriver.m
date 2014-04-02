//
//  ThingDoerTestDriver.m
//  CTestArena
//
//  Created by Brandon Stansbury on 4/1/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

int thing_doer_tests_main(void);

@interface ThingDoerTestDriver : XCTestCase

@end

@implementation ThingDoerTestDriver

- (void)test_ThingDoer_Suite
{
    XCTAssertEqual(0, thing_doer_tests_main());
}

@end
