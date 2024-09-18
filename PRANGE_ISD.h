#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef PRANGE_ISD_H_INCLUDED
#define PRANGE_ISD_H_INCLUDED

#define MAX_N 1000
#define K 500


void echange_lignes(int M[][MAX_N], int , int , int );
void application_Permutation(int M[][MAX_N], int Per[], int , int );
//void Multiplication_Matrice(int resultat[][MAX_N], int mat1[][MAX_N], int mat2[][MAX_N], int , int , int , int );
void generate_random_permutation(int P[][MAX_N], int );
void genere_matrice_identite(int I[][MAX_N], int , int );
int A_un_poids_faible(int vecteur[MAX_N], int , int );
void print_matrix(int M[][MAX_N], int , int );
void Prange_ISD(int H[][MAX_N], int s[MAX_N], int , int , int );
void genere_matrice_aleatoire(int M[][MAX_N], int , int );
//void generer_vecteur_aleatoire(int vecteur[MAX_N], int );
void matrice_inverse(int matrice[MAX_N][MAX_N], int matrice_inverse[MAX_N][MAX_N], int );

#endif // PRANGE_ISD_H_INCLUDED
