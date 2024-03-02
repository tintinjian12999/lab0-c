#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(*head));
    if (!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    element_t *node, *safe;
    list_for_each_entry_safe (node, safe, head, list)
        q_release_element(node);
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_element = malloc(sizeof(*new_element));
    if (!new_element)
        return false;
    new_element->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    strncpy(new_element->value, s, strlen(s) + 1);
    list_add(&new_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_element = malloc(sizeof(*new_element));
    if (!new_element)
        return false;
    new_element->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    strncpy(new_element->value, s, strlen(s) + 1);
    list_add_tail(&new_element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *temp = list_first_entry(head, element_t, list);
    list_del(head->next);
    if (sp != NULL && bufsize != 0)
        strncpy(sp, temp->value, bufsize);
    return temp;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *temp = list_last_entry(head, element_t, list);
    list_del(head->prev);
    if (sp != NULL && bufsize != 0)
        strncpy(sp, temp->value, bufsize);
    return temp;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;
    struct list_head *node;
    int count = 0;
    list_for_each (node, head)
        count++;
    return count;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;
    struct list_head *slow = head->next, *fast = head->next;
    while (fast != head && fast->next != head) {
        fast = fast->next->next;
        slow = slow->next;
    }
    list_del(slow);
    q_release_element(list_entry(slow, element_t, list));
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (head == NULL || list_empty(head) || list_is_singular(head))
        return false;
    struct list_head *node = head->next;
    bool dup = false;
    while (node->next != NULL) {
        if (strcmp(list_entry(node, element_t, list)->value,
                   list_entry(node->next, element_t, list)->value) == 0) {
            dup = true;
            list_del(node);
            q_release_element(list_entry(node, element_t, list));
        } else if (dup) {
            dup = false;
            list_del(node);
            q_release_element(list_entry(node, element_t, list));
        }
    }
    if (dup) {
        list_del(node);
        q_release_element(list_entry(node, element_t, list));
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;
    struct list_head *node;
    for (node = head->next; node != head && node->next != head;
         node = node->next)
        list_move(node, node->next);
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    struct list_head *node = head->next;
    while (node->next != head)
        list_move(node->next, head);
}


/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    if (!head || list_empty(head) || list_is_singular(head))
        return;
    int count = 0;
    struct list_head *node, *safe, *head_to = q_new(), *head_from = head;
    list_for_each_safe (node, safe, head) {
        count++;
        if (count == k) {
            list_cut_position(head_to, head_from, node);
            q_reverse(head_to);
            list_splice_init(head_to, head_from);
            count = 0;
            head_from = safe->prev;
        }
    }
}


/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
