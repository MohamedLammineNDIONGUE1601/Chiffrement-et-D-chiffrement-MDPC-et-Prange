#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define N 4813

void genererPoly(int n, int *p){
    int i;
    p[0] = 0;
    for(i = 1; i < n; i++){
        p[i] = rand() % 2;
    }
}

void rot(int n , int *h, int **H){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            H[i][j] = h[(i - j + n) % n];
        }
    }
}

void multiplier_vecteur_matrice(int n, int *resultat){
    int *p = (int *)malloc((n + 1) * sizeof(int));
    int **H = (int **)malloc(n * sizeof(int *));
    int i, j;
    for(i = 0; i < n; i++){
        H[i] = (int *)malloc(n * sizeof(int));
    }

    genererPoly(n, p);
    rot(n, p, H);

    for(i = 0; i < n; i++){
        resultat[i] = 0;
        for(j = 0; j < n; j++){
            resultat[i] += p[j] * H[j][i];
        }
    }

    free(p);
    for(i = 0; i < n; i++){
        free(H[i]);
    }
    free(H);
}

int Poids(int n, int *v){
    int i;
    int som = 0;
    for(i = 0; i < n; i++){
        if(v[i] == 1){
            som++;
        }
    }
    return som;
}

void calcul(int n, int *u, int *s, int **H, int *R){
    int i, j;
    for(i = 0; i < n; i++){
        R[i] = 0;
        for(j = 0; j < n; j++){
            R[i] += s[i] - H[i][j] * u[j];
        }
    }
}

/*void bitflip(int n, int *h0, int *h1, int *s, int seuil, int poids, int *u, int *v){
    int **H0 = (int **)malloc(n * sizeof(int *));
    int **H1 = (int **)malloc(n * sizeof(int *));
    int **H = (int **)malloc(n * sizeof(int *));
    int i, j;

    for(i = 0; i < n; i++){
        H0[i] = (int *)malloc(n * sizeof(int));
        H1[i] = (int *)malloc(n * sizeof(int));
        H[i] = (int *)malloc(n * sizeof(int));
    }

    rot(n, h0, H0);
    rot(n, h1, H1);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            H[i][j] = H0[i][j] + H1[i][j];
        }
    }

    int *syndrome = (int *)malloc(n * sizeof(int));
    for(i = 0; i < n; i++){
        syndrome[i] = s[i];
    }

    int *som = (int *)malloc(n * sizeof(int));
    int *flipped_positions = (int *)malloc(n * sizeof(int));

    while((Poids(n,u) != poids || Poids(n,v) != poids) && Poids(n,syndrome) != 0){
        for(i = 0; i < n; i++){
            som[i] = 0;
            for(j = 0; j < n; j++){
                som[j] = (som[j] + syndrome[i] * H[i][j]) % 2;
            }
        }

        for(i = 0; i < n; i++){
            if(som[i] > seuil){
                flipped_positions[i] = (flipped_positions[i] + 1) % 2;
            }
        }

        for(i = 0; i < n; i++){
            u[i] = (u[i] + flipped_positions[i]);
            v[i] = (v[i] + flipped_positions[i]);
        }

        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                syndrome[i] = (syndrome[i] + H[i][j] * flipped_positions[j]) % 2;
            }
        }
    }

    free(syndrome);
    free(som);
    free(flipped_positions);
    for(i = 0; i < n; i++){
        free(H0[i]);
        free(H1[i]);
        free(H[i]);
    }  
    free(H0);
    free(H1);
    free(H);
}*/

void KeyGen(int n, int **h_privee, int *h_pub){
    int *h0 = (int *)malloc(n * sizeof(int));
    int *h1 = (int *)malloc(n * sizeof(int));
    //memset(h0, 0, n * sizeof(int));
    genererPoly(n, h0);
    genererPoly(n, h1);
    
    int i, j;
    for(i = 0; i < n; i++){
        h0[i] = h0[n - 1 - i];
    }

    for(i = 0; i < n; i++){
        int *h0_inv =  1? 0 : 1;
        h_pub[i] = h1[i] * h0_inv[i];
    }

    h_privee[0] = h0;
    h_privee[1] = h1;
}

void chiffrement(int n, int *e0, int *e1, int *ciphertext){

    int poids = 78;
    int T = 26;
    int i;


    int *h0 = (int *)malloc(n * sizeof(int));
    int *h1 = (int *)malloc((n + 1) * sizeof(int));
    int *s = (int *)malloc((n + 1) * sizeof(int));
    int **h_privee = (int **)malloc(2 * sizeof(int *));
    int *h_pub = (int *)malloc(n * sizeof(int));

    KeyGen(n,h_privee,h_pub);

    for(i = 0; i < n; i++){
        h0[i] = h0[n - 1 - i];
    }

    //bitflip(n, h0, h1, s, T, poids, e0, e1);
    
    for(i = 0; i < n; i++){
        
        ciphertext[i] = e0[i] + e1[i] * h_pub[i];
    }

    free(h0);
    free(h1);
    free(s);
}

void decryption(int *ciphertext, int n, int t, int w, int *plaintext) {
    int *e0 = (int *)malloc(n * sizeof(int));
    int *e1 = (int *)malloc(n * sizeof(int));

    //bit_flipping(n, h0, h1, ciphertext, t, w);

    int *temp1 = (int *)malloc(n * sizeof(int));
    int *temp2 = (int *)malloc(n * sizeof(int));

    multiplier_vecteur_matrice(n, temp1);
    multiplier_vecteur_matrice(n, temp2);

    for (int i = 0; i < n; i++) {
        plaintext[i] = ciphertext[i] ^ temp1[i] ^ temp2[i];
    }

    free(e0);
    free(e1);
    free(temp1);
    free(temp2);
}


int main() {
    srand(time(NULL));
    clock_t start = clock();

    int T = 26;
    int W = 39;
    int *h_pub = (int *)malloc(N * sizeof(int));
    int **h_privee = (int **)malloc(2 * sizeof(int *));
    int *plaintext = (int *)malloc(N * sizeof(int));
    int *h0;
    int *h1;
    KeyGen(N, h_privee, h_pub);

    printf("La cle privee est : \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", h_privee[0][i]);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%d ", h_privee[1][i]);
    }
    printf("\n\n");

    printf("La cle publique est : \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", h_pub[i]);
    }
    printf("\n");

    /*int *h0 = (int *)malloc(N * sizeof(int));
    int *h1 = (int *)malloc(N * sizeof(int));
    int *e0 = (int *)malloc(N * sizeof(int));
    int *e1 = (int *)malloc(N * sizeof(int));
    int *ciphertext = (int *)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++){
        e0[i] = rand() % 2;
        e1[i] = rand() % 2;
    }
    chiffrement(N, e0, e1, ciphertext);

    printf("e0 : ");
    for (int i = 0; i < N; i++) {
        printf("%d ", e0[i]);
    }
    printf("\n");

    printf("e1 : ");
    for (int i = 0; i < N; i++) {
        printf("%d ", e1[i]);
    }
    printf("\n");

    printf("Le chiffré est : ");
    for (int i = 0; i < N; i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    decryption(ciphertext, N, T, W, plaintext);

    printf("Le texte déchiffré est : \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", plaintext[i]);
    }*/
    printf("\n\n\n");
    printf("\nLe temps de calcul pour le chiffrement est : %.2f secondes\n", ((double)clock() - start) / CLOCKS_PER_SEC);

    free(h_pub);
    free(h_privee[0]);
    free(h_privee[1]);
    free(h_privee);
    //free(e0);
    //free(e1);
    //free(ciphertext);

    return 0;
}