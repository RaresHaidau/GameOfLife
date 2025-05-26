// TASK 1
#include "gol.h"

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

char **citire_fisier(const char *nume, int *n, int *m, int *t, int *k)
{
    FILE *fisier = fopen(nume, "rt");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului date.txt");
        exit(1);
    }
    fscanf(fisier, "%d", t);
    fscanf(fisier, "%d %d", n, m);
    fscanf(fisier, "%d", k);
    char **mat = alocare_matrice(*n, *m);
    for (int i = 0; i < (*n); i++)
    {
        fscanf(fisier, "%100s", *(mat + i));
    }
    fclose(fisier);
    return mat;
}

int nr_vecini(char **mat, int n, int m, int x, int y)
{
    int mat_x = 0, mat_y = 0, cnt = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            mat_x = x + i;
            mat_y = y + j;
            if (mat_x >= 0 && mat_x < n && mat_y >= 0 && mat_y < m && mat[mat_x][mat_y] == 'X')
            {
                cnt++;
            }
        }
    }
    return cnt;
}

void reguli_GoL(char **mat, int n, int m)
{
    int vecini;
    int i, j;
    char **temp = alocare_matrice(n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            vecini = nr_vecini(mat, n, m, i, j);
            if (mat[i][j] == 'X')
            {
                if (vecini < 2 || vecini > 3)
                {
                    temp[i][j] = '+';
                }
                else
                {
                    temp[i][j] = 'X';
                }
            }
            else
            {
                if (vecini == 3)
                {
                    temp[i][j] = 'X';
                }
                else
                {
                    temp[i][j] = '+';
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            mat[i][j] = temp[i][j];
        }
    }
    eliberare_memorie_matrice(&temp, n);
}

void scriere_rezultat(char **mat, int n, const char *nume)
{
    FILE *fisier = fopen(nume, "a");
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

// TASK 2

void addAtEnd_list(LIST **head, COORD v)
{
    LIST *aux = *head;
    LIST *newNode = (LIST *)malloc(sizeof(LIST));
    if (newNode == NULL)
    {
        printf("Eroare la alocarea dinamica pentru lista");
        return;
    }
    newNode->poz.l = v.l;
    newNode->poz.c = v.c;
    newNode->next = NULL;
    if (*head == NULL)
    {
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

void push(STACK **top, LIST *v, int k)
{
    STACK *newNode = (STACK *)malloc(sizeof(STACK));
    newNode->elem = v;
    newNode->gen = k;
    newNode->next = *top;
    *top = newNode;
}

void deleteStack(STACK **top)
{

    while ((*top) != NULL)
    {
        STACK *temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void aflare_coordonate(char **mat, int n, int m, LIST **head)
{
    int vecini;
    int i, j;
    COORD v;
    char **temp = alocare_matrice(n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            vecini = nr_vecini(mat, n, m, i, j);
            if (mat[i][j] == 'X')
            {
                if (vecini < 2 || vecini > 3)
                {
                    temp[i][j] = '+';
                }
                else
                {
                    temp[i][j] = 'X';
                }
            }
            else
            {
                if (vecini == 3)
                {
                    temp[i][j] = 'X';
                }
                else
                {
                    temp[i][j] = '+';
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (mat[i][j] != temp[i][j])
            {
                v.l = i;
                v.c = j;
                addAtEnd_list(head, v);
                mat[i][j] = temp[i][j];
            }
        }
    }
    eliberare_memorie_matrice(&temp, n);
}

// void inversare_stack(STACK **top)
// {
//     STACK *p,*aux;
//     if(top==NULL)
//     {
//         return;
//     }
//     p=(*top)->next;
//     (*top)->next=NULL;
//     while((*top))
//     {
//         aux=p;
//         p=p->next;
//         aux->next=p;
//
//     }
//      (*top)=aux;
// }

void scriere_stack_initial(const char *nume, STACK *top)
{

    FILE *fisier = fopen(nume, "w");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    if (top != NULL)
    {
        fprintf(fisier, "%d", top->gen);
        LIST *q = top->elem;
        while (q != NULL)
        {
            fprintf(fisier, " %d %d", q->poz.l, q->poz.c);
            q = q->next;
        }
        fprintf(fisier, "\n");
    }
    fclose(fisier);
}

void scriere_stack(const char *nume, STACK *top)
{

    FILE *fisier = fopen(nume, "a");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    if (top != NULL)
    {
        fprintf(fisier, "%d", top->gen);
        LIST *q = top->elem;
        while (q != NULL)
        {
            fprintf(fisier, " %d %d", q->poz.l, q->poz.c);
            q = q->next;
        }
        fprintf(fisier, "\n");
    }
    fclose(fisier);
}

// TASK3

void reguli_GoL_left(char **mat, int n, int m, bnrTree **root)
{
    int vecini;
    int i, j;
    char **temp = alocare_matrice(n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            vecini = nr_vecini(mat, n, m, i, j);
            if (vecini == 2 && mat[i][j] == '+')
            {
                temp[i][j] = 'X';
            }
            else
            {
                temp[i][j] = mat[i][j];
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (mat[i][j] != temp[i][j])
            {
                COORD cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
            // mat[i][j] = temp[i][j];
        }
    }
    eliberare_memorie_matrice(&temp, n);
}

void reguli_GoL_right(char **mat, int n, int m, bnrTree **root)
{
    int vecini;
    int i, j;
    char **temp = alocare_matrice(n, m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            vecini = nr_vecini(mat, n, m, i, j);
            if (mat[i][j] == 'X')
            {
                if (vecini < 2 || vecini > 3)
                {
                    temp[i][j] = '+';
                }
                else
                {
                    temp[i][j] = 'X';
                }
            }
            else
            {
                if (vecini == 3)
                {
                    temp[i][j] = 'X';
                }
                else
                {
                    temp[i][j] = '+';
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (mat[i][j] != temp[i][j])
            {
                COORD cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
            // mat[i][j] = temp[i][j];
        }
    }
    eliberare_memorie_matrice(&temp, n);
}

void populare_root(bnrTree **root, char **mat, int n, int m)
{
    *root = (bnrTree *)malloc(sizeof(bnrTree));
    (*root)->elem = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'X')
            {
                COORD cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
        }
    }
}

void eliberare_bnrtree(bnrTree **root)
{
    if (*root == NULL)
    {
        return;
    }
    eliberare_bnrtree(&(*root)->left);
    eliberare_bnrtree(&(*root)->right);
    eliberare_lista(&(*root)->elem);
    free(*root);
    *root = NULL;
}

void modificare_matrice(char **mat, LIST *v)
{
    while (v != NULL)
    {
        if (mat[v->poz.l][v->poz.c] == 'X')
        {
            mat[v->poz.l][v->poz.c] = '+';
        }
        else
        {
            mat[v->poz.l][v->poz.c] = 'X';
        }
        v = v->next;
    }
}

void reguli_noi_GoL(bnrTree **root, char **mat, int n, int m, int k)
{
    if (k == 0)
    {
        return;
    }
    char **mat_left = alocare_matrice(n, m);
    char **mat_right = alocare_matrice(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat_left[i][j] = mat[i][j];
            mat_right[i][j] = mat[i][j];
        }
    }
    (*root)->left = (bnrTree *)malloc(sizeof(bnrTree));
    (*root)->right = (bnrTree *)malloc(sizeof(bnrTree));

    (*root)->left->elem = NULL;
    (*root)->left->left = NULL;
    (*root)->left->right = NULL;

    (*root)->right->elem = NULL;
    (*root)->right->left = NULL;
    (*root)->right->right = NULL;

    reguli_GoL_left(mat_left, n, m, &(*root)->left);
    modificare_matrice(mat_left, (*root)->left->elem);

    reguli_GoL_right(mat_right, n, m, &(*root)->right);
    modificare_matrice(mat_right, (*root)->right->elem);

    reguli_noi_GoL(&(*root)->left, mat_left, n, m, k - 1);
    reguli_noi_GoL(&(*root)->right, mat_right, n, m, k - 1);

    eliberare_memorie_matrice(&mat_left, n);
    eliberare_memorie_matrice(&mat_right, n);
}

void afisare_bnr(bnrTree *root, FILE *fisier, char **mat, int n, int m)
{
    if (root == NULL)
    {
        return;
    }
    // FILE *fisier = fopen(nume, "a");
    // if (fisier == NULL)
    // {
    //     printf("Eroare la deschiderea fisierului pentru scrierea rezultatului");
    //     exit(1);
    // }
    char **temp = alocare_matrice(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp[i][j] = mat[i][j];
        }
    }
    LIST *v = root->elem;
    while (v != NULL)
    {

        if (temp[v->poz.l][v->poz.c] == 'X')
        {
            temp[v->poz.l][v->poz.c] = '+';
        }
        else if (temp[v->poz.l][v->poz.c] == '+')
        {
            temp[v->poz.l][v->poz.c] = 'X';
        }
        v = v->next;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(fisier, "%s\n", temp[i]);
    }
    fprintf(fisier, "\n");
    afisare_bnr(root->left, fisier, temp, n, m);
    afisare_bnr(root->right, fisier, temp, n, m);
    eliberare_memorie_matrice(&temp, n);
    // fclose(fisier);
}

void afisare_root(bnrTree *root, const char *nume, char **mat, int n, int m)
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
    if (root != NULL)
    {
        afisare_bnr(root->left, fisier, mat, n, m);
        afisare_bnr(root->right, fisier, mat, n, m);
    }
    fclose(fisier);
}

// TASK 4
int **alocare_matrice_int(int n, int m)
{
    int i;
    int **mat;
    mat = (int **)malloc(n * sizeof(int *));
    if (mat == NULL)
    {
        printf("Eroare la alocarea dinamica a matricei!\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        mat[i] = (int *)malloc((m + 1) * sizeof(int));
        if (mat[i] == NULL)
        {
            printf("Eroare la alocarea dinamica a liniei %d din matrice!\n", i);
            exit(1);
        }
    }
    return mat;
}

void eliberare_matrice_int(int ***mat, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free((*mat)[i]);
    }
    free(*mat);
    *mat = NULL;
}

int vecinatate(COORD x, COORD y)
{
    if (x.l == y.l && x.c == y.c)
    {
        return 0;
    }
    else if ((x.l - y.l >= -1 && x.l - y.l <= 1) && (x.c - y.c >= -1 && x.c - y.c <= 1))
    {
        return 1;
    }
    return 0;
}

LIST *celule_vii(char **mat, int n, int m)
{
    LIST *celule = NULL;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'X')
            {
                COORD c;
                c.l = i;
                c.c = j;
                addAtEnd_list(&celule, c);
            }
        }
    }
    return celule;
}

int nr_celule_vii(LIST *lista)
{
    int cnt = 0;
    LIST *temp = lista;
    while (temp != NULL)
    {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

void transformare_vector(LIST *lista, int nr, COORD **v)
{
    LIST *temp = lista;
    for (int i = 0; i < nr; i++)
    {
        *(v[i]) = temp->poz;
        temp = temp->next;
    }
}

void completare_adiacenta(int ***adj, int n, const COORD *v)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (vecinatate(v[i], v[j]) == 1)
            {
                (*adj)[i][j] = 1;
                (*adj)[j][i] = 1;
            }
        }
    }
}

void matrice_adiacenta(char **mat, int n, int m, int ***adj, COORD **v, int *nr)
{
    LIST *celule = celule_vii(mat, n, m);
    (*nr) = nr_celule_vii(celule);
    *v = malloc((*nr) * sizeof(COORD));
    if ((*v) == NULL)
    {
        printf("Eroare la alocarea vectorului!");
        exit(1);
    }
    transformare_vector(celule, *nr, v);
    *(adj) = alocare_matrice_int(*nr, *nr);
    completare_adiacenta(adj, *nr, *v);
    eliberare_lista(&celule);
}

void DFS(int **adj, int *viz, int *drum, int *lungime, int nod, int nr, int *max, int *cale_max)
{
    viz[nod] = 1;
    drum[*lungime] = nod;
    (*lungime)++;
    if ((*lungime) > (*max))
    {
        *max = *lungime;
        for (int i = 0; i < (*lungime); i++)
        {
            cale_max[i] = drum[i];
        }
    }
    for (int i = 0; i < nr; i++)
    {
        if (adj[nod][i] != 0 && viz[i] == 0)
        {
            DFS(adj, viz, drum, lungime, i, nr, max, cale_max);
        }
    }
    (*lungime)--;
    viz[nod] = 0;
}

void update_matrice(char ***mat, bnrTree *root, bnrTree *nod)
{
    if (root == NULL || nod == NULL)
    {
        return;
    }
    if (root == nod)
    {
        modificare_matrice(*mat, root->elem);
        return;
    }
    update_matrice(mat, root->left, nod);
    update_matrice(mat, root->right, nod);
    modificare_matrice(*mat, root->elem);
}

void scriere_graf(const char *nume, int max, const COORD *v, const int *cel_mai_lung_drum)
{
    FILE *file = fopen(nume, "a");
    if (file == NULL)
    {
        printf("Eroare la deschiderea fisierului!");
        exit(1);
    }
    if (max == -1)
    {
        fprintf(file, "-1\n");
    }
    else
    {
        fprintf(file, "%d\n", max);
        for (int i = 0; i < max; i++)
        {
            fprintf(file, "(%d,%d) ", v[cel_mai_lung_drum[i]].l, v[cel_mai_lung_drum[i]].c);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void eliberare_dfs(int **a, int **b, int **c, COORD **d)
{
    free(*a);
    free(*b);
    free(*c);
    free(*d);
}

void aplicare_hamilton(bnrTree *root, bnrTree *nod, char **mat_initiala, int n, int m, const char *nume)
{

    char **mat_actuala = alocare_matrice(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat_actuala[i][j] = mat_initiala[i][j];
        }
    }
    update_matrice(&mat_actuala, root, nod);
    int **adj, nr; // marime matrice adjuncta
    COORD *v;
    matrice_adiacenta(mat_actuala, n, m, &adj, &v, &nr);
    int *viz = malloc(nr * sizeof(int));
    int *drum = malloc(nr * sizeof(int));
    int *cel_mai_lung_drum = malloc(nr * sizeof(int));
    int max = -1;
    // for (int i = 0; i < nr; i++)
    // {
    //     viz[i] = 0;
    // }
    for (int i = 0; i < nr; i++)
    {
        for(int k=0;k<nr;k++)
        {
            viz[i]=0;
        }
        int lungime = 0;
        DFS(adj, viz, drum, &lungime, i, nr, &max, cel_mai_lung_drum);
    }
    scriere_graf(nume, max, v, cel_mai_lung_drum);
    eliberare_matrice_int(&adj, nr);
    eliberare_memorie_matrice(&mat_actuala,n);
    eliberare_dfs(&viz, &drum, &cel_mai_lung_drum, &v);
}

void hamilton(bnrTree *root, bnrTree *nod, int n, int m, char **mat, const char *nume)
{
    if (nod == NULL)
    {
        return;
    }
    char **mat_left=alocare_matrice(n,m);
    char **mat_right=alocare_matrice(n,m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            mat_left[i][j]=mat[i][j];
            mat_right[i][j]=mat[i][j];
        }
    }
    
    aplicare_hamilton(root, nod, mat, n, m, nume);
    hamilton(root, nod->left, n, m, mat_left, nume);
    hamilton(root, nod->right, n, m, mat_right, nume);
    eliberare_memorie_matrice(&mat_left,n);
    eliberare_memorie_matrice(&mat_right,n);
}
//incercare

void aplicare_hamilton_node(const bnrTree *node,char **mat,int n,int m,const char *nume)
{
    if(node==NULL)
    {
        return;
    }
    int **adj,nr;
    COORD *v;
    matrice_adiacenta(mat,n,m,&adj,&v,&nr);
    int *viz = malloc(nr * sizeof(int));
    int *drum = malloc(nr * sizeof(int));
    int *cel_mai_lung_drum = malloc(nr * sizeof(int));
    int max = -1;
    for (int i = 0; i < nr; i++)
    {
        for(int k=0;k<nr;k++)
        {
            viz[i]=0;
        }
        int lungime = 0;
        DFS(adj, viz, drum, &lungime, i, nr, &max, cel_mai_lung_drum);
    }
    scriere_graf(nume, max, v, cel_mai_lung_drum);
    eliberare_matrice_int(&adj, nr);
    eliberare_dfs(&viz, &drum, &cel_mai_lung_drum, &v);
}

void hamiloton_recursiv(bnrTree *node,char **mat_init,int n,int m,const char *nume)
{
    char **mat_actuala=alocare_matrice(n,m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            mat_actuala[i][j]=mat_init[i][j];
        }
    }
    modificare_matrice(mat_actuala,node->elem);
    aplicare_hamilton_node(node,mat_actuala,n,m,nume);
    hamiloton_recursiv(node->left,mat_actuala,n,m,nume);
    hamiloton_recursiv(node->right,mat_actuala,n,m,nume);
    eliberare_memorie_matrice(&mat_actuala,n);
}
