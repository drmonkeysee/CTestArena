#CTestArena
This is simply a toy C project with which to refresh my memory of how to use the C language.

This won't be a real project. It won't compile into something cool. It's just a sounding board to explore various aspects of C which I haven't touched since college oh so very long ago. Though the long term goal **is** to build something cool with C.

A few of the techniques I want to explore in this project:

* pulling in and linking the [SDL] framework/library
* expressing code in clearly defined modules with opaque types where appropriate (should binary\_tree be binary\_tree\_ref? or not hide the pointer modifier?)
* explore the interplay between xcode projects and workspaces
* play with unit-testing
* building linked libraries as static libraries and as frameworks (to limit public header exposure)
* playing with cmake and using it to generate xcode stuff
* compiler agnostic macros (e.g. #pragma mark vs. #pragma region)

[SDL]: http://www.libsdl.org/
