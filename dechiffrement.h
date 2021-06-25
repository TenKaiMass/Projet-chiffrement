#ifndef DECHIFFREMENT_H
#define DECHIFFREMENT_H

#include "chiffrement.h"

extern const int S[16];

char *inverse_substitution(char *bin);
char *inverse_permutation(char *bin);
char *dechiffrement(char *bin, char *K);

#endif // DECHIFFREMENT_H
