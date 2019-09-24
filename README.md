# Linked List in C with Unit Tests and Valgrind

Implementation of a linked list in C with [Unity](https://github.com/ThrowTheSwitch/Unity) unit tests and [Valgrind](http://valgrind.org/).

This is a project where test cases are developed before the implementation is written. Test cases serve as a debugging and verification tool used during development.

## Development Steps

### Install Unity

1. Copy `unity.h`, `unity.c`, `unity_internals.h` from the [Unity repo](https://github.com/ThrowTheSwitch/Unity) to `test/unity`.
1. Create an empty test file that follows the naming convention of prefexing the code-under-test file name (`linked_list.c`) with `test_` to get `test_linked_list.c`.
1. Create a simple Makefile to build the test executable.

Directory and file structure looks like this:

```text
.
├── README.md
├── src
└── test
    ├── Makefile
    ├── test_linked_list.c
    └── unity
        ├── unity.c
        ├── unity.h
        └── unity_internals.h
```

### Write the Interface for the Linked List

1. In `src/linked_list.h` declare the interface (a.k.a. API) for the linked list module.
1. In `src/linked_list.c` define function stubs (a.k.a. empty function) for the interface. Can use the cast-to-void (```(void)param```) trick to silence the compiler complaining about unused parameters or add `-Wno-unused-parameter` to the `Makefile`.
1. In `test/test_linked_list.c` create test function stubs for each linked list interface function. Add calls to stubs via Unit's `RUN_TEST(test_ll_append)` to `main`. Doing this will keep you from forgetting to add test function calls to main later. Alternatively use Unit's helper scripts to generate test runners. See the [Unity - Getting Started guide](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityGettingStartedGuide.md).
1. Modify the `test_linked_list.c` to include `linked_list.h`.
1. Modify the `Makefile` to compile `src/linked_list.c`.

File structure looks like this:

```text
.
├── README.md
├── src
│   ├── linked_list.c
│   └── linked_list.h
└── test
    ├── Makefile
    ├── test_linked_list.c
    └── unity
        ├── unity.c
        ├── unity.h
        └── unity_internals.h
```

Running the test suite passes 100% because everything is a stub at this point:

```text
test_linked_list.c:20:test_ll_append:PASS
test_linked_list.c:21:test_ll_prepend:PASS
test_linked_list.c:22:test_ll_insert_after:PASS
test_linked_list.c:23:test_ll_delete:PASS
test_linked_list.c:24:test_ll_length:PASS
test_linked_list.c:25:test_ll_iterate:PASS

-----------------------
6 Tests 0 Failures 0 Ignored 
OK
```

### Write the Tests and Implement Linked List API

As much as it would seem to be cleaner to write test cases independently of writing code-under-test, it is not practical because test code needs to be tested as well and without code-under-test to test the test code it is not possible. Sure, a simpler implementation of linked list API can be developed for the sole purpose of testing test code, but that's throw-away code and it itself needs to be tested. All this to say is that test case development and linked list implementation in this case was done iteratively.

Test code was structured so as not to rely on linked list functions to test other linked list functions. `ll_destroy()` was one unavoidable exception to that rule. This meant that test coded needed to create its own linked list to compare with the list produced by code-under-test, which, in turn, meant that test code needed to access internal `struct ll_node` members directly. This is fine until someone decides to make this into a doubly linked list for example, which will lead to the test code having to be modified while the API might not change. If test code did not rely on internal knowledge of node structure and only used linked list API for testing, then changing the nature of the linked list down the road may not require changing the tests.

1. Write tests and execute them against linked list function stubs.
1. Once enough tests are written, start implementing linked list functions while continuously re-running tests.
1. Fix bugs in tests and code-under-test until everything passes.

### Run Valgrind

```text
valgrind --leak-check=yes ./test_linked_list
```

```text
==11258== Memcheck, a memory error detector
==11258== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==11258== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==11258== Command: ./test_linked_list
==11258== 
test_linked_list.c:430:test_ll_get:PASS
test_linked_list.c:431:test_ll_length:PASS
test_linked_list.c:432:test_ll_iterate:PASS
test_linked_list.c:434:test_ll_append:PASS
test_linked_list.c:435:test_ll_prepend:PASS
test_linked_list.c:436:test_ll_set:PASS
test_linked_list.c:437:test_ll_insert_after:PASS
test_linked_list.c:438:test_ll_delete:PASS
test_linked_list.c:439:test_ll_destroy:PASS
test_linked_list.c:441:test_misc:PASS

-----------------------
10 Tests 0 Failures 0 Ignored 
OK
==11258== 
==11258== HEAP SUMMARY:
==11258==     in use at exit: 0 bytes in 0 blocks
==11258==   total heap usage: 33 allocs, 33 frees, 1,536 bytes allocated
==11258== 
==11258== All heap blocks were freed -- no leaks are possible
==11258== 
==11258== For counts of detected and suppressed errors, rerun with: -v
==11258== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
