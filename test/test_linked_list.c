#include <string.h>

#include "linked_list.h"
#include "unity.h"

// Global variables used by test cases

// Number of strings available to expected and actual list to use as node data.
// Changing NUM_STRS value is not enough to ensure tests run. Some tests do not
// check the bounds of strs and exp_list.
#define NUM_STRS (4)

// String constants that comprize the data in the linked list. I.e. linked lists
// used in this test suite simply point to these strings for their data.
const char *strs[] = {"Red", "Green", "Blue", "Violet"};

// Hand-made expected linked list that is compared to actual list produced via
// the linked list API
struct ll_node exp_list[NUM_STRS];

// Head for the actual linked list produced by the linked list API
struct ll_node *head = NULL;

/**
 * Create a linked list by hand. The list is composed of NUM_STRS nodes that use
 * strings in the strs array for data. This list is used by test cases as the
 * expected linked list to be compared to the actual list produced by the
 * code-under-test linked list API.
 *
 * This function is called by Unity before every test function. No matter what a
 * previous test case run did to exp_list, this function ensures that exp_list
 * is in known state at the beginning of each test function execution.
 */
void setUp(void) {
  // Create the expected list
  for (unsigned int i = 0; i < NUM_STRS - 1; i++) {
    exp_list[i].data = (void *)strs[i];
    exp_list[i].next = &exp_list[i + 1];
  }
  exp_list[NUM_STRS - 1].data = (void *)strs[NUM_STRS - 1];
  exp_list[NUM_STRS - 1].next = NULL;

  // Clear the actual link list pointer
  head = NULL;
}

/**
 * This function is called by Unity at the end of each test case.
 */
void tearDown(void) {
  ll_destroy(&head);
  head = NULL;
}

/**
 * Helper test function. Compare two linked lists.
 *
 * @param equal   Function pointer that compares data stored in the list and
 *                returns 0 when its parameters are not the same and 1 when they
 *                are the same.
 *
 * @retval 0 If list topology or node data is different.
 * @retval 1 If list topology and node data are the same.
 */
int lists_equal(struct ll_node *h1, struct ll_node *h2,
                int (*equal)(void *d1, void *d2)) {
  while (h1 != NULL && h2 != NULL) {
    if (equal(h1->data, h2->data) == 0) {
      return 0;
    }
    h1 = h1->next;
    h2 = h2->next;
  }
  if (h1 != NULL || h2 != NULL) {
    return 0;
  }
  return 1;
}

int strs_equal(void *s1, void *s2) {
  if (s1 == s2) {
    return 1;  // If s1 is pointing at the same location as s2 or both are NULL
  }
  if (s1 == NULL || s2 == NULL) {
    return 0;  // If one is NULL
  }
  return (!strcmp(s1, s2));
}

void test_ll_append(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_append(NULL, NULL));  // head cannot be NULL

  // It's OK to append NULL. Append to an empty list.
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, NULL));
  TEST_ASSERT_EQUAL_PTR(NULL, head->data);

  // Change list data by hand so that it can be compared to the expected list
  // Compare single-node lists
  head->data = (void *)strs[0];  // Fix up the append of NULL data
  exp_list[0].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Append to a list with one element
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  exp_list[0].next = &exp_list[1];
  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Append to a list with two elements
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[2]));
  exp_list[1].next = &exp_list[2];
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Append again and make sure expected and actual lists are not the same
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
}

void test_ll_prepend(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_prepend(NULL, NULL));  // head cannot be NULL

  // It's OK to prepend NULL. Prepend to an empty list.
  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, NULL));
  TEST_ASSERT_EQUAL_PTR(NULL, head->data);

  // Fix up the append of NULL data and compare to the tail of the expected list
  head->data = (void *)strs[NUM_STRS - 1];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 1], head, strs_equal));

  // Prepend to a list with a single node
  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[NUM_STRS - 2]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 2], head, strs_equal));

  // Prepend to a list with a two nodes
  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[NUM_STRS - 3]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 3], head, strs_equal));
}

void test_ll_set(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_set(NULL, 0, NULL));  // head cannot be NULL

  // It's OK to set data to NULL
  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 0, NULL));
  TEST_ASSERT_EQUAL_PTR(NULL, exp_list[0].data);

  // Set data in the expected list to various values
  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL_STRING(strs[0], (char *)exp_list[0].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 1, (void *)"test"));
  TEST_ASSERT_EQUAL_STRING("test", (char *)exp_list[1].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 2, (void *)"Grey"));
  TEST_ASSERT_EQUAL_STRING("Grey", (char *)exp_list[2].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 3, (void *)"End"));
  TEST_ASSERT_EQUAL_STRING("End", (char *)exp_list[3].data);

  // Test out of bounds index
  TEST_ASSERT_EQUAL(LL_FAIL, ll_set(&exp_list[0], 4, (void *)"Error"));

  // Check integrity of the list data
  TEST_ASSERT_EQUAL_STRING(strs[0], (char *)exp_list[0].data);
  TEST_ASSERT_EQUAL_STRING("test", (char *)exp_list[1].data);
  TEST_ASSERT_EQUAL_STRING("Grey", (char *)exp_list[2].data);
  TEST_ASSERT_EQUAL_STRING("End", (char *)exp_list[3].data);
}

void test_ll_insert_after(void) {
  // head cannot be NULL
  TEST_ASSERT_EQUAL(LL_FAIL, ll_insert_after(NULL, 0, NULL));

  // cannot insert after a non-existent index
  TEST_ASSERT_EQUAL(LL_FAIL, ll_insert_after(&head, 0, NULL));

  // Add a single node and insert a new node after it
  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[2]));

  // At this point the list is {strs[0], strs[2]}, so set exp_list to this
  exp_list[0].next = &exp_list[2];
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Insert between nodes
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[1]));
  exp_list[0].next = &exp_list[1];
  exp_list[1].next = &exp_list[2];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Insert at the tail end of the list
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 2, (void *)strs[3]));
  exp_list[2].next = &exp_list[3];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Insert at the tail end of the list and check that the actual list is not
  // equal to expected
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 3, (void *)strs[0]));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
}

void test_ll_delete(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_delete(NULL, 0));  // head cannot be NULL

  // Delete from an empty list should fail
  TEST_ASSERT_EQUAL(LL_FAIL, ll_delete(&head, 0));

  // Create a list
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[2]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[3]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Delete tail
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 3));
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Delete middle
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 1));
  exp_list[0].next = &exp_list[2];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Delete head
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[2], head, strs_equal));

  // Delete last remaining element
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, head);
}

void test_ll_destroy(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_destroy(NULL));  // head cannot be NULL

  // Destroy a list of several nodes
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[2]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[3]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));
  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
  TEST_ASSERT_EQUAL_PTR(NULL, head);

  // Destroy a list with one node
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
  TEST_ASSERT_EQUAL_PTR(NULL, head);

  // Two (inadvertent) destroys in a row
  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
}

void test_ll_get(void) {
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(NULL, 0));  // head cannot be NULL

  // index outside of range
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(exp_list, 1000));

  // Test that correct data is returned and also that the data pointer is
  // pointing to the right data (i.e. that data was not somehow copied).
  TEST_ASSERT_EQUAL_STRING(strs[0], (char *)ll_get(exp_list, 0));
  TEST_ASSERT_EQUAL_PTR(strs[0], (char *)ll_get(exp_list, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], (char *)ll_get(exp_list, 1));
  TEST_ASSERT_EQUAL_PTR(strs[1], (char *)ll_get(exp_list, 1));
  TEST_ASSERT_EQUAL_STRING(strs[2], (char *)ll_get(exp_list, 2));
  TEST_ASSERT_EQUAL_PTR(strs[2], (char *)ll_get(exp_list, 2));

  // Test on a linked list with a single element
  exp_list[0].next = NULL;
  TEST_ASSERT_EQUAL_STRING(strs[0], (char *)ll_get(&exp_list[0], 0));
  TEST_ASSERT_EQUAL_PTR(strs[0], (char *)ll_get(&exp_list[0], 0));
}

void test_ll_length(void) {
  // Length with a NULL parameter should be 0
  TEST_ASSERT_EQUAL(0, ll_length(NULL));

  // Length of an empty list should be 0
  TEST_ASSERT_EQUAL(0, ll_length(head));

  // Length of expected list is NUM_STRS
  TEST_ASSERT_EQUAL(NUM_STRS, ll_length(&exp_list[0]));

  // Length of 2-node list
  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(2, ll_length(&exp_list[0]));

  // Length of 1-node list
  exp_list[0].next = NULL;
  TEST_ASSERT_EQUAL(1, ll_length(&exp_list[0]));
}

/*
 * Linked list iterator callback that counts number of times it's been called.
 */
enum ll_status count(struct ll_node *node, void *cookie) {
  (void)node;    // stop compiler complaints about unused parameter
  (void)cookie;  // stop compiler complaints about unused parameter

  (*(unsigned int *)(cookie))++;
  return LL_OK;
}

/*
 * Linked list iterator callback that counts number of times it's been called
 * and stops iteration at 2.
 */
enum ll_status stop_at_2(struct ll_node *node, void *cookie) {
  (void)node;  // stop compiler complaints about unused parameter

  (*(unsigned int *)(cookie))++;
  if (*(unsigned int *)(cookie) == 2) {
    return LL_FAIL;
  }
  return LL_OK;
}

/*
 * Test access to linked list data in the iterator. The iterator copies link
 * list data pointers to an array of pointers to strings.
 *
 * Cookie is a tripple char pointer (i.e. a pointer to a pointer to a string)
 */
enum ll_status add_str(struct ll_node *node, void *cookie) {
  char ***str_ptr_ptr = (char ***)(cookie);
  if (node->data == NULL) {
    return LL_FAIL;
  }
  (*(*(str_ptr_ptr))) = node->data;
  (*(str_ptr_ptr))++;
  return LL_OK;
}

void test_ll_iterate(void) {
  char *strs_from_list[NUM_STRS] = {0};
  char **strs_iter = &strs_from_list[0];
  unsigned int cnt = 0;

  // Iterate with NULL parameter. Should not call the callback at all
  ll_iterate(NULL, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  // Iterate over an empty list. Should not call the callback at all
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  // Iterate over the expected list
  cnt = 0;
  ll_iterate(&exp_list[0], count, &cnt);
  TEST_ASSERT_EQUAL(NUM_STRS, cnt);

  // Test terminating the iteration
  cnt = 0;
  ll_iterate(&exp_list[0], stop_at_2, &cnt);
  TEST_ASSERT_EQUAL(2, cnt);

  // Test access to node data inside the callback
  ll_iterate(&exp_list[0], add_str, &strs_iter);
  for (int i = 0; i < NUM_STRS; i++) {
    TEST_ASSERT_EQUAL_STRING(strs[i], strs_from_list[i]);
  }

  // Iterate over a list with a single node
  exp_list[0].next = NULL;
  cnt = 0;
  ll_iterate(&exp_list[0], count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
}

// Miscellaneous tests designed to test (non-exhaustively) list operations done
// sequentially in case there are any odd side effects from one function
// to another.
void test_misc(void) {
  unsigned int cnt = 0;

  // Iterate over an empty list
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  // Append to an empty list. Test append, length, get, iteration
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[1], head, strs_equal));

  // Prepend to a 1-node list. Test prepend, length, get, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(2, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 1));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 2));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(2, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Delete head node. Test delete, length, get, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[1], head, strs_equal));

  // Chagne node 0 data. Test length, get, out-of-bounds get, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_set(head, 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);

  // Append 2 nodes and insert another. Test append, insert, length, get,
  // out-of-bounds get, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[3]));
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 1, (void *)strs[2]));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 1));
  TEST_ASSERT_EQUAL_STRING(strs[2], ll_get(head, 2));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 4));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  exp_list[1].next = &exp_list[2];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Insert after head. Test insert, length
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL(5, ll_length(head));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));

  // Delete head, test delete, length, get
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 1));
  TEST_ASSERT_EQUAL_STRING(strs[2], ll_get(head, 2));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Delete last element. Test delete, length, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 3));
  TEST_ASSERT_EQUAL(3, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(3, cnt);
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Append. Test append, length, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 3));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  exp_list[2].next = &exp_list[3];
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));

  // Change tail's data. Test set, length, iterate
  TEST_ASSERT_EQUAL(LL_OK, ll_set(head, 3, (void *)strs[3]));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  // Destroy the list. Test destroy, length, iterate over empty list
  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 3));
  TEST_ASSERT_EQUAL(0, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  // Create another list. Test whether a pointer that used to be a list that was
  // destroyed can still be used for a new list
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[2]));
  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[3]));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ll_get);
  RUN_TEST(test_ll_length);
  RUN_TEST(test_ll_iterate);

  RUN_TEST(test_ll_append);
  RUN_TEST(test_ll_prepend);
  RUN_TEST(test_ll_set);
  RUN_TEST(test_ll_insert_after);
  RUN_TEST(test_ll_delete);
  RUN_TEST(test_ll_destroy);

  RUN_TEST(test_misc);

  return UNITY_END();
}