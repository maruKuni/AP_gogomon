#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/*
2014Autumun
連結リストのマージソート．
もうメモリリークしてないはず
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
Node *divide(Node *head) {
    Node *head1 = head;
    Node *head2 = head1->next;
    Node *ret;
    if (head2 != NULL) {
        head2 = head2->next;
    }

    while (head2 != NULL) {
        head1 = head1->next;
        head2 = head2->next;
        if (head2 != NULL) {
            head2 = head2->next;
        }
    }
    ret = head1->next;
    head1->next = NULL;
    return ret;
}
Node *merge(Node *a, Node *b) {
    List l;
    l.head = NULL;
    while (a != NULL && b != NULL) {
        if (a->value <= b->value) {
            add_list(&l, a->value);
            a = a->next;

        } else {
            add_list(&l, b->value);
            b = b->next;
        }
    }
    while (a != NULL) {
        add_list(&l, a->value);
        a = a->next;
    }
    while (b != NULL) {
        add_list(&l, b->value);
        b = b->next;
    }
    // 途中経過表示用
    // print_list(p);
    return l.head;
}
Node *sort(Node *head) {
    if (head->next == NULL) {
        return head;
    }
    Node *d = divide(head);
    d = sort(d);
    head = sort(head);

    return merge(head, d);
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
    init_list(&s);
    add_list(l, 6);
    add_list(l, 4);
    add_list(l, 3);
    add_list(l, 8);
    add_list(l, 7);
    add_list(l, 2);
    add_list(l, 1);
    add_list(l, 5);

    s->head = sort(l->head);
    print_list(s);
}