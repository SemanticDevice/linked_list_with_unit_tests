#include "linked_list.h"
#include <stdio.h>

enum ll_status ll_append(struct ll_node **head, void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

enum ll_status ll_prepend(struct ll_node **head, void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

enum ll_status ll_insert_after(struct ll_node **head, unsigned int idx,
                               void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)idx;   // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

enum ll_status ll_delete(struct ll_node **head, unsigned int idx) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)idx;   // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

void *ll_get(struct ll_node *head, unsigned int idx) {
  (void)head;
  (void)idx;
  return NULL;
}

unsigned int ll_length(struct ll_node *head) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  return 0;
}

void ll_iterate(struct ll_node *head,
                enum ll_status (*cb)(struct ll_node *node)) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)cb;    // temp to prevent compiler complaining about unused parameter
  return;
}