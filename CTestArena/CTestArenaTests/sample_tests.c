//
//  sample_tests.c
//  CTestArena
//
//  Created by Brandon Stansbury on 3/30/14.
//  Copyright (c) 2014 Monkey Bits. All rights reserved.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka/cmocka.h>

static void null_test_success(void **state)
{
    assert_true(1);
}

int test_main(void)
{
    const UnitTest tests[] = { unit_test(null_test_success) };
    
    return run_tests(tests);
}