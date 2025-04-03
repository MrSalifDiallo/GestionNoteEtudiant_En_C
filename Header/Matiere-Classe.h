
int AssocierMatiere(){

	FILE *fichier_association = NULL;

	MatiereClasse association;

	NOTER estNoter;

	int nombreMatiere = 0;
	int code = 0;
	int reference = 0;
	int choix = 0;
	int existe = 0;
	int n = 0;
	int m = 0;

	char chaine[MAX_CARACTERE_LIGNE];

	fichier_association = fopen("../Donnees/MatiereClasse.csv", "a+");
	getchar();

	if (fichier_association != NULL) {
	
		association.code = MenuListerClasse();
		association.estNoter = non;
		getchar();

		while (association.code != 0) {
			
			printf("   Combien de matiere voulez vous ajouter : ");
			scanf("%d", &nombreMatiere);
			getchar();

			for (int i = 1; i <= nombreMatiere; ++i) {
				
				printf("\n\t\t\t association %d\n", i);
				getchar();

				reessayer:
				association.reference = MenuChoixListeMatiere();
				existe = 0;

				if (association.reference != 0) {

					fseek(fichier_association, 0, SEEK_SET);

					while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_association) != NULL) {

						fscanf(fichier_association, "%d;%d;%d;%d", &code, &reference, &n, &m);

						if (code == association.code && reference == association.reference) {
							
							getchar();
							printf("\n\nCette association existe deja !!!\n");
							getchar();
							existe = 1;
							break;
						}
						fseek(fichier_association, ftell(fichier_association), SEEK_SET);
					}

					if (existe == 0) {
						
						fprintf(fichier_association, "\n%d;%d;%d", association.code, association.reference, association.estNoter);
						printf("\nMatiere ajouter !!!");
						getchar();
						getchar();
					
					} else {

						printf("\t 0 : Annuler \n");
						printf("\t 1 : Ressayer \n\n");
						printf("  votre choix : ");
						scanf("%d", &choix);

						while(choix != 0 && choix != 1) {

							printf("choix non conforme !!\n");
							printf("  votre choix : ");
							scanf("%d", &choix);
						}

						if (choix)
							goto reessayer;
						else
							continue;
					}
				} else
					break;
			}
			association.code = MenuListerClasse();
		}
	}	

	fclose(fichier_association);
	return 1;
}

int ListerMatiereParClasse() {

	FILE *fichier_matiere = NULL;
	FILE *fichier_classe = NULL;
	FILE *fichier_association = NULL;

	MatiereClasse association;
	Matiere matiere;
	Classe classe;
	char  noteRecu[4] = {'\0'};

	fichier_matiere = fopen("../Donnees/Matiere.csv", "r+");
	fichier_classe = fopen("../Donnees/Classe.csv", "r+");
	fichier_association = fopen("../Donnees/MatiereClasse.csv", "r+");

	int code = 0;
	int reference = 0;
	int dejaAfficher = 0;
	char niveau[9] = {'\0'};

	char chaine[MAX_CARACTERE_LIGNE];

	if (fichier_classe != NULL) {
		
		code = MenuListerClasse();

		if (code != 0) {

			while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_classe) != NULL) {

				fseek(fichier_classe, ftell(fichier_classe), SEEK_SET);
				fscanf(fichier_classe, "%d;%s ;%d", &classe.code, classe.nom, &classe.niveau);

				if (code == classe.code)					
					break;
			}
			if (classe.niveau == Licence)
				strcpy(niveau, "Licence");
			else
				strcpy(niveau, "Master");

			if (fichier_matiere != NULL && fichier_association != NULL) {
				
				CLEAR;

				printf("+------------------------------------------------------------+\n");
				printf("|               %15s  %s                      |\n", classe.nom, niveau);
				printf("+------------------------------------------------+-----------+\n");
				printf("|  reference  |      Libelle       | coefficient | Note recu |\n");
				printf("+------------------------------------------------+-----------+\n");

				while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_association) != NULL) {

					fseek(fichier_association, ftell(fichier_association), SEEK_SET);
					fscanf(fichier_association, "%d;%d", &association.code, &association.reference);
					fseek(fichier_matiere, 0, SEEK_SET);

					if (association.code == classe.code) {
				
						while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_matiere) != NULL) {

							fseek(fichier_matiere, ftell(fichier_matiere), SEEK_SET);
							fscanf(fichier_matiere, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);

							if (EstNoter(classe.code, matiere.reference) == oui)
								strcpy(noteRecu, "oui");
							else
								strcpy(noteRecu, "non");

							if (association.reference == matiere.reference && dejaAfficher != matiere.reference) {
								
								printf("|     %2d      |   %10s       |      %1d      |    %3s    |\n", matiere.reference, matiere.libelle, matiere.coefficient, noteRecu);
								printf("+------------------------------------------------+-----------+\n");
								dejaAfficher = matiere.reference;
							}
						}
					}
				}
				getchar();
				getchar();
			}
		}
	}
		fclose(fichier_matiere);
		fclose(fichier_association);
		fclose(fichier_classe);
}

void SupprimerAssociation (MatiereClasse association) {

	char chaine[MAX_CARACTERE_LIGNE];

	FILE *obsolete = NULL, *copie = NULL;
	MatiereClasse associationPresent;

	rename("../Donnees/MatiereClasse.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r");
	copie = fopen("../Donnees/MatiereClasse.csv", "a");

	if (copie != NULL && obsolete != NULL) {
		
		fseek(obsolete, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			fscanf(obsolete, "%d;%d", &associationPresent.code, &associationPresent.reference);

			if (association.code != associationPresent.code || association.reference != associationPresent.reference) {
				
				fprintf(copie, "\n%d;%d", associationPresent.code, associationPresent.reference);
			}

			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
	} else {

		printf("erreur !!!");
		getchar();
		getchar();
	}

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);

	SupprimerNote(association);
}

