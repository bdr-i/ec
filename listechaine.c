#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listechaine.h"

Node* create_node(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) exit(EXIT_FAILURE);
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

void appendNode(Node** head, int val) {
    Node* new_node = create_node(val);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

void print_list(Node* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int list_length(Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

void generate_random_list(Node** head, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        int val = rand() % 10;  
        appendNode(head, val);
    }
}
