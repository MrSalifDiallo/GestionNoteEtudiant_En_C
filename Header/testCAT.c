#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *fichier = NULL;
	char domaine[20] = {'\0'};
	char chaine[7] = {'\0'};
	int n = 100000;
	char mail[60] = {'\0'};
	int numero = 154007;
	char nom[] = "bar";
	int nb = 0;

	fichier = fopen("domaine.txt", "r");

	if (fichier != NULL) {
		fscanf(fichier, "%d;%s", &nb, domaine);

		for (int i = 0; i < 6; ++i) {
			
			chaine[i] = numero/n + 48;
			numero = numero - (numero/n) * n;
			n = n/10;
		}
		strcat(mail, nom);
		strcat(mail, chaine);
		strcat(mail, domaine);
	}

	fclose(fichier);
	printf("%s\n", mail);
	return 0;
}