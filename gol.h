#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** alocare_matrice(int n, int m);
void eliberare_memorie(char ***mat,int n);
char** citire_fisier(const char *nume, int *n, int *m, int *t, int *k);
int nr_vecini(char **mat, int n, int m, int x, int y);
void reguli_GoL(char **mat, int n, int m);
void scriere_rezultat(char **mat, int n, const char *nume);
void scriere_matINITIALA(char **mat, int n, const char *nume);