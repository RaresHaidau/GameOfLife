#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct coordonate
{
    int l,c;
};
typedef struct coordonate COORD;

struct list
{
    COORD poz;
    struct list *next;
};
typedef struct list LIST;

struct stack
{
    LIST *elem;
    int gen;
    struct stack *next;
};
typedef struct stack STACK;

char** alocare_matrice(int n, int m);
void eliberare_memorie_matrice(char ***mat,int n);
char** citire_fisier(const char *nume, int *n, int *m, int *t, int *k);
int nr_vecini(char **mat, int n, int m, int x, int y);
void reguli_GoL(char **mat, int n, int m);
void scriere_rezultat(char **mat, int n, const char *nume);
void scriere_matINITIALA(char **mat, int n, const char *nume);
void addAtBeginning_list(LIST** head, COORD v);
void addAtEnd_list(LIST **head, COORD v);
void eliberare_lista(LIST **head);
void aflare_coordonate(char **mat, int n, int m, LIST **head);
void push(STACK** top, LIST *v, int k);
int isEmpty(STACK* top);
void deleteStack(STACK** top);
void scriere_stack(const char *nume,STACK *top);