#include "linked_list.h"

enum ll_status ll_append(struct ll_node **head, void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

/**
 * Prepend @p data to the head of the list. I.e. insert before the head.
 */
enum ll_status ll_prepend(struct ll_node **head, void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}

/**
 * Insert @p data after the list node at index @p idx.
 */
enum ll_status ll_insert_after(struct ll_node **head, unsigned int idx,
                               void *data) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)idx;   // temp to prevent compiler complaining about unused parameter
  (void)data;  // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}
/**
 * Delete list node at index @p idx.
 */
enum ll_status ll_delete(struct ll_node **head, unsigned int idx) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)idx;   // temp to prevent compiler complaining about unused parameter
  return LL_OK;
}
/**
 * Return number of nodes in the list.
 */
unsigned int ll_length(struct ll_node *head) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  return 0;
}
/**
 * Iterate over the list calling @p cb function at every node until every node
 * is visited or until the @p cb function returns LL_FAIL to indicate that the
 * iteration should stop.
 */
void ll_iterate(struct ll_node *head,
                enum ll_status (*cb)(struct ll_node *node)) {
  (void)head;  // temp to prevent compiler complaining about unused parameter
  (void)cb;    // temp to prevent compiler complaining about unused parameter
  return;
}