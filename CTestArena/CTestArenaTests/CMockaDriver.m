//
//  CMockaDriver.m
//  CTestArena
//
//  Created by Brandon Stansbury on 3/29/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface CMockaDriver : XCTestCase

@end

@implementation CMockaDriver

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

@end
