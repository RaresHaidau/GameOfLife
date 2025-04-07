#include "gol.h"

int main(int argc, char** argv)
{
    int N,M,T,K;
    char **mat;
    int i;
    mat=citire_fisier(argv[1], &N, &M, &T, &K);
    scriere_matINITIALA(mat,N,argv[2]);
    for(i=0;i<K;i++)
    {
        reguli_GoL(mat,N,M);
        scriere_rezultat(mat,N,argv[2]);
    }
    eliberare_memorie(&mat,N);
    return 0;
}