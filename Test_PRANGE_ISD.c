#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_POIDS 39

void generer_matrice_aleatoire_binaire(int matrice[MAX_N][MAX_N], int n, int k);
void generer_matrice_inversible(int U[][MAX_N], int n, int k);
void generer_vecteur_syndrome(int vecteur[MAX_N], int n, int k);
void PRANGE_ISD_BIS(int H[MAX_N][MAX_N], int U[MAX_N][MAX_N], int s[MAX_N], int n, int k);
int poids_hamming(int n, int k, int s[MAX_N], int U[MAX_N][MAX_N]);
void generer_matrice_permutation_P(int P[MAX_N][MAX_N], int n);
void s_U_transpose(int s[MAX_N], int U[MAX_N][MAX_N], int n, int k,  int resultat[MAX_N]);

int main(){
    int n = 10;
    int k = 5;
    int H[MAX_N][MAX_N];
    int U[MAX_N][MAX_N];
    int s[MAX_N];
    srand(time(NULL));
    generer_matrice_aleatoire_binaire(H,n,k);
    generer_matrice_inversible(U,n,k);
    generer_vecteur_syndrome(s,n,k);
    PRANGE_ISD_BIS(H,U,s,n,k);
    return 0;
}

void echange_lignes(int M[][MAX_N], int i, int j, int n){
    int temp;
    for(int k = 0; k < n; k++){
        temp = M[i][k];
        M[i][k] = M[j][k];
        M[j][k] = temp;
    }
}

//Générer une matrice aléatoire de taille n - k x k
void generer_matrice_aleatoire_binaire(int matrice[MAX_N][MAX_N], int n, int k){
    int i,j;
    for(i = 0; i < n - k; i++){
        for(j = 0; j < k; j++){
            matrice[i][j] = rand() % 2;
        }
    }
}
//Générer une matrice inversible U(n-k,n-k)
void generer_matrice_inversible(int U[][MAX_N], int n, int k){
    int i,j;
    for(i = 0; i < n - k; i++){
        for(j = 0; j < n - k; j++){
            U[i][j] = 0;
        }
    }
    for(i = 0; i < n - k; i++){
        U[i][i] = 1;
    }
}

//générer un vecteur syndrôme aléatoire binaire
void generer_vecteur_syndrome(int vecteur[MAX_N], int n, int k){
    int i;
    for(i = 0; i < n - k; i++){
        vecteur[i] = rand() % 2;
    }
}

int poids_hamming(int n, int k, int s[MAX_N], int U[MAX_N][MAX_N]){
    int i, j;
    int poids = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < k; j++){
            poids += s[i] & U[j][i];
        }
    }
    return poids;
}
void generer_matrice_permutation_P(int P[MAX_N][MAX_N], int n){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            P[i][j] = 0;
        }
    }
    for(i = 0; i < n; i++){
        P[i][i] = 1;
    }
    for(i = 0; i < n; i++){
        int j = rand() % n;
        echange_lignes(P,i,j,n);
    }
}
int poids_hamming_s(int vecteur[MAX_N], int n){
    int i;
    int poids = 0;
    for(i = 0; i < n; i++){
        poids += vecteur[i];
    }
    return poids;
}
void s_U_transpose(int s[MAX_N], int U[MAX_N][MAX_N], int n, int k, int resultat[MAX_N]){
    int i,j;
   
    for(i = 0; i < n - k; i++){
        resultat[i] = 0;
    }
    for(i = 0; i < n - k; i++){
        for(j = 0; j < n - k; j++){
            resultat[i] ^= s[j] & U[i][j];
        }
    }
}
void PRANGE_ISD_BIS(int H[MAX_N][MAX_N],int U[MAX_N][MAX_N], int s[MAX_N], int n, int k){
    int i,j;
    int P[MAX_N][MAX_N];
    int resultat[MAX_N];

    do{
        generer_matrice_permutation_P(P,n);
        int H_P[MAX_N][MAX_N];
        //Calcul H*P
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                H_P[i][j] = 0;
            }
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                for(int l = 0; l < n; l++){
                    H_P[i][j] ^= H[i][l] & P[l][j];
                }
            }
        }
        generer_matrice_inversible(U,n,k);
        generer_vecteur_syndrome(s,n,k);
        //Calcul s*U^T
        int s_transpose[MAX_N];
        for(i = 0; i < n; i++){
            s_transpose[i] = 0;
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                s_transpose[i] ^= s[j] & U[i][j];
            }
        }

    }while(poids_hamming(n,k,s,U) <= poids_hamming_s(s,n));

    //Afficher s*U^T*P^-1
    s_U_transpose(s, U, n, k, resultat);
    int s_U_transpose_P_inverse[MAX_N];
    for(i = 0; i < n; i++){
        s_U_transpose_P_inverse[i] = 0;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            s_U_transpose_P_inverse[i] ^= resultat[j] & P[j][i];
        }
    }
    for(i = 0; i < n; i++){
        printf("%d",s_U_transpose_P_inverse[i]);
    }
}
