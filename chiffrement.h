#ifndef CHIFFREMENT_H
#define CHIFFREMENT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//char S[16];
extern const int P[24];
extern const char S_bin[64];
extern const char digits[16];
extern const char binary[16][5];
//petites fonctions utiles
void aff_with_space_bin(char *bin);
int* decimal_to_bin(int x);
int conv_pr_subst(char* test);
//fonction conversion
char *hexa_to_bin(char hexa[6]);
//char *bin_to_hexa(char* bin);

//fonctions principal
char *substitution(char *bin);
char *permutation(char *bin);
char *key_schedule(char m_cle_hexa[6]);
char *chiffrement(char etat[6], char *K);
void print_bin_to_hexa(char bin[24]);



#endif // CHIFFREMENT_H
