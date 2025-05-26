#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct coordonate
{
    int l, c;
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

struct tree
{
    LIST *elem;
    struct tree *left;
    struct tree *right;
};
typedef struct tree bnrTree;

char **alocare_matrice(int n, int m);
void eliberare_memorie_matrice(char ***mat, int n);
char **citire_fisier(const char *nume, int *n, int *m, int *t, int *k);
int nr_vecini(char **mat, int n, int m, int x, int y);
void reguli_GoL(char **mat, int n, int m);
void scriere_rezultat(char **mat, int n, const char *nume);
void scriere_matINITIALA(char **mat, int n, const char *nume);
void addAtEnd_list(LIST **head, COORD v);
void eliberare_lista(LIST **head);
void aflare_coordonate(char **mat, int n, int m, LIST **head);
void push(STACK **top, LIST *v, int k);
void deleteStack(STACK **top);
void inversare_stack(STACK **top);
void scriere_stack_terminal(STACK *top);
void scriere_stack_initial(const char *nume, STACK *top);
void scriere_stack(const char *nume, STACK *top);
void reguli_GoL_left(char **mat, int n, int m, bnrTree **root);
void reguli_GoL_right(char **mat, int n, int m, bnrTree **root);
void reguli_GoL_right(char **mat, int n, int m, bnrTree **root);
void populare_root(bnrTree **root, char **mat, int n, int m);
void eliberare_bnrtree(bnrTree **root);
void modificare_matrice(char **mat, LIST *v);
void reguli_noi_GoL(bnrTree **root, char **mat, int n, int m, int k);
void afisare_bnr(bnrTree *root, FILE *fisier, char **mat, int n, int m);
void afisare_root(bnrTree *root, const char *nume, char **mat, int n, int m);
int **alocare_matrice_int(int n, int m);
void eliberare_matrice_int(int ***mat, int n);
int vecinatate(COORD x, COORD y);
LIST *celule_vii(char **mat, int n, int m);
int nr_celule_vii(LIST *lista);
void transformare_vector(LIST *lista, int nr, COORD **v);
void completare_adiacenta(int ***adj, int n, const COORD *v);
void matrice_adiacenta(char **mat, int n, int m, int ***adj, COORD **v, int *nr);
void DFS(int **adj, int *viz, int *drum, int *lungime, int nod, int nr, int *max, int *cale_max);
void update_matrice(char ***mat, bnrTree *root, bnrTree *nod);
void scriere_graf(const char *nume, int max, const COORD *v, const int *cel_mai_lung_drum);
void eliberare_dfs(int **a, int **b, int **c, COORD **d);
void aplicare_hamilton(bnrTree *root, bnrTree *nod, char **mat_initiala, int n, int m, const char *nume);
void hamilton(bnrTree *root, bnrTree *nod, int n, int m, char **mat, const char *nume);
void aplicare_hamilton_node(const bnrTree *node,char **mat,int n,int m,const char *nume);
void hamiloton_recursiv(bnrTree *node,char **mat_init,int n,int m,const char *nume);