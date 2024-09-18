#include "PRANGE_ISD.h"

int main(){
    srand(time(NULL));

    int n ;
    int k ;
    int poids;
    int i, j;
    int s[MAX_N];
    FILE*f = fopen("resultat.txt", "w");
    //int poids = 1;
    int H[MAX_N][MAX_N];

    do{
        printf("Entrer la valeur de n: ");
        scanf("%d", &n);
        printf("Entrer la valeur de k: ");
        scanf("%d", &k);
        printf("Entrer la valeur du poids: ");
        scanf("%d", &poids);
    }while((n <= 0 || n > MAX_N) && (k <= 0 || k > K) && (poids < 0 || poids > n - k));

    genere_matrice_aleatoire(H, n, k);

    for(i = 0; i < n; i++){
        s[i] = rand() % 2;
    }

    //Afficahge de la matrice de contrôle
    print_matrix(H, n - k, n);
    double cpu_time_used;

    clock_t start = clock();
    Prange_ISD(H, s, n, k, poids);
    clock_t end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Temps de calcul: %f\n", cpu_time_used);
    fprintf(f, "Temps de calcul: %lf\n", cpu_time_used);
    fclose(f);
    return 0;
}