#include "selection.h"
#include <stdlib.h>
#include "listechaine.h"

// Tri par sélection - version itérative
void selectionSortIterative(Node* head) {
    for (Node* i = head; i != NULL && i->next != NULL; i = i->next) {
        Node* min = i;
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (j->val < min->val) {
                min = j;
            }
        }
        if (min != i) {
            int temp = i->val;
            i->val = min->val;
            min->val = temp;
        }
    }
}

// Tri par sélection - version récursive
void selectionSortRecursive(Node* head) {
    if (!head || !head->next) return;

    Node* min = head;
    for (Node* j = head->next; j != NULL; j = j->next) {
        if (j->val < min->val) {
            min = j;
        }
    }

    if (min != head) {
        int temp = head->val;
        head->val = min->val;
        min->val = temp;
    }

    selectionSortRecursive(head->next);
}
