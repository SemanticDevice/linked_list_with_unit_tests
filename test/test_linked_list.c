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

// Hand-made expected that is compared to actual list produced via the linked
// list API
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

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, NULL));  // it's OK to append NULL
  TEST_ASSERT_EQUAL_PTR(NULL, head->data);
  head->data = (void *)strs[0];  // Fix up the append of NULL data
  exp_list[0].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  exp_list[0].next = &exp_list[1];
  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[2]));
  exp_list[1].next = &exp_list[2];
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
}

void test_ll_prepend(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_prepend(NULL, NULL));  // head cannot be NULL

  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, NULL));  // it's OK to prepend NULL
  TEST_ASSERT_EQUAL_PTR(NULL, head->data);
  head->data = (void *)strs[NUM_STRS - 1];  // Fix up the append of NULL data
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 1], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[NUM_STRS - 2]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 2], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[NUM_STRS - 3]));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[NUM_STRS - 3], head, strs_equal));
}

void test_ll_set(void) {
  TEST_ASSERT_EQUAL(LL_FAIL, ll_set(NULL, 0, NULL));  // head cannot be NULL

  // It's OK to set data to NULL
  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 0, NULL));
  TEST_ASSERT_EQUAL_PTR(NULL, exp_list[0].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL_STRING(strs[0], (char *)exp_list[0].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 1, (void *)"test"));
  TEST_ASSERT_EQUAL_STRING("test", (char *)exp_list[1].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 2, (void *)"Grey"));
  TEST_ASSERT_EQUAL_STRING("Grey", (char *)exp_list[2].data);

  TEST_ASSERT_EQUAL(LL_OK, ll_set(&exp_list[0], 3, (void *)"End"));
  TEST_ASSERT_EQUAL_STRING("End", (char *)exp_list[3].data);

  // Out of bounds index
  TEST_ASSERT_EQUAL(LL_FAIL, ll_set(&exp_list[0], 4, (void *)"Error"));
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

  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[2]));
  // At this point the list is {strs[0], strs[2]}, so set exp_list to this
  exp_list[0].next = &exp_list[2];
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[1]));
  exp_list[0].next = &exp_list[1];
  exp_list[1].next = &exp_list[2];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 2, (void *)strs[3]));
  exp_list[2].next = &exp_list[3];
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

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
  TEST_ASSERT_EQUAL(0, ll_length(NULL));

  TEST_ASSERT_EQUAL(NUM_STRS, ll_length(&exp_list[0]));

  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(2, ll_length(&exp_list[0]));

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

  ll_iterate(NULL, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  cnt = 0;
  ll_iterate(&exp_list[0], count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);

  cnt = 0;
  ll_iterate(&exp_list[0], stop_at_2, &cnt);
  TEST_ASSERT_EQUAL(2, cnt);

  ll_iterate(&exp_list[0], add_str, &strs_iter);
  for (int i = 0; i < NUM_STRS; i++) {
    TEST_ASSERT_EQUAL_STRING(strs[i], strs_from_list[i]);
  }

  exp_list[0].next = NULL;
  cnt = 0;
  ll_iterate(&exp_list[0], count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
}

void test_misc(void) {
  unsigned int cnt = 0;

  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[1]));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
  exp_list[1].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[1], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_prepend(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL(2, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 1));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 2));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(2, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[1], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_set(head, 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL(1, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 1));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(1, cnt);

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

  TEST_ASSERT_EQUAL(LL_OK, ll_insert_after(&head, 0, (void *)strs[0]));
  TEST_ASSERT_EQUAL(5, ll_length(head));
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));
  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 0));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 0));
  TEST_ASSERT_EQUAL_STRING(strs[1], ll_get(head, 1));
  TEST_ASSERT_EQUAL_STRING(strs[2], ll_get(head, 2));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_delete(&head, 3));
  TEST_ASSERT_EQUAL(3, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(3, cnt);
  exp_list[2].next = NULL;
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_append(&head, (void *)strs[0]));
  TEST_ASSERT_EQUAL_STRING(strs[0], ll_get(head, 3));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  exp_list[2].next = &exp_list[3];
  TEST_ASSERT_EQUAL(0, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_set(head, 3, (void *)strs[3]));
  TEST_ASSERT_EQUAL_STRING(strs[3], ll_get(head, 3));
  TEST_ASSERT_EQUAL(4, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(4, cnt);
  TEST_ASSERT_EQUAL(1, lists_equal(&exp_list[0], head, strs_equal));

  TEST_ASSERT_EQUAL(LL_OK, ll_destroy(&head));
  TEST_ASSERT_EQUAL_PTR(NULL, ll_get(head, 3));
  TEST_ASSERT_EQUAL(0, ll_length(head));
  cnt = 0;
  ll_iterate(head, count, &cnt);
  TEST_ASSERT_EQUAL(0, cnt);

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