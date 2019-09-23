CC=gcc

CFLAGS = -ggdb
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition

INC_DIRS = -Iunity
INC_DIRS += -I../src

test_linked_list: ../src/linked_list.c test_linked_list.c
	$(CC) $(CFLAGS) $(INC_DIRS) ../src/linked_list.c unity/unity.c test_linked_list.c -o test_linked_list