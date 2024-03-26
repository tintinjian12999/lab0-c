#include "shuffle.h"
#include <stdlib.h>
#include "queue.h"

void q_shuffle(struct list_head *head)
{
    if (!head || list_is_singular(head) || list_empty(head))
        return;
    struct list_head *finished_node = head;
    int len = q_size(head);
    while (len > 0) {
        int new = rand() % len;
        struct list_head *new_node = head->next;
        struct list_head *old_node = finished_node->prev;
        while (new --)
            new_node = new_node->next;
        swap(old_node, new_node);
        old_node = old_node->prev;
        finished_node = finished_node->prev;
        len--;
    }
    return;
}

void swap(struct list_head *n1, struct list_head *n2)
{
    if (n1 == n2)
        return;

    struct list_head *n1_prev = n1->prev;
    struct list_head *n2_prev = n2->prev;

    if (n1->prev != n2)
        list_move(n2, n1_prev);

    list_move(n1, n2_prev);
}
