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
