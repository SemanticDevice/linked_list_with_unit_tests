#include "linked_list.h"
#include "unity.h"

struct ll_node *head = NULL;

void setUp(void) {}

void tearDown(void) {}

void test_ll_append(void) {}
void test_ll_prepend(void) {}
void test_ll_insert_after(void) {}
void test_ll_delete(void) {}
void test_ll_length(void) {}
void test_ll_iterate(void) {}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_ll_append);
  RUN_TEST(test_ll_prepend);
  RUN_TEST(test_ll_insert_after);
  RUN_TEST(test_ll_delete);
  RUN_TEST(test_ll_length);
  RUN_TEST(test_ll_iterate);

  return UNITY_END();
}