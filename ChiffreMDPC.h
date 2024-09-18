#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define N 4813
#define w 39
#define T 26
#define erreur 78

typedef struct {
	int coefs[N];
	int u[N];
	int v[N];
}Polynome;

Polynome *generer_polynome_aleatoire(int );
void afficher_Polynome(int , Polynome *);
void rot(int , Polynome *, int H[][N]);
Polynome *multiplier_vecteur_matrice(int , Polynome *);
Polynome *key_generation(int n, Polynome *, Polynome *);
Polynome *chiffrement(int n, Polynome *, Polynome *);
Polynome *bit_flipping(int , Polynome *, Polynome *, Polynome *, int , int);
void dechiffrement(Polynome *, Polynome *, Polynome *, Polynome *);

void afficher_chiffrement(int , Polynome *);
void afficher_dechiffrement(Polynome *);