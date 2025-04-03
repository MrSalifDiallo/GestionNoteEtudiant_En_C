#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prototype.h"



int Menu ();

typedef enum {
	
	vide,
	gestionClasses,
	gestionEtudiants,
	gestionNotes,
	gestionMatieres

} menu;

int main(int argc, char const *argv[]) {

	int retour = 0;
	menu choix = 0;

	Debut :
	
	CLEAR;

	rename("domaine.txt", "domaineBis.txt");
	FILE *fichier_copie = fopen("domaine.txt", "a");
	FILE *fichier = fopen("domaineBis.txt", "r+");
	char domaine[21];
	int existe = 0;

	if (fichier != NULL) {
		
		fscanf(fichier, "%d;%s", &existe, domaine);
		if (!existe) {
			
			printf("Bienvenue dans SengNote votre application de gestion de note\n");
			printf("Pour commencer veillez renseigner le domain de l'etablissement\n");
			printf("Entrer le domaine : ");
			fgets(domaine, 20, stdin);
			existe = 1;
			fprintf(fichier_copie, "%d;@%s.sn", existe, domaine);
		} else {

			fprintf(fichier_copie, "%d;%s", existe, domaine);
		}
	}
	fclose(fichier_copie);
	fclose(fichier);
	remove("domaineBis.txt");
	CLEAR;
	choix = Menu();

	while(choix < 1 || choix > 5) {

		system("clear");
		printf("\n\n\n");
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (1\\2\\3\\4\\5)!                |\n");
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		getchar();
		getchar();
		system("clear");
		choix = Menu();
	}

	switch (choix) {

		case gestionClasses:
		
			retour = GestionClasses();

		break;

		case gestionEtudiants:
		
			retour = GestionEtudiants();

		break;
		
		case gestionNotes:
		
			retour = GestionNotes();

		break;
		
		case gestionMatieres:
		
			retour = GestionMatieres();

		break;
		
		default: return 0;
	}

	if (retour) {

		goto Debut;
	}
}

int Menu () {

		int choix = 0;

	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|  Bienvenue dans SenNote votre application de gestion de Note !  |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|\t     Choisissez une option :                              |\n");
	printf("|                                                                 |\n");
	printf("|\t\t     1 : Gestion des Classes                      |\n");
	printf("|\t\t     2 : Gestion des Etudiants                    |\n");
	printf("|\t\t     3 : Gestion des Notes                        |\n");
	printf("|\t\t     4 : Gestion des Matieres                     |\n");
	printf("|\t\t     5 : Quitter l'application                    |\n");
	printf("|                                                                 |\n");
	printf("\tVotre choix (1\\2\\3\\4\\5) : ");
	scanf("%d", &choix);

	return choix;
}