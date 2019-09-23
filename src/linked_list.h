/**
 * @file
 *
 * Implementation of a linked list that is agnostic to the type of data stored
 * in the list (a.k.a. generic linked list).
 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct ll_node {
  void *data;
  struct ll_node *next;
};

enum ll_status { LL_OK, LL_FAIL };

/**
 * Append @p data to the tail of the linked list.
 */
enum ll_status ll_append(struct ll_node **head, void *data);

/**
 * Prepend @p data to the head of the list. I.e. insert before the head.
 */
enum ll_status ll_prepend(struct ll_node **head, void *data);

/**
 * Insert @p data after the list node at index @p idx.
 */
enum ll_status ll_insert_after(struct ll_node **head, unsigned int idx,
                               void *data);

/**
 * Delete list node at index @p idx.
 */
enum ll_status ll_delete(struct ll_node **head, unsigned int idx);

/**
 * Destroy the whole list. Dealocate memory allocated for the list.
 */
enum ll_status ll_destroy(struct ll_node **head);

/**
 * Return node data at index specified by @p idx. Return NULL if @p idx is out
 * of range.
 */
void *ll_get(struct ll_node *head, unsigned int idx);

/**
 * Return number of nodes in the list.
 */
unsigned int ll_length(struct ll_node *head);

/**
 * Iterate over the list calling @p cb function at every node until every node
 * is visited or until the @p cb function returns LL_FAIL to indicate that the
 * iteration should stop.
 */
void ll_iterate(struct ll_node *head,
                enum ll_status (*cb)(struct ll_node *node));

#endif  // LINKED_LIST_H