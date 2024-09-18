#include "ChiffreMDPC.h"


Polynome *generer_polynome_aleatoire(int n){

	Polynome *p = malloc(n * sizeof(int));
	int i;
	for(i = 0; i < n; i++){
		p->coefs[i] = rand() % 2;
	}

	return p;

}
void afficher_Polynome(int n, Polynome *p){
	int i;
	p = generer_polynome_aleatoire(n);
	for(i = 0; i < n; i++){
		printf("%d ", p->coefs[i]);
	}

	printf("\n");

	free(p);
}
void rot(int n, Polynome *h, int H[][N]){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			H[i][j] = h->coefs[(i - j + n) % n];
		}
	}
}
Polynome *multiplier_vecteur_matrice(int n, Polynome *p){

	int H[N][N];
	rot(n,p, H);
	Polynome *resultat;
	int i,j;
	for(i = 0; i < n; i++){
		resultat->coefs[i] = 0;
		for(j = 0; j < n; j++){
			resultat->coefs[i] ^= p->coefs[j] * H[i][j];
		}
	}
	return resultat;
}
Polynome *key_generation(int n, Polynome *h0, Polynome *h1){
	Polynome *h;
	h0 = generer_polynome_aleatoire(n);
	h1 = generer_polynome_aleatoire(n);

	memcpy(h->coefs, h1->coefs, n*sizeof(int));

	return h;
}
Polynome *chiffrement(int n, Polynome *m, Polynome *h){
	Polynome *ciphertext;

	int i, j;
	Polynome *e0, *e1;
	e0 = generer_polynome_aleatoire(n);
	e1 = generer_polynome_aleatoire(n);

	Polynome *temp2 ;
	temp2 = multiplier_vecteur_matrice(n,h);
	m = e0;

	for(i = 0; i < n; i++){
		ciphertext->coefs[i] = m->coefs[i] + e1->coefs[i] ^ temp2->coefs[i];
	}

	return ciphertext;

}
void afficher_chiffrement(int n, Polynome *p){
	int i;
	printf("chiffrement : ");
	for(i = 0; i < n; i++){
		printf("%d ", p->coefs[i]);
	}
	printf("\n");
}

Polynome *bit_flipping(int n, Polynome *h0, Polynome *h1, Polynome *s, int seuil, int poids){
    int i, j;
    int H0[N][N], H1[N][N], H[N][N];
    Polynome *resultat;

    /*rot(n, h0, H0, 1);
    rot(n, h1, H1, 0);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            H[i][j] = H0[i][j];
            H[i][j + n] = H1[i][j];
        }
    }*/

    int *syndrome = malloc(n * sizeof(int));
    syndrome = recupere_syndrome_s(s,n);

    
    int u[N] = {1, 0, 1, 1, 0};
    int v[N] = {1, 1, 1, 1, 0};

    //init_vecteur(n,u);//Initialisation du vecteur u à 0
    //init_vecteur(n,v);//Initialisation du vecteur v à 0

    /*u = init_vecteur(n);
    v = init_vecteur(n);*/


    int *somme = malloc(n * sizeof(int));
    int *flipped_positions = malloc(n * sizeof(int));
    

   
    int k;
    //Tant que la norme de u et la norme de v sont différents de t
    while(poids_hamming(u) != poids && poids_hamming(v) != poids){
       
        //Initialisation du vecteur somme à 0
       
        somme = init_vecteur(n);
        
        flipped_positions = init_vecteur(n);

        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                somme[j] = (somme[j] + syndrome[i] * H[i][j]) % 2;
            }
        }

        for(i = 0; i < n; i++){
            if(somme[i] > seuil){
                flipped_positions[i] = (flipped_positions[i] + 1) % 2;
            }
        }

        for(i = 0; i < n; i++){
            u[i] = (u[i] + flipped_positions[i]) % 2;
            v[i] = (v[i] + flipped_positions[i + n]) % 2;
        }
    
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            syndrome[j] = syndrome[j] - H[i][j] & flipped_positions[j];
        }
    }
    for(i = 0; i < n; i++){
        resultat->u[i] = u[i];
        resultat->v[i] = v[i];
    }
    //Si s - H * (u,v)^T != 0 alors retourner NULL
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j ++){
            if(s[j] ^ H[i][j] & u[j] != 0 && s[j] ^ H[i][j] & u[j] != 0){
                return NULL;
            }
            else
                return resultat;
        }
    }
    return resultat;
    free(somme);
    free(flipped_positions);
    free(u);
    free(v);
}


void dechiffrement(Polynome *, Polynome *, Polynome *, Polynome *);