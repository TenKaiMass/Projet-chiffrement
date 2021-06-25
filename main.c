#include "dechiffrement.h"
#include "chiffrement.h"

int main(int argc, char const *argv[])
{	
	
	char message[6];// message
	char cle[6];//cle
	
	printf("entrer votre message : ");
	scanf("%s", message);
	printf("entrer votre clé : ");
	scanf("%s", cle);

	//generation des cle
	char* test_covid = key_schedule(cle);
	int x = 1;
	char sub_key[24]; 
	for (int i = 0; i < 264; i+=24)
	{
		printf("K%d : ",x);
		for (int j = i; j < i+24; j++)
		{
			sub_key[j-i] = test_covid[j];
			printf("%c", test_covid[j]);
		}
		x++;
		printf(" | ");
		print_bin_to_hexa(sub_key);
	}

	//chiffrage du message
	char* mess_chif = chiffrement(message, test_covid); 
	printf("Message chiffré : ");
	print_bin_to_hexa(mess_chif);

	//dechiffrage du message 
	char* dechif = dechiffrement(mess_chif, test_covid); 
	printf("Message dechiffré : ");
	print_bin_to_hexa(dechif);

	//liberation mémoire
	free(dechif);
	free(test_covid);

	return 0;
}

