#include <stdlib.h>
#include "listechaine.h"
#include "mergesort.h"

// Fusionne deux listes triées
Node* merge(Node* l1, Node* l2) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// Découpe une liste en deux
void split(Node* head, Node** front, Node** back) {
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

// Tri fusion récursif
Node* mergesort_recursive(Node* head) {
    if (!head || !head->next) return head;

    Node* front, * back;
    split(head, &front, &back);
    front = mergesort_recursive(front);
    back = mergesort_recursive(back);
    return merge(front, back);
}


// Tri fusion itératif (bottom-up)
Node* mergesort_iterative(Node* head) {
    if (!head || !head->next) return head;

    int n = list_length(head);
    Node* dummy = create_node(0);
    dummy->next = head;

    for (int size = 1; size < n; size *= 2) {
        Node* curr = dummy->next;
        Node* tail = dummy;

        while (curr) {
            Node* left = curr;
            Node* right = NULL;
            Node* next = NULL;

            int i = 1;
            while (i < size && curr->next) {
                curr = curr->next;
                i++;
            }

            right = curr->next;
            curr->next = NULL;
            curr = right;

            i = 1;
            while (i < size && curr && curr->next) {
                curr = curr->next;
                i++;
            }

            if (curr) {
                next = curr->next;
                curr->next = NULL;
            }

            Node* merged = merge(left, right);
            tail->next = merged;
            while (tail->next) tail = tail->next;
            curr = next;
        }
    }

    Node* sorted = dummy->next;
    free(dummy);
    return sorted;
}
