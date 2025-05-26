#include "gol.h"

int main(int argc, char **argv)
{
    int N, M, T, K;
    char **mat;
    LIST *head = NULL;
    STACK *top = NULL;
    bnrTree *root = NULL;
    // TASK 1
    mat = citire_fisier(argv[1], &N, &M, &T, &K);
    if (T == 1)
    {
        scriere_matINITIALA(mat, N, argv[2]);
        for (int i = 0; i < K; i++)
        {
            reguli_GoL(mat, N, M);
            scriere_rezultat(mat, N, argv[2]);
        }
    }
    eliberare_memorie_matrice(&mat, N);
    // finTASK 1
    // TASK 2
    mat = citire_fisier(argv[1], &N, &M, &T, &K);
    if (T == 2)
    {
        for (int i = 0; i < K; i++)
        {
            aflare_coordonate(mat, N, M, &head);
            push(&top, head, i + 1);
            if (i == 0)
            {
                scriere_stack_initial(argv[2], top);
            }
            else
            {
                scriere_stack(argv[2], top);
            }
            eliberare_lista(&head);
        }

        deleteStack(&top);
    }
    eliberare_memorie_matrice(&mat, N);
    // finTASK 2
    // TASK 3
    mat = citire_fisier(argv[1], &N, &M, &T, &K);
    if (T == 3)
    {
        populare_root(&root, mat, N, M);
        reguli_noi_GoL(&root, mat, N, M, K);
        afisare_root(root, argv[2], mat, N, M);
        eliberare_bnrtree(&root);
    }
    eliberare_memorie_matrice(&mat, N);
    // finTASK 3
    //  TASK 4
    mat = citire_fisier(argv[1], &N, &M, &T, &K);
    if (T == 4)
    {
        FILE *file = fopen(argv[2], "w");
        if (file == NULL)
        {
            exit(1);
        }
        fclose(file);
        populare_root(&root, mat, N, M);
        if (root == NULL)
        {
            printf("NU SE POPULEAZA ROOT");
            exit(1);
        }
        reguli_noi_GoL(&root, mat, N, M, K);

        //prima varianta
        hamilton(root,root,N,M,mat,argv[2]);
        

       //a doua varianta
        // aplicare_hamilton_node(root,mat,N,M,argv[2]);
        // if(root!=NULL)
        // {
        //     hamiloton_recursiv(root->left,mat,N,M,argv[2]);
        //     hamiloton_recursiv(root->right,mat,N,M,argv[2]);
        // }
        

        eliberare_bnrtree(&root);
    }
    eliberare_memorie_matrice(&mat, N);
    // finTASK 4
    return 0;
}