
// void AjouterMatiere ();
// void SupprimerMatiere ();
// void ModifierMatiere ();
// int AfficherMatiere();
// void ListerMatiere();
// void InitialiseChaine();


void AjouterMatiere () {

	FILE *fichier = NULL;
	Matiere matiere;
	int c = 0;

	fichier = fopen("../Donnees/Matiere.csv", "a");

	if (fichier != NULL) {
		
		getchar();
		printf("|                                                                 |\n");
		printf(" \tLibelle de la matiere : ");
		fgets(matiere.libelle, MAX_LONG_LIBELLE, stdin);
		SupprimerEspace(matiere.libelle);

		if (strlen(matiere.libelle) >= MAX_LONG_LIBELLE) {

			do { 
    		    c = getchar(); 
	    	} while (c != '\n' && c != EOF);
		}	

		matiere.libelle[strlen(matiere.libelle) - 1] = '\0';  

		printf(" \tCoefficient : ");
		scanf("%d", &matiere.coefficient);

		matiere.reference = NouveauReferenceMatiere();

		fprintf(fichier, "\n%d;%s ;%d", matiere.reference, matiere.libelle, matiere.coefficient);
	}

	fclose(fichier);
}

void SupprimerMatiere (int reference){

	Matiere matiere;

	char chaine[MAX_CARACTERE_LIGNE];

	FILE *obsolete = NULL, *copie = NULL;

	rename("../Donnees/Matiere.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r");
	copie = fopen("../Donnees/Matiere.csv", "a");

	if (copie != NULL && obsolete != NULL) {
		
		fseek(obsolete, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			fscanf(obsolete, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

			// ON COPIE TOUS SAUF LA MATIERE A SUPPRIMER

			if (reference != matiere.reference) {
				
				fprintf(copie, "\n%d;%s ;%d", matiere.reference, matiere.libelle, matiere.coefficient);
			}

			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
	}

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);
/*

	ON SUPPRIMER LES ASSOCIATIONS ENTRE MATIERE ET CLASSE UNITILE

*/
	FILE * fichier = NULL;
	int code = 0;
	MatiereClasse association;

	fichier = fopen("../Donnees/Classe.csv", "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;", &code);
			association.code = code;
			association.reference = reference;
			SupprimerAssociation(association);
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);
}

void ModifierMatiere () {

	int reference = 0;
	int c; 

	Matiere matiere;
	Matiere matiereModifier;

	char chaine[MAX_CARACTERE_LIGNE];

	FILE *obsolete = NULL, *copie = NULL;

	const char nomfichier[] = "../Donnees/Matiere.csv";
	
	/* RECUPERATION DES NOUVELLES INFORMATIONS SUR LA MATIERE*/

	reference = MenuChoixListeMatiere();

	if (reference != 0) {		
		
		rename("../Donnees/Matiere.csv", "../Donnees/fichierObsolete.csv");
		copie = fopen("../Donnees/Matiere.csv", "a+");
		obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");

		printf("\tNouveau Nom : ");
		fscanf(stdin,"%s", matiereModifier.libelle);
	  
	    do { 
	        c = getchar(); 
	    } while (c != '\n' && c != EOF);

	    printf("\tNouveau Coefficient : ");
	    scanf("%d", &matiereModifier.coefficient);

	    /* ON ESSAYE DE COPIER LE FICHIER EN MODIFIANT LA PARTIE QUI NOUS INTERRESSE */


		if (copie != NULL && obsolete != NULL) {
			

			fseek(obsolete, 0, SEEK_SET);

			while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

				fscanf(obsolete, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

				if (reference != matiere.reference) {
					
					fprintf(copie, "\n%d;%s ;%d", matiere.reference, matiere.libelle, matiere.coefficient);
							
				} else {

					fprintf(copie, "\n%d;%s ;%d", reference, matiereModifier.libelle, matiereModifier.coefficient);
				}

				fseek(obsolete, ftell(obsolete), SEEK_SET);
			}
		}
		fclose(obsolete);
		remove("../Donnees/fichierObsolete.csv");
		fclose(copie);
	}
}

void ListerMatiere () {

	Matiere matiere;
	char chaine[MAX_CARACTERE_LIGNE];

	FILE *fichier = NULL;

	fichier = fopen("../Donnees/Matiere.csv", "r");

	if (fichier != NULL) {
		
		printf("+------------------------------------------------+\n");
		printf("|  reference  |      Libelle       | coefficient |\n", matiere.reference, matiere.libelle, matiere.coefficient);
		printf("+------------------------------------------------+\n");

		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

			printf("|     %2d      |   %10s       |      %1d      |\n", matiere.reference, matiere.libelle, matiere.coefficient);
			printf("+------------------------------------------------+\n");
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
		getchar();
		getchar();
	}
	fclose(fichier);
}

