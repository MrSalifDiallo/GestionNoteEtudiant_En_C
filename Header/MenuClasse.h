

int GestionClasses() {

	int choix = 0;
	int choixListe = 0;

	Debut:

	choix = MenuClasse();

	switch (choix) {

		case 1:

			MenuAjouterClasse();
			AjouterClasse();

		break;

		case 2:

			MenuModifierClasse();
			ModifierClasse();

		break;

		case 3:
		
			MenuSupprimerClasse();
			SupprimerClasse();

		break;
		
		case 4:
		
			choixListe = MenuListerClasse();
			ListerClasse(choixListe);

		break;

		default: return 1;
	}

	goto Debut;
}

int MenuClasse() {

	int choix = 0;

	Debut:
	NE;
	CLEAR;

	printf(".............................................................+\n");
	printf("       ooo,    .---.                    @                    |\n");
	printf("      o`  o   /    |\\________________   @                    |\n");
	printf("     o`   'oooo()  | ________   _   _)  @                    |\n");
	printf("     `oo   o` \\    |/        | | | |    @                    |\n");
	printf("       `ooo'   `---'         \"-\" |_|    @                    |\n");
	printf("........................................@                    |\n");
	printf("                 Choissisez une option:                      |\n");
	printf("                                      1.Ajouter une Classe   |\n");
	printf("                                      2.Modifier une Classe  |\n");
	printf("                                      3.Supprimer une Classe |\n");
	printf("                                      4.Lister une Classe    |\n");
	printf("                                      5.Revenir en arriere   |\n");
	printf("-------------------------------------------------------------+\n");
	printf("\t     Votre choix (1\\2\\3\\4\\5) : ");
	scanf("%d", &choix);


	while (choix < 1 || choix > 5) {

		CLEAR;
		
		goto Debut;
	}
	return choix;
}

void MenuAjouterClasse() {

	CLEAR;
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      GESTION DES CLASSES                        |\n");
	printf("|                                                                 |\n");
	printf("|                       Ajouter une Classe                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");
}

void MenuModifierClasse() {

	CLEAR;

	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      GESTION DES CLASSES                        |\n");
	printf("|                                                                 |\n");
	printf("|                      Modifier une Classe                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

}

void MenuSupprimerClasse() {

	CLEAR;
	
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      GESTION DES CLASSES                        |\n");
	printf("|                                                                 |\n");
	printf("|                      Supprimer une Classe                       |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

}

int MenuListerClasse() {

	int choix = 0;

	Debut:

	CLEAR;
	
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                       Liste des classes                         |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez une Classe :                              |\n");
	printf("|                                                                 |\n");

	FILE *fichier = NULL;
	Classe classe;
	char chaine[MAX_CARACTERE_LIGNE];
	int nombreClasse = 0;

	const int MAX_TABLEAU = 100;

	int tableauCodeClasse[MAX_TABLEAU];

	fichier = fopen("../Donnees/Classe.csv", "r+");

	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			nombreClasse ++;
			fscanf(fichier, "%d;%s ;%d", &classe.code, classe.nom, &classe.niveau);

			printf("|\t\t   %d : %10s                                 |\n", nombreClasse, classe.nom);

			tableauCodeClasse[nombreClasse] = classe.code;
			fseek(fichier, ftell(fichier), SEEK_SET);
		}

	}

	fclose(fichier);

	printf("|                                                                 |\n");

	printf("\t     Votre choix entre (0..%d) : ", nombreClasse);
	scanf("%d", &choix);


	while (choix < 0 || choix > nombreClasse) {

		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (1..%d)!                    |\n", nombreClasse);
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		getchar();
		getchar();
		CLEAR;
		
		goto Debut;
	}
	if (choix == 0) {
		
		return 0;
	}
	return tableauCodeClasse[choix];
}
