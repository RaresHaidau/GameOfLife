#include "gol.h"

int main(int argc, char **argv)
{
    int N, M, T, K;
    char **mat;
    LIST *head = NULL;
    STACK *top = NULL;
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
        eliberare_memorie_matrice(&mat, N);
        // finTASK 1
        // TASK 2
        mat = citire_fisier(argv[1], &N, &M, &T, &K);
    }
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
    return 0;
}