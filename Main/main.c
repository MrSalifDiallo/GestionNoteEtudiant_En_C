#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/Prototype.h"


int Menu ();

typedef enum {
	
	vide,
	gestionClasses=3,
	gestionEtudiants=1,
	gestionNotes=4,
	gestionMatieres=2,

} menu;

int main(int argc, char const *argv[]) {

	int retour = 0;
	menu choix = 0;

	Debut :
	
	CLEAR;
	system("COLOR 07"); 
	rename("domaine.txt", "domaineBis.txt");
	FILE *fichier_copie = fopen("domaine.txt", "a");
	FILE *fichier = fopen("domaineBis.txt", "r+");
	char domaine[21];
	int existe = 0;

	if (fichier != NULL) {
		
		fscanf(fichier, "%d;%s", &existe, domaine);
		if (!existe) {
			
			printf("+--------------------------------------------------------------------+\n");
			printf("|                                                                    |\n");
			printf("|    Bienvenue dans SengNote votre application de gestion de note    |\n");
			printf("|   Pour commencer veillez renseigner le domain de l'etablissement   |\n");
			printf("|                                                                    |\n");
			printf("+--------------------------------------------------------------------+\n");
			printf("\tEntrer le domaine : ");
			fgets(domaine, 20, stdin);
			domaine[strlen(domaine) - 1] = '\0';
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

		CLS;
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
		
		default: 
		CLS;
        printf("$$\\      $$\\                               $$\\                       $$\\       $$\\                      $$\\                $$\\\n");     
        printf("$$$\\    $$$ |                              \\__|                      $$ |      \\__|                     $$ |               $$ |\n");    
        printf("$$$$\\  $$$$ | $$$$$$\\   $$$$$$\\   $$$$$$$\\ $$\\        $$$$$$\\        $$$$$$$\\  $$\\  $$$$$$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\ $$$$$$\\\n");   
        printf("$$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$  _____|$$ |       \\____$$\\       $$  __$$\\ $$ |$$  __$$\\ $$  __$$\\_$$  _|  $$  __$$\\_$$  _|\n");  
        printf("$$ \\$$$  $$ |$$$$$$$$ |$$ |  \\__|$$ /      $$ |       $$$$$$$ |      $$ |  $$ |$$ |$$$$$$$$ |$$ |  $$ | $$ |    $$ /  $$ | $$ |\n");    
        printf("$$ |\\$  /$$ |$$   ____|$$ |      $$ |      $$ |      $$  __$$ |      $$ |  $$ |$$ |$$   ____|$$ |  $$ | $$ |$$\\ $$ |  $$ | $$ |$$\\\n"); 
        printf("$$ | \\_/ $$ |\\$$$$$$$\\ $$ |      \\$$$$$$$\\ $$ |      \\$$$$$$$ |      $$$$$$$  |$$ |\\$$$$$$$\\ $$ |  $$ | \\$$$$  |\\$$$$$$  | \\$$$$  |\n");
        printf("\\__|     \\__| \\_______|\\__|       \\_______|\\__|       \\_______|      \\_______/ \\__| \\_______|\\__|  \\__|  \\____/  \\______/   \\____/\n"); 
		return 0;
	}

	if (retour) {

		goto Debut;
	}
}

int Menu()
{
    int choix;
    printf(".----------------------------------------------------------------------------.\n");
    printf("| .------------------------------------------------------------------------. |\n");
    printf("| |              \\    |  ___|     /  ___>     |  _ \\   /       __--__      | |\n");
    printf("| |               \\   |  ___|     \\___  \\     |  __/  /    __--      --__  | |\n");
    printf("| |                \\  |_____|     <_____/     |__|   /   --__          __--| |\n");
    printf("| |                 \\_______________________________/        --__  __--  | | |\n");
    printf("| |                                                           |  --  |   | | |\n");
    printf("| |                                                            --__--    * | |\n");
    printf("| |    Choisissez une option:                                              | |\n");
    printf("| |                          1.Gestion des etudiants                       | |\n");
    printf("| |                          2.Gestion des matieres                        | |\n");
    printf("| |                          3.Gestion des Classes                         | |\n");
    printf("| |                          4.Gestion des Notes                           | |\n");
    printf("| |                          5.Quitter l'application                       | |\n");
    printf("| |                                                                        | |\n");
    printf("| |                                                                        | |\n");
    printf("| |                                                                        | |\n");
    printf("| |                                                                        | |\n");
    printf("| |                                                                        | |\n");
    printf("| |                                                                        | |\n");
    printf("| |________________________________________________________________________| |\n");
    printf("|____________________________________________________________________________|\n");
    printf("                        )__________|__|__________(                            \n");
    printf("                       |            ||            |                           \n");
    printf("                       |____________||____________|                           \n");

    printf("\n");
    printf("\tVotre choix (1\\2\\3\\4\\5) : ");
	scanf("%d", &choix);
	return choix;
}
