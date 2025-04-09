//TASK 1
#include "gol.h"

char** alocare_matrice(int n, int m)
{
    int i;
    char **mat;
    mat=(char **)malloc(n*sizeof(char*));
    if(mat==NULL)
    {
        printf("Eroare la alocarea dinamica a matricei!\n");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        mat[i]=(char *)malloc((m+1)*sizeof(char));
        if(mat[i]==NULL)
        {
            printf("Eroare la alocarea dinamica a liniei %d din matrice!\n",i);
            exit(1);
        }
    }
    return mat;
}

void eliberare_memorie_matrice(char ***mat,int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        free((*mat)[i]);
    }
    free(*mat);
    *mat=NULL;
}

char** citire_fisier(const char *nume, int *n, int *m, int *t, int *k)
{
    FILE *fisier=fopen(nume,"rt");
    if(fisier==NULL)
    {
        printf("Eroare la deschiderea fisierului date.txt");
        exit(1);
    }
    fscanf(fisier , "%d" , t);
    fscanf(fisier,"%d %d" , n, m);
    fscanf(fisier,"%d", k);
    char **mat=alocare_matrice(*n,*m);
    for(int i=0;i<(*n);i++)
    {
        fscanf(fisier,"%100s", *(mat+i));
    }
    fclose(fisier);
    return mat;
}

int nr_vecini(char **mat, int n, int m, int x, int y)
{
    int mat_x=0,mat_y=0,cnt=0;
    for(int i=-1;i<=1;i++)
    {
        for(int j=-1;j<=1;j++)
        {
            if(i==0 && j==0)
                continue;
            mat_x=x+i;
            mat_y=y+j;
            if(mat_x>=0 && mat_x<n && mat_y>=0 && mat_y<m && mat[mat_x][mat_y]=='X')
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
    int i,j;
    char **temp=alocare_matrice(n,m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            vecini=nr_vecini(mat,n,m,i,j);
            if(mat[i][j]=='X')
            {
                if( vecini < 2 || vecini > 3 )
                {
                    temp[i][j]='+';
                }
                else
                {
                    temp[i][j]='X';
                }
            }
            else
            {
                if(vecini==3)
                {
                    temp[i][j]='X';
                }
                else
                {
                    temp[i][j]='+';
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            mat[i][j]=temp[i][j];
        }
    }
eliberare_memorie_matrice(&temp,n);
}

void scriere_rezultat(char **mat, int n, const char *nume)
{
    FILE *fisier=fopen(nume,"a");
    if(fisier==NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        fprintf(fisier,"%s\n",mat[i]);
    }
    fprintf(fisier,"\n");
    fclose(fisier);
}

void scriere_matINITIALA(char **mat, int n, const char *nume)
{
    FILE *fisier=fopen(nume,"w");
    if(fisier==NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        fprintf(fisier,"%s\n",mat[i]);
    }
    fprintf(fisier,"\n");
    fclose(fisier);
}

//TASK 2

void addAtBeginning_list(LIST** head, COORD v)
{
    LIST *newNode=(LIST*)malloc(sizeof(LIST));
    newNode->poz.l=v.l;
    newNode->poz.c=v.c;
    newNode->next=*head;
    *head=newNode;

}

void addAtEnd_list(LIST **head, COORD v)
{
    LIST *aux=*head;
    LIST *newNode=(LIST*)malloc(sizeof(LIST));
    newNode->poz.l=v.l;
    newNode->poz.c=v.c;
    if(*head == NULL)
    {
        addAtBeginning_list(head,v);
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
    LIST *aux=*head;
    LIST *temp;
    while (aux!=NULL)
    {
        temp=aux;
        aux=aux->next;
        free(temp);
    }
    *head=NULL;
}

void push(STACK** top, LIST *v, int k) 
{
    STACK* newNode = (STACK*)malloc(sizeof(STACK));
    newNode->elem = v;
    newNode->gen=k;
    newNode->next = *top;
    *top = newNode;
}

void deleteStack(STACK** top) 
{
    STACK* temp;
    while ((*top) != NULL) 
    { 
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void aflare_coordonate(char **mat, int n, int m, LIST **head)
{
    int vecini;
    int i,j;
    COORD v;
    char **temp=alocare_matrice(n,m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            vecini=nr_vecini(mat,n,m,i,j);
            if(mat[i][j]=='X')
            {
                if( vecini < 2 || vecini > 3 )
                {
                    temp[i][j]='+';
                }
                else
                {
                    temp[i][j]='X';
                }
            }
            else
            {
                if(vecini==3)
                {
                    temp[i][j]='X';
                }
                else
                {
                    temp[i][j]='+';
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(mat[i][j]!=temp[i][j])
            {
                v.l=i;
                v.c=j;
                addAtEnd_list(head,v);
            }
        }
    }
eliberare_memorie_matrice(&temp,n);
}

void scriere_stack(const char *nume,STACK **top)
{
    FILE *fisier=fopen(nume,"w");
    if(fisier==NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scrierea rezulatatului");
        exit(1);
    }
    STACK *p=*top;
    while(p!=NULL)
    {
        LIST *q=p->elem;
        fprintf(fisier,"%d ", p->gen);
        while (q!=NULL)
        {
            fprintf(fisier,"%d %d ",q->poz.l,q->poz.c);
            q=q->next;
        }
        fprintf(fisier,"\n");
        p=p->next;
        eliberare_lista(&q);
    }
    deleteStack(&p);
    fclose(fisier);
}
