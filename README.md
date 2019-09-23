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

### Write the Tests
