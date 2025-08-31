#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct LinkedList {
    int len;
    struct Node *head;
    struct Node *tail;
};

struct LinkedList create_empty_linked_list() {
    struct LinkedList list = { 0, NULL, NULL };
    return list;
}

struct Node *create_node(int val) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = val;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

bool linked_list_append(struct LinkedList *list, int val) {
    struct Node *node = create_node(val);

    // if we failed to create the node, return false
    // or if we were given a blank list, return false
    if (node == NULL || list == NULL) {
        return false;
    }

    // append to an empty list
    if (list->len == 0) {
        list->head = node;
        list->tail = list->head;
        list->len = list->len + 1;

        return true;
    }

    // append to a non-empty list
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;

    // increase length by one
    list->len = list->len + 1;

    return true;
}

bool linked_list_prepend(struct LinkedList *list, int val) {
    struct Node *node = create_node(val);

    // if we failed to create the node, return false
    // or if we were given a blank list, return false
    if (node == NULL || list == NULL) {
        return false;
    }

    // prepend to an empty list
    if (list->len == 0) {
        list->head = node;
        list->tail = list->head;
        list->len = list->len + 1;

        return true;
    }

    // prepend to a non-empty list
    list->head->prev = node;
    node->next = list->head;
    list->head = node;

    // increase length by one
    list->len = list->len + 1;

    return true;
}

struct LinkedList create_linked_list(int *vals, int len) {
    struct LinkedList list = create_empty_linked_list();

    // append all elements of the list into the linked list
    for (int i = 0; i < len; i++) {
        linked_list_append(&list, vals[i]);
    }

    return list;
}

void empty_linked_list(struct LinkedList *list) {
    if (list->len == 0) {
        return;
    }

    // free the entire list, iterating through
    struct Node *current = list->head;
    while (current->next != NULL) {        
        current = current->next;
        free(current->prev);
    }

    free(current);
    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
    return;
}

void print_linked_list(struct LinkedList *list) {
    int index = 0;
    struct Node *current = list->head;
    while (current->next != NULL) {
        printf("Node Index %d, Node Value %d\n", index, current->data);

        ++index;
        current = current->next;
    }

    printf("Node Index %d, Node Value %d\n", index, current->data);
}

bool linked_list_contains(struct LinkedList *list, int val) {
    if (list->len == 0) {
        return false;
    }

    struct Node *current = list->head;
    while (current->next != NULL) {
        if (current->data == val) {
            return true;
        }
        
        current = current->next;
    }

    if (current->data == val) {
        return true;
    }

    return false;
}

struct Node *linked_list_get(struct LinkedList *list, int index) {
    if (list == NULL) {
        return NULL;
    }
    
    int len = list->len;

    if (len == 0 || index < 0 || index >= len) {
        return NULL;
    }

    // get value using forward/reverse iteration
    // depending on whether the index is closer to the
    // head or tail of the linked list
    int mid = len / 2;
    struct Node *current;
    if (index <= mid) {
        current = list->head;
        for (int i = 0; i <= mid; i++) {
            if (i == index) {
                return current;
            }

            current = current->next;
        }
    } else {
        current = list->tail;
        for (int i = len - 1; i > mid; i--) {
            if (i == index) {
                return current;
            }

            current = current->prev;
        }
    }

    return NULL;
}

// TODO: Implement insertion, removal methods

int main(void) {

    int arr[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int len = 12;
    struct LinkedList list = create_linked_list(arr, len);

    printf("Linked list length: %d\n", list.len);
    print_linked_list(&list);
    printf("\n");

    // print in reverse to verify reverse traversal works
    struct Node *current = list.tail;
    int index = list.len - 1;
    printf("Reverse traversal check\n");
    while (current->prev != NULL) {
        printf("Node Index %d, Node Value %d\n", index, current->data);

        index--;
        current = current->prev;
    }
    printf("Node Index %d, Node Value %d\n", index, current->data);
    printf("\n");

    // check prepending to a linked list
    linked_list_prepend(&list, 99);
    print_linked_list(&list);
    printf("\n");

    // check contains funtion
    int a = 28;
    int b = 99;
    printf("Linked List contains val %d: (0 / 1) %d\n", a, linked_list_contains(&list, a));
    printf("Linked List contains val %d: (0 / 1) %d\n", b, linked_list_contains(&list, b));
    printf("\n");

    // check get function
    int index_a = 6;
    int index_b = 2;
    int index_c = 15;
    struct Node *node_a = linked_list_get(&list, index_a);
    struct Node *node_b = linked_list_get(&list, index_b);
    struct Node *node_c = linked_list_get(&list, index_c);
    if (node_a != NULL) {
        printf("Linked List val %d at index %d\n", node_a->data, index_a);
    } else {
        printf("Linked List val at index %d not found\n", index_a);
    }
    if (node_b != NULL) {
        printf("Linked List val %d at index %d\n", node_b->data, index_b);
    } else {
        printf("Linked List val at index %d not found\n", index_b);
    }
    if (node_c != NULL) {
        printf("Linked List val %d at index %d\n", node_c->data, index_c);
    } else {
        printf("Linked List val at index %d not found\n", index_c);
    }
    printf("\n");

    // free list once done
    empty_linked_list(&list);

    return 0;
}