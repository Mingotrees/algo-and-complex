#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SKIPLIST_ALLOW_FORWARD_FIX
#endif

#define forward next
#define SKIPLIST_NO_MAIN
#include "skip.c"

static void init_skiplist(Skiplist *list, int max_level, float p) {
    list->max_level = max_level;
    list->level = 0;
    list->p = p;
    list->header = createNode(INT_MIN, max_level);
    for (int i = 0; i <= max_level; i++) {
        list->header->next[i] = NULL;
    }
}

static void free_skiplist(Skiplist *list) {
    List curr = list->header->next[0];
    while (curr != NULL) {
        List next = curr->next[0];
        free(curr->next);
        free(curr);
        curr = next;
    }
    free(list->header->next);
    free(list->header);
    list->header = NULL;
}

static int contains_level0(Skiplist *list, int value) {
    List curr = list->header->next[0];
    while (curr != NULL) {
        if (curr->data == value) {
            return 1;
        }
        curr = curr->next[0];
    }
    return 0;
}

static void print_check(const char *label, int expected, int actual) {
    printf("%s: expected=%d actual=%d %s\n", label, expected, actual,
           (expected == actual) ? "[OK]" : "[FAIL]");
}

static void test_insert_increases_level(void) {
    Skiplist list;
    init_skiplist(&list, 4, 1.0f);

    insert(&list, 10);

    print_check("level after insert (p=1.0)", 4, list.level);

    free_skiplist(&list);
}

static void test_insert_delete_roundtrip(void) {
    Skiplist list;
    init_skiplist(&list, 3, 0.0f);

    insert(&list, 3);
    insert(&list, 1);
    insert(&list, 2);

    print_check("contains 1 after insert", 1, contains_level0(&list, 1));
    print_check("contains 2 after insert", 1, contains_level0(&list, 2));
    print_check("contains 3 after insert", 1, contains_level0(&list, 3));

    deleteNode(&list, 2);

    print_check("contains 2 after delete", 0, contains_level0(&list, 2));
    print_check("contains 1 after delete", 1, contains_level0(&list, 1));
    print_check("contains 3 after delete", 1, contains_level0(&list, 3));

    free_skiplist(&list);
}

static void test_random_level_bounds(void) {
    Skiplist list;
    init_skiplist(&list, 5, 1.0f);

    int lvl = randomLevel(&list);
    printf("random level bounds: expected in [0,%d] actual=%d %s\n",
           list.max_level, lvl,
           (lvl >= 0 && lvl <= list.max_level) ? "[OK]" : "[FAIL]");

    free_skiplist(&list);
}

#define RUN_TEST(fn) do { \
    printf("[TEST] %s\n", #fn); \
    fn(); \
} while (0)

int main(void) {
    RUN_TEST(test_insert_increases_level);
    RUN_TEST(test_insert_delete_roundtrip);
    RUN_TEST(test_random_level_bounds);

    return 0;
}
