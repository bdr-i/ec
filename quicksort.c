#include <stdlib.h>
#include "listechaine.h"
#include "quicksort.h"

void partition(Node* start, Node* end, Node** pivotRef) {
    if (!start || start == end) {
        *pivotRef = start;
        return;
    }

    int pivotValue = end->val;
    Node* p = start;
    Node* prev = NULL;
    Node* curr = start;

    while (curr != end) {
        if (curr->val < pivotValue) {
            // Échanger les valeurs de curr et p
            int temp = curr->val;
            curr->val = p->val;
            p->val = temp;

            prev = p;
            p = p->next;
        }
        curr = curr->next;
    }

    // Échanger la valeur de p (pivot final) avec end
    int temp = p->val;
    p->val = end->val;
    end->val = temp;

    *pivotRef = p;
}


// Fusionne deux listes
Node* concat(Node* less, Node* equal, Node* greater) {
    Node* head = NULL, * tail = NULL;
    Node* lists[] = { less, equal, greater };
    for (int i = 0; i < 3; ++i) {
        if (lists[i]) {
            if (!head) {
                head = tail = lists[i];
            }
            else {
                tail->next = lists[i];
            }
            while (tail->next) tail = tail->next;
        }
    }
    return head;
}

// Tri rapide r�cursif
Node* quicksort_recursive(Node* head) {
    if (!head || !head->next) return head;

    int pivot = head->val;
    Node* less = NULL, * equal = NULL, * greater = NULL;
    while (head) {
        Node* next = head->next;
        if (head->val < pivot) {
            head->next = less;
            less = head;
        }
        else if (head->val == pivot) {
            head->next = equal;
            equal = head;
        }
        else {
            head->next = greater;
            greater = head;
        }
        head = next;
    }

    less = quicksort_recursive(less);
    greater = quicksort_recursive(greater);
    return concat(less, equal, greater);
}
void quicksort_iterative(Node** headRef) {
    if (!headRef || !*headRef || !(*headRef)->next) return;

    typedef struct {
        Node* start;
        Node* end;
    } StackItem;

    StackItem stack[100];
    int top = -1;

    Node* start = *headRef;
    Node* end = *headRef;
    while (end->next) end = end->next;

    stack[++top] = (StackItem){start, end};

    while (top >= 0) {
        StackItem current = stack[top--];
        start = current.start;
        end = current.end;

        if (!start || start == end || start == end->next)
            continue;

        Node* pivot = NULL;
        partition(start, end, &pivot);

        Node* temp = start;
        Node* prev = NULL;
        while (temp && temp != pivot) {
            prev = temp;
            temp = temp->next;
        }

        if (prev && start != pivot) {
            stack[++top] = (StackItem){start, prev};
        }

        if (pivot && pivot->next && pivot->next != end->next) {
            stack[++top] = (StackItem){pivot->next, end};
        }
    }
}
