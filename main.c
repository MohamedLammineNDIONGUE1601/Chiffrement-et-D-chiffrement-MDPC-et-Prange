#include "ChiffreMDPC.h"

int main(){


	int n = 10;
	Polynome *p;
	Polynome *h0;
	Polynome *h1;
	Polynome *h = malloc(n * sizeof(int));
	Polynome*resultat = malloc(n * sizeof(int));
	int H[N][N];
	int i;
	
	h = key_generation(n, h0, h1);
	for(i = 0; i < n; i++){
		printf("%d ", h->coefs[i]);
	}
	printf("\n");
	Polynome *m;
	Polynome *resultat1 = malloc(n * sizeof(int)); 
	resultat1 = chiffrement(n, m, h);
	afficher_chiffrement(n,resultat1);

	//afficher_Polynome(n,p);
	//rot(n, h0, H);
	//rot(n, h1, H,0);
	//resultat = multiplier_vecteur_matrice(n, p,H);


	free(resultat1);
	free(resultat);
	free(h);



	

	return 0;
}