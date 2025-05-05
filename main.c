#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listechaine.h"
#include "selection.h"
#include "quicksort.h"
#include "mergesort.h"

// Génère une liste chaînée aléatoire de taille n (valeurs 0-99)
Node* generateRandomList(int n) {
    Node* head = NULL;
    for (int i = 0; i < n; ++i) {
        int val = rand() % 100;
        appendNode(&head, val);
    }
    return head;
}

// Libère la mémoire d'une liste chaînée
void freeList(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Affiche le menu des tris disponibles
void printMenu() {
    printf("\n=========================================\n");
    printf("              MENU DES TRIAGES\n");
    printf("=========================================\n");
    printf("1. Selection Sort Iteratif\n");
    printf("2. Selection Sort Recursif\n");
    printf("3. Quicksort Iteratif\n");
    printf("4. Quicksort Recursif\n");
    printf("5. Mergesort Iteratif\n");
    printf("6. Mergesort Recursif\n");
    printf("7. Modifier la taille de la liste\n");
    printf("0. Quitter\n");
    printf("=========================================\n");
    printf("Votre choix : ");
}

int main() {
    int size, choice;
    srand((unsigned)time(NULL));

    printf("Entrez la taille de la liste : ");
    scanf("%d", &size);
    while (size <= 0) {
        printf("Taille invalide! Veuillez entrer une taille positive : ");
        scanf("%d", &size);
    }

    do {
        printMenu();
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 7) {
            printf("Nouvelle taille de la liste : ");
            scanf("%d", &size);
            while (size <= 0) {
                printf("Taille invalide! Veuillez entrer une taille positive : ");
                scanf("%d", &size);
            }
            continue;
        }

        // Génération et affichage de la liste
        Node* head = generateRandomList(size);
        printf("\nListe avant tri : ");
        print_list(head);

        // Temps d'exécution du tri
        clock_t start = clock();

        switch (choice) {
        case 1:
            selectionSortIterative(head);
            break;
        case 2:
            selectionSortRecursive(head);
            break;
        case 3:
            head = quicksort_iterative(head);
            break;
        case 4:
            head = quicksort_recursive(head);
            break;
        case 5:
            head = mergesort_iterative(head);
            break;
        case 6:
            head = mergesort_recursive(head);
            break;
        default:
            printf("Choix invalide!\n");
            free_list(head);
            continue;
        }

        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;


        // Affichage résultat
        printf("Liste apres tri : ");
        print_list(head);
        printf("Temps d'execution : %.3f millisecondes\n", duration);


        free_list(head);

    } while (1);

    printf("\nMerci d'avoir utilisé le programme. Au revoir !\n");
    return 0;
}
