#include <stdlib.h>
#include "listechaine.h"
#include "quicksort.h"

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

// Tri rapide récursif
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


Node* quicksort_iterative(Node* head) {
    if (!head || !head->next) return head;

    Node* unsorted = head;
    Node* sorted = NULL;

    // Utilisé pour stocker temporairement des morceaux à trier
    Node* pending = NULL;

    // Ajouter la liste entière dans pending
    unsorted->next = NULL;
    pending = unsorted;

    while (pending) {
        // Extraire une sous-liste de pending
        Node* current = pending;
        pending = pending->next;
        current->next = NULL;

        if (!current->next) {
            // Ajouter l’élément seul à sorted
            current->next = sorted;
            sorted = current;
            continue;
        }

        // Pivot et partition
        int pivot = current->val;
        Node* less = NULL, * equal = NULL, * greater = NULL;

        while (current) {
            Node* next = current->next;
            if (current->val < pivot) {
                current->next = less;
                less = current;
            }
            else if (current->val == pivot) {
                current->next = equal;
                equal = current;
            }
            else {
                current->next = greater;
                greater = current;
            }
            current = next;
        }

        // Ajouter les parties à traiter plus tard (less et greater) à pending
        if (greater) {
            Node* tail = greater;
            while (tail->next) tail = tail->next;
            tail->next = pending;
            pending = greater;
        }

        if (less) {
            Node* tail = less;
            while (tail->next) tail = tail->next;
            tail->next = pending;
            pending = less;
        }

        // Ajouter les éléments égaux (déjà triés) à sorted
        if (equal) {
            Node* tail = equal;
            while (tail->next) tail = tail->next;
            tail->next = sorted;
            sorted = equal;
        }
    }

    return sorted;
}

