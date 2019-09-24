#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

enum ll_status ll_append(struct ll_node **head, void *data) {
  if (head == NULL) {
    return LL_FAIL;
  }

  struct ll_node *new = malloc(sizeof(struct ll_node));
  if (new == NULL) {
    return LL_FAIL;
  }
  new->data = data;
  new->next = NULL;

  if (*head == NULL) {
    *head = new;
    return LL_OK;
  }

  struct ll_node *n = *head;
  while (n->next != NULL) {
    n = n->next;
  }
  n->next = new;

  return LL_OK;
}

enum ll_status ll_prepend(struct ll_node **head, void *data) {
  if (head == NULL) {
    return LL_FAIL;
  }

  struct ll_node *new = malloc(sizeof(struct ll_node));
  if (new == NULL) {
    return LL_FAIL;
  }
  new->data = data;
  new->next = *head;

  *head = new;

  return LL_OK;
}

enum ll_status ll_set(struct ll_node *head, unsigned int idx, void *data) {
  unsigned int i = 0;

  while (head != NULL && i < idx) {
    i++;
    head = head->next;
  }

  if (head != NULL) {
    head->data = data;
    return LL_OK;
  }

  return LL_FAIL;
}

enum ll_status ll_insert_after(struct ll_node **head, unsigned int idx,
                               void *data) {
  // Cannot insert after anything if list is empty, which means head could be
  // a single pointer since the head is not going to be modified because
  // inserting after precludes inserting before the head of the list. Double
  // pointer is being kept for consistency with other node creating functions.
  if (head == NULL || *head == NULL) {
    return LL_FAIL;
  }

  unsigned int i = 0;
  struct ll_node *n = *head;
  while (n != NULL && i < idx) {
    i++;
    n = n->next;
  }

  if (i == idx && n != NULL) {
    struct ll_node *new = malloc(sizeof(struct ll_node));
    if (new == NULL) {
      return LL_FAIL;
    }
    new->data = data;
    new->next = n->next;
    n->next = new;
  } else {
    return LL_FAIL;
  }

  return LL_OK;
}

enum ll_status ll_delete(struct ll_node **head, unsigned int idx) {
  if (head == NULL || *head == NULL) {
    return LL_FAIL;
  }

  unsigned int i = 0;
  struct ll_node *n = *head;
  struct ll_node *p = *head;

  // Delete head
  if (idx == 0) {
    *head = (*head)->next;
    free(n);
    return LL_OK;
  }

  while (p != NULL && n != NULL && i < idx) {
    i++;
    p = n;
    n = n->next;
  }

  if (i == idx && p != NULL && n != NULL) {
    p->next = n->next;
    free(n);
  } else {
    return LL_FAIL;
  }

  return LL_OK;
}

enum ll_status ll_destroy(struct ll_node **head) {
  if (head == NULL) {
    return LL_FAIL;
  }
  struct ll_node *n = *head;
  struct ll_node *t = *head;
  while (n != NULL) {
    t = n;
    n = n->next;
    free(t);
  }

  *head = NULL;
  return LL_OK;
}

void *ll_get(struct ll_node *head, unsigned int idx) {
  unsigned int i = 0;
  while (head != NULL && i < idx) {
    i++;
    head = head->next;
  }

  if (head != NULL && head->data != NULL) {
    return head->data;
  } else {
    return NULL;
  }
}

unsigned int ll_length(struct ll_node *head) {
  unsigned int i = 0;
  while (head != NULL) {
    i++;
    head = head->next;
  }
  return i;
}

void ll_iterate(struct ll_node *head,
                enum ll_status (*cb)(struct ll_node *node, void *cookie),
                void *cookie) {
  while (head != NULL) {
    if (cb(head, cookie) == LL_FAIL) {
      return;
    }
    head = head->next;
  }
}