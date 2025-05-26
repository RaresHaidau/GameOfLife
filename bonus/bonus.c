#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char **alocare_matrice(int n, int m)
{
    int i;
    char **mat;
    mat = (char **)malloc(n * sizeof(char *));
    if (mat == NULL)
    {
        printf("Eroare la alocarea dinamica a matricei!\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        mat[i] = (char *)malloc((m + 1) * sizeof(char));
        if (mat[i] == NULL)
        {
            printf("Eroare la alocarea dinamica a liniei %d din matrice!\n", i);
            exit(1);
        }
    }
    return mat;
}

void eliberare_memorie_matrice(char ***mat, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free((*mat)[i]);
    }
    free(*mat);
    *mat = NULL;
}

void addAtEnd(LIST **head, int l, int c)
{
    LIST *aux = *head;
    LIST *newNode = (LIST *)malloc(sizeof(LIST));
    newNode->poz.l = l;
    newNode->poz.c = c;
    if (*head == NULL)
    {
        newNode->poz.l = l;
        newNode->poz.c = c;
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = newNode;
        newNode->next = NULL;
    }
}

void push(STACK **top, LIST *v, int k)
{
    STACK *newNode = (STACK *)malloc(sizeof(STACK));
    newNode->elem = v;
    newNode->gen = k;
    newNode->next = *top;
    *top = newNode;
}

char **citire_fisier(const char *nume, int *n, int *m, int *k, STACK **top)
{
    FILE *fisier = fopen(nume, "rt");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului date.txt");
        exit(1);
    }
    fscanf(fisier, "%d %d", n, m);
    fscanf(fisier, "%d", k);
    char **mat = alocare_matrice(*n, *m);
    for (int i = 0; i < (*n); i++)
    {
        fscanf(fisier, "%100s", *(mat + i));
    }
    int gen;
    while (fscanf(fisier, "%d", &gen) == 1)
    {
        LIST *head = NULL;
        int l, c;
        while (fscanf(fisier, " %d %d", &l, &c) == 2)
        {
            addAtEnd(&head,l,c);
            int urm=fgetc(fisier);
            if(urm=='\n' || urm== -1)
            {
                break;
            }
            else
            {
                ungetc(urm,fisier);
            }
        }
        push(top, head, gen);
    }
    fclose(fisier);
    return mat;
}

void eliberare_lista(LIST **head)
{
    LIST *aux = *head;
    // LIST *temp;
    while (aux != NULL)
    {
        LIST *temp = aux;
        aux = aux->next;
        free(temp);
    }
    *head = NULL;
}

void deleteStack(STACK **top)
{

    while ((*top) != NULL)
    {
        LIST *head=(*top)->elem;
        eliberare_lista(&head);
        STACK *temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void matrice_initiala(char ***mat, STACK *top, int n, int m)
{
    while (top != NULL)
    {
        LIST *head = top->elem;
        if (head == NULL)
        {
            return;
        }
        while (head != NULL)
        {
            int l = head->poz.l;
            int c = head->poz.c;
            if (l >= 0 && l < n && c >= 0 && c < m)
            {
                if ((*mat)[l][c] == 'X')
                {
                    (*mat)[l][c] = '+';
                }
                else
                {
                    (*mat)[l][c] = 'X';
                }
            }
            head = head->next;
        }
        // eliberare_lista(&head);
        top = top->next;
    }
}

void scriere_matINITIALA(char **mat, int n, const char *nume)
{
    FILE *fisier = fopen(nume, "w");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(fisier, "%s\n", mat[i]);
    }
    fprintf(fisier, "\n");
    fclose(fisier);
}

void printStack(STACK *top)
{
    while (top != NULL)
    {
        LIST *head = top->elem;
        printf("%d!!! ", top->gen);
        while (head != NULL)
        {
            printf("%d %d ", head->poz.l, head->poz.c);
            head = head->next;
            
        }
        printf("\n");
        top = top->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int n, m, k;
    LIST *head = NULL;
    STACK *top = NULL;
    char **mat = citire_fisier(argv[1], &n, &m, &k, &top);
    matrice_initiala(&mat, top, n, m);
    scriere_matINITIALA(mat, n, argv[2]);
    printStack(top);
    deleteStack(&top);
    eliberare_memorie_matrice(&mat, n);
    return 0;
}