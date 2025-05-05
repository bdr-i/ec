#ifndef LISTE_H
#define LISTE_H

typedef struct Node {
    int val;
    struct Node* next;
} Node;

// Fonctions de base
Node* create_node(int val);
void appendNode(Node** head, int val);
void print_list(Node* head);
void free_list(Node* head);
int list_length(Node* head);

// Génération aléatoire
void generate_random_list(Node** head, int n);

#endif
