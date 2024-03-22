/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_LIST_SORT_H
#define _LINUX_LIST_SORT_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

struct list_head;

typedef int
    __attribute__((nonnull(1, 2))) (*list_cmp_func_t)(const struct list_head *,
                                                      const struct list_head *,
                                                      bool);

__attribute__((nonnull(1, 2))) void list_sort(struct list_head *head,
                                              list_cmp_func_t cmp,
                                              bool descend);
__attribute__((nonnull(1, 2))) int cmp(const struct list_head *left,
                                       const struct list_head *right,
                                       bool descend);


#endif
