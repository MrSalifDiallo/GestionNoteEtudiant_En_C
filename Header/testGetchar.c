#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

int main(int argc, char const *argv[]) {
	
	char nom[] = "Papa VoitureA";

	SupprimerEspace(nom);

	RemettreEspace(nom);

	printf("%s\n", nom);

	return 0;
}