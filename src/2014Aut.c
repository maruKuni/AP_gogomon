#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/*
2014Autumun
連結リストのマージソート．
これメモリリークしてんね（私の実装の問題です）．
divide, merge, sortはNode *を受け取る実装にするべきだった．
*/
typedef struct Node {
    uint64_t value;
    struct Node *next;
} Node;
typedef struct List {
    Node *head;
} List;

void print_list(List *l);
void init_list(List **l) {
    *l = malloc(sizeof(List));
    (*l)->head = NULL;
}
void add_list(List *l, size_t value) {
    if (l->head == NULL) {
        l->head = malloc(sizeof(Node));
        l->head->next = NULL;
        l->head->value = value;
        return;
    }
    Node *tmp = l->head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(Node));
    tmp->next->next = NULL;
    tmp->next->value = value;
}
List *divide(List *l) {
    Node *head = l->head;
    Node *head2 = head->next;
    List *ret;
    init_list(&ret);
    if (head2 != NULL) {
        head2 = head2->next;
    }

    while (head2 != NULL) {
        head = head->next;
        head2 = head2->next;
        if (head2 != NULL) {
            head2 = head2->next;
        }
    }
    ret->head = head->next;
    head->next = NULL;
    return ret;
}
List *merge(List *a, List *b) {
    List *p;
    init_list(&p);
    Node *head_a = a->head;
    Node *head_b = b->head;
    while (head_a != NULL && head_b != NULL) {
        if (head_a->value <= head_b->value) {
            add_list(p, head_a->value);
            head_a = head_a->next;

        } else {
            add_list(p, head_b->value);
            head_b = head_b->next;
        }
    }
    while (head_a != NULL) {
        add_list(p, head_a->value);
        head_a = head_a->next;
    }
    while (head_b != NULL) {
        add_list(p, head_b->value);
        head_b = head_b->next;
    }
    // 途中経過表示用
    // print_list(p);
    return p;
}
List *sort(List *l) {
    if (l->head->next == NULL) {
        return l;
    }
    List *d = divide(l);
    d = sort(d);
    l = sort(l);

    return merge(l, d);
}
void print_list(List *l) {
    Node *head = l->head;
    while (head != NULL) {
        printf("%c%zu", (head == l->head) ? '\0' : '-', head->value);
        head = head->next;
    }
    printf("\n");
}
int main() {
    List *l, *s;
    init_list(&l);
    add_list(l, 6);
    add_list(l, 4);
    add_list(l, 3);
    add_list(l, 8);
    add_list(l, 7);
    add_list(l, 2);
    add_list(l, 1);
    add_list(l, 5);

    s = sort(l);
    print_list(s);
}