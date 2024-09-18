#include "PRANGE_ISD.h"
#include <stdlib.h>
#include <string.h>


void echange_lignes(int M[][MAX_N], int i, int j, int n){
    int temp;
    for(int k = 0; k < n; k++){
        temp = M[i][k];
        M[i][k] = M[j][k];
        M[j][k] = temp;
    }
}

// Défintion de la matrice de permutation P(n,n)
void generate_random_permutation(int P[][MAX_N], int n){
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
//poids de hamming d'un vecteur
int poids_hamming(int n, int k, int vecteur[MAX_N], int U[MAX_N][MAX_N]){
    int i, j;
    int poids = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < k; j++){
            poids += vecteur[i] & U[j][i];
        }
    }
    return poids;
}
    

void matrice_transpose(int matrice[MAX_N][MAX_N], int matrice_transpose[MAX_N][MAX_N], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrice_transpose[i][j] = matrice[j][i];
        }
    }
   
}

//Fonction pour calculer le produit s*U^T
void 
//Fonction pour génèrer une matrice identité
void genere_matrice_identite(int I[][MAX_N], int n, int k){
    int i, j;
    for(i = 0; i < n-k; i++){
        for(j = 0; j < n-k; j++){
            I[i][j] = (i == j) ? 1 : 0;
        }
    }
}

//Fonction pour imprimer une matrice
void print_matrix(int M[][MAX_N], int rows, int cols) {
    //matrix = (int**)malloc(rows*sizeof(int*));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    //free(matrix);
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
//Fonction Calcul de s*U^T
void s_U_transpose(int s[MAX_N], int U[MAX_N][MAX_N], int s_transpose[MAX_N], int n, int k){
    int i,j;
    for(i = 0; i < n; i++){
        s_transpose[i] = 0;
        for(j = 0; j < n - k; j++){
            s_transpose[i] ^= s[j] & U[j][i];
        }
    }
}

// Inverse d'une matrice carrée
void matrice_inverse(int matrice[MAX_N][MAX_N], int matrice_inverse[MAX_N][MAX_N], int n){
    int i, j, k;
    int matrice_identite[MAX_N][MAX_N];
    genere_matrice_identite(matrice_identite, n, n);
    int matrice_temp[MAX_N][MAX_N];
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrice_temp[i][j] = matrice[i][j];
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matrice_inverse[i][j] = matrice_identite[i][j];
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i != j){
                if(matrice_temp[i][i] == 0){
                    for(k = i + 1; k < n; k++){
                        if(matrice_temp[k][i] != 0){
                            echange_lignes(matrice_temp, i, k, n);
                            echange_lignes(matrice_inverse, i, k, n);
                            break;
                        }
                    }
                }
                int temp = matrice_temp[j][i] / matrice_temp[i][i];
                for(k = 0; k < n; k++){
                    matrice_temp[j][k] ^= matrice_temp[i][k] & temp;
                    matrice_inverse[j][k] ^= matrice_inverse[i][k] & temp;
                }
            }
        }
    }
    for(i = 0; i < n; i++){
        int temp = matrice_temp[i][i];
        for(j = 0; j < n; j++){
            matrice_temp[i][j] ^= matrice_temp[i][j] & temp;
            matrice_inverse[i][j] ^= matrice_inverse[i][j] & temp;
        }
    }
}

//Fonction principale pour implémenter PRANGE_ISD

void Prange_ISD(int H[][MAX_N], int s[MAX_N], int n, int k, int poids){
    int i,j, l;
    int lignes = n - k;
    int cols = n;
    //int permut_H[][MAX_N];
    int P[MAX_N][MAX_N];
    int P_inverse[MAX_N][MAX_N];

    int s_transpose[MAX_N];
    int e[MAX_N];
    int U[MAX_N][MAX_N];

    generer_matrice_inversible(U,n,k);
    do{
        generate_random_permutation(P,n);

        //Calcul H*P et H(n-k,n) et P(n,n)
        int H_P[MAX_N][MAX_N];
        for(i = 0; i < n - k; i++){
            for(j = 0; j < n; j++){
                H_P[i][j] = 0;
                for(l = 0; l < n; l++){
                    H_P[i][j] ^= H[i][l] & P[l][j];
                }
            }
        }
        //Quand il eixste, trouver U(n-k,n-k) tel que U*H*P = S=(I|H_tilde) avec H_tilde(n-k,k) et I(n-k,n-k)
        //int H_tilde[MAX_N][MAX_N];
        

        
        //calcule s*U^T
        int s_transpose[MAX_N];
        s_U_transpose(s,U,s_transpose,n,k);

    }while(poids_hamming(n,k,s,U) <= poids);
    //afficher s*U^T*P^(-1)
    //Calculer e = s*U^T*P^(-1), avec P^(-1) la matrice inverse de P
    matrice_inverse(P,P_inverse,n);
    for(i = 0; i < n; i++){
        e[i] = 0;
        for(j = 0; j < n; j++){
            e[i] ^= s_transpose[j] & P_inverse[j][i];
        }
    }

    //Afficher e
    printf("e = [");
    for(i = 0; i < n; i++){
        printf("%d",e[i]);
        if(i < n - 1){
            printf(", ");
        }
    }
    printf("]\n");
}

void genere_matrice_aleatoire(int M[][MAX_N], int n, int k){
    int i,j;
    for(i = 0; i < n-k; i++){
        for(j = 0; j < n; j++){
            M[i][j] = rand() % 2;
        }
    }
}
