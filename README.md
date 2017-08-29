# CTestArena

This is simply a toy C project with which to refresh my memory of how to use the C language. Specifically the weird corners of the C language that are hard to remember.

This won't be a real project. It won't compile into something cool. It's just a sounding board to explore various aspects of C which I haven't touched since college oh so very long ago. Though the long term goal **is** to build something cool with C.

* pulling in and linking the [SDL] framework/library
* expressing code in clearly defined modules with opaque types where appropriate
    * should binary\_tree be binary\_tree\_ref?
    * or not hide the pointer modifier?
    * should binary\_tree ever be a \* const?
* explore the interplay between xcode projects and workspaces
* play with unit-testing
    * [Unity]/CMock
    * CTest
    * CUnit
    * googletest
    * cmockery/cmocka
    * TestDept
    * CppUTest
* building linked libraries as static libraries and as frameworks (to limit public header exposure)
* playing with cmake and using it to generate xcode stuff
* compiler agnostic macros (e.g. #pragma mark vs. #pragma region)
* lots of other stuff this list is likely way out of date

[SDL]: http://www.libsdl.org/
[Unity]: http://throwtheswitch.org
