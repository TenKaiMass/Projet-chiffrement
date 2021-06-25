#ifndef CHIFFREMENT_C
#define CHIFFREMENT_C

#include "chiffrement.h"

//tableau permutation en bit
const char S_bin[64] = {"1100010101101011100100001010110100111110111110000100011100010010"};
const int P[24] = {0, 6, 12, 18, 1, 7, 13, 19, 2, 8, 14, 20, 3, 9, 15, 21, 4, 10, 16, 22, 5, 11, 17, 23};

//tab binaire de l'hexadecimal (binary[i] corresponds to digits[i])
const char binary[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

//tab hexadecimal
const char digits[16] = "0123456789abcdef";

void aff_with_space_bin(char *bin)
{
	for(int i = 0; i < 24; i++)
	{
		if (i % 4 == 0 && (!i == 0))
		{
			printf(" ");
		}
		printf("%c", bin[i]);
		i++;
	}
	printf("\n");
}

void print_bin_to_hexa(char bin[24])
{
	char hexVal[6];
	char temp[4];
	
	for(int i = 0; i < 24; i+=4)
	{
		strncpy(temp, &bin[i], 4);

		for(int j = 0; j < 16; j++)
		{
			if (!strncmp(temp, binary[j], 4))
			{
				hexVal[i/4] = digits[j];
			}
		}
	}
	printf("%s\n", hexVal);
}

char *hexa_to_bin(char hexa[6])
{
	char *bin = malloc(sizeof(char) * 24);
	int p = 0;

	for(int i = 0; i < 24; i+=4)
	{
		const char *v = strchr(digits, hexa[p++]);
		if (v)
		{
			strncpy(&bin[i], binary[v - digits], 4);
		}
	}

	return bin;
}

char *chiffrement(char etat[6], char *K)
{
	char *bin = hexa_to_bin(etat);
	char* sub;
	int k = 0;
	for (int i = 1; i <= 10; i++) //pour les 10 premiers clé
	{
		for (int j = 0; j < 24; j++)
		{
			bin[j] = (bin[j] == K[k])? '0': '1';
			k++;	
		}
		sub = substitution(bin);
		free(bin);
		bin = permutation(sub);
		free(sub);
	}
	for (int j = 0; j < 24; j++)
	{
		bin[j] = (bin[j] == K[k]) ? '0': '1';
	
		k++;
	}
	return bin;
}

int conv_pr_subst(char *test)
{	
	for(int i = 0; i < 16; i++)
	{
		if (!strncmp(test, binary[i], 4))
		{
			return i;
		}
	}
	return -1;
}

char *substitution(char *bin)
{
	char *sub = malloc(sizeof(char) * 24);
	char mot[4];

	for (int j = 0; j <= 20; j += 4)
	{
		strncpy(mot, &bin[j],4);
		int indice = conv_pr_subst(mot);
		strncpy(&sub[j], &S_bin[indice*4], 4);
	}
	
	return sub;
}

char *permutation(char *bin)
{
	char *permu = malloc(sizeof(char) * 24);

	for (int i = 0; i < 24; i++)
	{
		permu[P[i]] = bin[i];
	}

	return permu;
}

int *decimal_to_bin(int x)
{
	int *xor = malloc(sizeof(int) * 5);
	for(int i = 1; i < 5; i++)
	{
		xor[i] = binary[x][i-1] - '0';
	}
	return xor;
}

char* key_schedule(char m_cle_hexa[6])
{
	char master_cle[80];	// creation de la master cle
	char cle_hexa_pr_S[4];	// creation cle pour substitution avec S
	int *xor;				//creation tab conenant indice cle sur 5bits
	char decalage[80];		//creation cle pour decalage
	int indice;	
	
	char *cle_small = hexa_to_bin(m_cle_hexa); //On convertit la cle de l'hexa 

	//ajout de la cle en binaire et des 0
	for (int i = 0; i < 24; i++)
	{
		master_cle[i] = cle_small[i];
	}
	for (int i = 24; i < 80; i++)
	{
		master_cle[i] = '0';
	}

	char *Ki = malloc(sizeof(char) * 264);	// contiendra les 11 cle de 24bits
	int j = 0;								//pour circuler dans les K
	int k = 1;							 	// indice de la cle k

	for (int x = 0; x < 264; x += 24)		//264 pour 11 sous cle
	{
		//Ki recupere sa cle attribuee
		for (int i = 40; i <= 63; i++)
		{
			Ki[j] = master_cle[i];
			j++;
		}

		//Decalage des bits. Le tableau est a l'envers donc k79 de l'enonce = k0 ici
		int i = 61;
		for(int decal = 0; decal <= 79; decal++)
		{
			decalage[decal] = master_cle[i%80]; //Le modulo permet de passer de 79 a 0 sans faire une deuxieme boucle
			i++; 
		}

		strncpy(master_cle, decalage, sizeof(char)*80); // on met a jour la master cle de 80bit

		//mini substitution k79 ... k76
		strncpy(cle_hexa_pr_S, master_cle, 4);
		indice = conv_pr_subst(cle_hexa_pr_S); //conversion de l'indice pour avoir les bon bit a substituer
		strncpy(master_cle, &S_bin[indice*4], 4);

		//Xor!!!!!! On xor avec les bits k19...k15
		xor = decimal_to_bin(k); //transfome indice decimal en 5 bit

		master_cle[60] = xor[0] ^ (master_cle[60] == '1') ? '1' : '0';
		master_cle[61] = xor[1] ^ (master_cle[61] == '1') ? '1' : '0';
		master_cle[62] = xor[2] ^ (master_cle[62] == '1') ? '1' : '0';
		master_cle[63] = xor[3] ^ (master_cle[63] == '1') ? '1' : '0';
		master_cle[64] = xor[4] ^ (master_cle[64] == '1') ? '1' : '0';

		k++; //augemente K pour changer de sous cle k

		free(xor);
	}
	free(cle_small);

	return Ki;
}

#endif