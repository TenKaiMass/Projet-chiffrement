#ifndef DECHIFFREMENT_C
#define DECHIFFREMENT_C

#include "dechiffrement.h"
#include "chiffrement.h"

const int S[16] = {5, 14, 15, 8, 12, 1, 2, 13, 11, 4, 6, 3, 0, 7, 9, 10};

char *dechiffrement(char *bin, char *K)
{
	char* permu;	//cette variable recupere l'inverse de la permutation
	int k = 240;	//indice pour prendre les bonnes clé
	int recul = 2;	// pour ce positionner avant de prendre les bonnes clé

	for (int j = 0; j < 24; j++)
	{
		bin[j] = (bin[j] == K[k]) ? '0' : '1'; //xor entre la cle et le message binaire
		k++;
	}

	for (int i = 1; i <= 10; i++) 				//pour les 10 premieres clé
	{
		permu = inverse_permutation(bin);		//permu prends la permutation inverse du binaire
		free(bin);								//bin va etre alloque dans inverse_substution(), donc pour le reutiliser il faut d'abord le free
		bin = inverse_substitution(permu);		//on donne a bin la permutation inverse du resultat de la permutation (une zone memoire alloquee)
		k -= (24*recul); 						//on se positionne pour chaque clé 
		
		for (int j = 0; j < 24; j++)
		{
			bin[j] = (bin[j] == K[k]) ? '0' : '1';
			k++;
		}
		free(permu);							//permu est alloque dans inverse_permutation();
	}

	return bin;
}

char *inverse_substitution(char *bin)
{
	char* sub = malloc(sizeof(char) * 24);
	char toast[4]; //cette variable va recuperer le mot binaire a convertir

	for (int j = 0; j <= 20; j += 4)
	{
		strncpy(toast, &bin[j], 4);			//on copie les bits de 4 en 4
		int indice = conv_pr_subst(toast);	//on transforme les char en int (dont la valeur est situee entre 0 et 16)
		strncpy(&sub[j], binary[S[indice]], 4);	//on copie alors le binaire du chiffre apres substitution dans la chaine de char qu'on va retourner
	}
	
	return sub;
}

char *inverse_permutation(char *bin)
{
	char *perm = malloc(sizeof(char) * 24);
	
	for (int i = 0; i < 24; i++)
	{
		perm[i] = bin[P[i]];		
	}
	
	return perm;
}

#endif