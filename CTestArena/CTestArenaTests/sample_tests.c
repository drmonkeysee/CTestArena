//
//  sample_tests.c
//  CTestArena
//
//  Created by Brandon Stansbury on 3/30/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

static void example_pass(void **state)
{
    assert_true(1);
}

static void example_fail(void **state)
{
    assert_true(0);
}

int test_main(void)
{
    const UnitTest tests[] = {
        unit_test(example_pass),
        unit_test(example_fail)
    };
    
    return run_tests(tests);
}