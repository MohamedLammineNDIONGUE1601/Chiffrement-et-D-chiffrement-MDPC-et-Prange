#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 4813
#define T  26
#define t 78


void genererPoly(int n, int *p){
    int i;
    p[0] = 0;
    for(i = 1; i < n; i++){
        p[i] = rand() % 2;
    }
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

void rot(int n , int *h, int **H){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            H[i][j] = h[(i - j + n) % n];
        }
    }
}


void bitflip(int n, int *h0, int *h1, int *s, int seuil, int poids){
    int **H0 = (int **)malloc(n * sizeof(int *));
    int **H1 = (int **)malloc(n * sizeof(int *));
    int **H = (int **)malloc(n * sizeof(int *));
    int *u = (int *)malloc(n * sizeof(int));
    int *v = (int *)malloc(n * sizeof(int));
    int e0[N], e1[N];
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

    for(i = 0; i < n; i++){
        e0[i] = (u[i] + flipped_positions[i]) % 2;
        e1[i] = (v[i] + flipped_positions[i]) % 2;
    }
    printf("e0 = ");
    for(i = 0; i < n; i++){
        printf("%d", e0[i]);
    }
    printf("\n");
    printf("e1 = ");
    for(i = 0; i < n; i++){
        printf("%d", e1[i]);
    }
    printf("\n");
    free(syndrome);
    free(som);
    free(flipped_positions);
    free(u);
    free(v);
    free(flipped_positions);
    for(i = 0; i < n; i++){
        free(H0[i]);
        free(H1[i]);
        free(H[i]);
    }  
    free(H0);
    free(H1);
    free(H);
}

int main(){
    int *h0;
    int *h1;
    int *s;

    genererPoly(N, h0);
    genererPoly(N, h1);
    genererPoly(N, s);
    
    bitflip(N,h0,h1,s,T,t);

}