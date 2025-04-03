

int MenuPrincipale() {

	int choix = 0;

	Debut:
	NR;
	CLEAR;
    printf("+------------------------------------------------------------------------------------+\n");
    printf("|        .--.                   .---.    ==>Choissisez une option :                  |\n");
    printf("|    .---|L |           .-.     | D |             1.Ajout d'une matiere              |\n");
    printf("| .--| A |A |_          |_|     | A |--.          2.Modification Matiere             |\n");
    printf("| |M | L |N |'\\     .---!~|  .--| T |--|          3.Associer une matiere a une classe|\n");
    printf("| |A | G |G |.'\\    | O | |--|%% | A |  |          4.Lister les matieres              |\n");
    printf("| |T | O |A |\\.'\\   | S | |__|  |   |  |          5.Supprimer Matiere                |\n");
    printf("| |H |   |G | \\  \\  |===| |==|  |   |  |          6.Revenir en arriere               |\n");
    printf("| |S |   |E_|  \\.'\\ |   |_|__|  |~~~|__|                                             |\n");
    printf("| |  |===|C |   \\.'\\|\\|~|--|%%|~~~|-- |  |                                            |\n");
    printf("| ^--^---'--^    `-'`---^-^--^--^---'--'                                             |\n");
    printf("|\t     Votre choix (1\\2\\3\\4\\5\\6) :");
    scanf("%d",&choix);


	while (choix < 1 || choix > 6) {
		CLEAR;
		goto Debut;
	}

	return choix;
}	

void MenuAjouter() {

	
	CLEAR;
	printf("      _/_/    _/                        _/   \n");
	printf("   _/    _/        _/_/    _/    _/  _/_/_/_/\n");   
	printf("  _/_/_/_/  _/  _/    _/  _/    _/    _/     \n");   
	printf(" _/    _/  _/  _/    _/  _/    _/    _/      \n");   
	printf("_/    _/  _/    _/_/      _/_/_/      _/_/   \n");   
	printf("         _/                                  \n");   
	printf("      _/                                     \n");

}	

void MenuModifier() {

	
	CLEAR;

	printf(".______       _______ .__   __.      ___      .___  ___.  _______ \n");
	printf("|   _  \\     |   ____||  \\ |  |     /   \\     |   \\/   | |   ____|\n");
	printf("|  |_)  |    |  |__   |   \\|  |    /  ^  \\    |  \\  /  | |  |__   \n");
	printf("|      /     |   __|  |  . `  |   /  /_\\  \\   |  |\\/|  | |   __|  \n");
	printf("|  |\\  \\----.|  |____ |  |\\   |  /  _____  \\  |  |  |  | |  |____ \n");
	printf("| _| `._____||_______||__| \\__| /__/     \\__\\ |__|  |__| |_______|\n");

}

void MenuSupprimer() {

	int reference = 0;
	int reference_existe = 0;
	const char nomfichier[] = "../Donnees/Matiere.csv"; 

	reference = MenuChoixListeMatiere();

	if (reference != 0) {
		printf("    _/_/_/              _/              _/                      {__   \n");  
		printf("   _/    _/    _/_/    _/    _/_/    _/_/_/_/    _/_/         {__    \n"); 
		printf("  _/    _/  _/_/_/_/  _/  _/_/_/_/    _/      _/_/_/_/   {__ {__      \n"); 
		printf(" _/    _/  _/        _/  _/          _/      _/           {_ {__      \n"); 
		printf("_/_/_/      _/_/_/  _/    _/_/_/      _/_/    _/_/_/       {__   \n");  
		SupprimerMatiere(reference);
	}
}	

int MenuAssocier() {

	int choix = 0;

	Debut:
	
	CLEAR;
	printf("+------------------------------------------------------------------------------------+\n");
    printf("|        .--.                   .---.    ==>Choissisez une option :                  |\n");
    printf("|    .---|L |           .-.     | D |             1.Associer une matiere a une classe|\n");
    printf("| .--| A |A |_          |_|     | A |--.          2.Supprimer une association        |\n");
    printf("| |M | L |N |'\\     .---!~|  .--| T |--|          3.Revenir en arriere               |\n");
    printf("| |A | G |G |.'\\    | O | |--|%% | A |  |                                             |\n");
    printf("| |T | O |A |\\.'\\   | S | |__|  |   |  |                                             |\n");
    printf("| |H |   |G | \\  \\  |===| |==|  |   |  |                                             |\n");
    printf("| |S |   |E_|  \\.'\\ |   |_|__|  |~~~|__|                                             |\n");
    printf("| |  |===|C |   \\.'\\|\\|~|--|%%|~~~|-- |  |                                            |\n");
    printf("| ^--^---'--^    `-'`---^-^--^--^---'--'                                             |\n");
	printf("|                                                                 |\n");
	printf("\t     Votre choix (1\\2\\3) : ");
	scanf("%d", &choix);


	while (choix < 1 || choix > 3) {

		
		CLEAR;
		goto Debut;
	}

	switch (choix) {

		case 1: 
			AssocierMatiere();
		break;

		case 2: 
			MenuSupprimerAssociation();
		break;
		
		default : return 1;
	}

	goto Debut;
}

int  MenuSupprimerAssociation() {

	MatiereClasse association;

	int choix = 0;

	Debut:

	
	CLEAR;
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|           Cette Option vas Supprimer toutes les notes           |\n");
	printf("|                                                                 |\n");
	printf("|         enregister dans Cette matiere pour cette classe         |\n");
	printf("|                                                                 |\n");
	printf("|                Voulez vous toujours continuer :                 |\n");
	printf("|                                                                 |\n");
	printf("|                           1 : Continuer                         |\n");
	printf("|                           2 : Retour                            |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("                  Votre choix :");
	scanf("%d", &choix);

	while (choix < 1 || choix > 2) {

		
		CLEAR;
		goto Debut;
	}

	if (choix == 1) {

		association.code = MenuListerClasse();
		if (association.code != 0) {

			association.reference = MenuChoixMatiere(association.code);

			if (association.reference != 0){
				printf("          {__\n");
				printf("         {__\n");
				printf("{__     {__\n");
				printf(" {__   {__\n");
				printf("  {__ {__\n");  
				printf("   {_{__\n");   
				printf("    {__     SUCCES\n");    
				SupprimerAssociation(association);
				return 1;
			} else
				return 1;
		} else
			return 1;
	} else {

		return 1;
	}
}	

int MenuAfficherMatiere() {

	
	CLEAR;

	int choix = 0;

	Debut :

	printf("+------------------------------------------------------------------------------------+\n");
    printf("|        .--.                   .---.    ==>Choissisez une option :                  |\n");
    printf("|    .---|L |           .-.     | D |             1.Lister toutes les matieres       |\n");
    printf("| .--| A |A |_          |_|     | A |--.          2.Lister matiere(s) d'une classe   |\n");
    printf("| |M | L |N |'\\     .---!~|  .--| T |--|                                             |\n");
    printf("| |A | G |G |.'\\    | O | |--|%% | A |  |                                             |\n");
    printf("| |T | O |A |\\.'\\   | S | |__|  |   |  |                                             |\n");
    printf("| |H |   |G | \\  \\  |===| |==|  |   |  |                                             |\n");
    printf("| |S |   |E_|  \\.'\\ |   |_|__|  |~~~|__|                                             |\n");
    printf("| |  |===|C |   \\.'\\|\\|~|--|%%|~~~|-- |  |                                            |\n");
    printf("| ^--^---'--^    `-'`---^-^--^--^---'--'                                             |\n");

	printf("\t     Votre choix (1\\2) : ");
	scanf("%d", &choix);


	while (choix < 1 || choix > 2) {
		
		CLEAR;
		goto Debut;
	}

	return choix;;
}	

int AfficherMatiere () {

	int choix;
	
	choix = MenuAfficherMatiere();

	switch (choix) {

		case 1:

			ListerMatiere();

		break;

		case 2:

			ListerMatiereParClasse();

		break;
	}

	return 1;
}

int GestionMatieres () {
	
	int choix = 0;

	Debut:

	choix = MenuPrincipale();

	switch (choix) {

		case 1:

			MenuAjouter();
			AjouterMatiere();

		break;
	
		case 2:

			MenuModifier();
			ModifierMatiere();

		break;

		case 3:
			MenuAssocier();
		break;

		case 4:
			AfficherMatiere();
		break;

		case 5:
			MenuSupprimer();
		break;

		default:
		return 1;
	}

	goto Debut;
}

int MenuChoixListeMatiere () {


	int choix = 0;

	Debut:

	 CLEAR;
	
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                       Liste des matieres                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez une matiere :                             |\n");
	printf("|                                                                 |\n");

	FILE *fichier = NULL;
	Matiere matiere;
	char chaine[MAX_CARACTERE_LIGNE];
	int nombreMatiere = 0;

	const int MAX_TABLEAU = 100;

	int tableauReference[MAX_TABLEAU];

	fichier = fopen("../Donnees/Matiere.csv", "r");

	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			nombreMatiere ++;
			fscanf(fichier, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

			printf("|\t\t   %d : %10s  %d                              |\n", nombreMatiere, matiere.libelle, matiere.coefficient);

			tableauReference[nombreMatiere] = matiere.reference;
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);

	printf("|                                                                 |\n");
	printf("\t     Votre choix entre (0..%d) : ", nombreMatiere);
	scanf("%d", &choix);

	while (choix < 0 || choix > nombreMatiere) {
		
		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (1..%d)!                    |\n", nombreMatiere);
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
	return tableauReference[choix];
}

int MenuChoixMatiere (int code) {

	if (code == 0) {
		
		return 1;
	}

	int dejaAfficher = 0;
	int choix = 0;

	Debut:

	 CLEAR;
	
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                       Liste des Matieres                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez une Matiere :                             |\n");
	printf("|                                                                 |\n");

	FILE *fichier_association = NULL;
	FILE *fichier_matiere = NULL;

	MatiereClasse association;
	Matiere matiere;

	char chaine[MAX_CARACTERE_LIGNE];
	int nombreMatiere = 0;

	const int MAX_TABLEAU = 100;

	int tableauReference[MAX_TABLEAU];

	fichier_association = fopen("../Donnees/MatiereClasse.csv", "r");
	fichier_matiere = fopen("../Donnees/Matiere.csv", "r");

	if (fichier_association != NULL) {

		fseek(fichier_association, 0, SEEK_SET);
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_association) != NULL) {

			fscanf(fichier_association, "%d;%d", &association.code, &association.reference);

			if (code == association.code) {
				
				fseek(fichier_matiere, 0, SEEK_SET);
				
				while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_matiere) != NULL) {

					fscanf(fichier_matiere, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

					if (matiere.reference == association.reference && dejaAfficher != matiere.reference) {

						nombreMatiere ++;
						dejaAfficher = matiere.reference;
						printf("|\t\t   %d : %10s %d                               |\n", nombreMatiere, matiere.libelle, matiere.coefficient);
						tableauReference[nombreMatiere] = association.reference;
					}
					fseek(fichier_matiere, ftell(fichier_matiere), SEEK_SET);
				}
			}
			fseek(fichier_association, ftell(fichier_association), SEEK_SET);
		}
	}

	fclose(fichier_association);
	fclose(fichier_matiere);

	printf("| 0 : revenir en arriere                                          |\n");
	printf("|                                                                 |\n");

	printf("\t     Votre choix entre (0..%d) : ", nombreMatiere);
	scanf("%d", &choix);


	while (choix < 0 || choix > nombreMatiere) {

		
		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (1..%d)!                    |\n", nombreMatiere);
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		getchar();
		getchar();
		
		CLEAR;
		
		goto Debut;
	}

	if (!choix)
		return 0;
	 else
		return tableauReference[choix];
}