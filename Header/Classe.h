

// int AjouterClasse();
// int ModifierClasse();
// int SupprimerClasse();
// int ListerClasse (int choix);

int AjouterClasse() {

	FILE *fichier = NULL;
	Classe classe;
	int niveau = 0;
	char niv[10] = {'\0'};
	int existe = 0;

	fichier = fopen("../Donnees/Classe.csv", "a");

	if (fichier != NULL) {
		
		fflush(stdin);
		int c = 0; 
	  
	    do { 
	        c = getchar(); 
	    } while (c != '\n' && c != EOF);
		printf("|                                                                 |\n");
		printf(" \tNom classe : ");
		fgets(classe.nom, MAX_LONG_NOM, stdin);

		if (strlen(classe.nom) >= MAX_LONG_NOM) {

	 	   do { 
	    	    c = getchar(); 
	    	} while (c != '\n' && c != EOF);
		}
		SupprimerEspace(classe.nom);
		classe.nom[strlen(classe.nom) - 1] = '\0';  

		printf("\tNiveau classe : \n");
		printf("\t               1 : Licence\n");
		printf("\t               2 : Master\n");
		printf("\tNiveau : ");
		scanf("%d", &niveau);
		getchar();

		while (niveau < 1 || niveau > 2) {
			
			printf("Veillez choisir un niveau correcte !!! : ");
			scanf("%d", &niveau);
		}
		classe.niveau = niveau;

		if (niveau == 1) {
			strcpy(niv, "Licence");
		} else {

			strcpy(niv, "Master");
		}

		existe = RechercheClasse(classe);
		if (!existe) {
		
			classe.code = NouveauCode(classe.niveau);
			fprintf(fichier, "\n%d;%s ;%hd", classe.code, classe.nom, classe.niveau);

			CLEAR;
			printf("+------------------------------------------------------+\n");
			printf("|                Vous venez d'ajouter :                |\n");
			printf("|              %3d %16s %10s          |\n", classe.code, classe.nom, niv);
			printf("+------------------------------------------------------+\n");
			getchar();

		} else  {

			printf("Cette classe existe deja !!!");
			getchar();
		}

	}
	fclose(fichier);
}
int RechercheClasse(Classe classe) {

	Classe classePresent;

	FILE *fichier = NULL;
	char chaine[MAX_CARACTERE_LIGNE];

	fichier = fopen("../Donnees/Classe.csv", "r");

	fseek(fichier, 0, SEEK_SET);
	while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

		fscanf(fichier,"%d;%s ;%hd", &classePresent.code, classePresent.nom, &classePresent.niveau);
		if (strcmp(classePresent.nom, classe.nom) == 0 && classe.niveau == classePresent.niveau) {
			
			fclose(fichier);
			return 1;
		}
		fseek(fichier, ftell(fichier), SEEK_SET);
	}
	fclose(fichier);
	return 0;
}

int ModifierClasse() {

	int code = 0;
	int c; 
	int niveau = 0;

	Classe classe;
	Classe classeModifier;

	char chaine[MAX_CARACTERE_LIGNE];

	FILE *obsolete = NULL, *copie = NULL;

	const char nomfichier[] = "../Donnees/Classe.csv";
	
	/* RECUPERATION DES NOUVELLES INFORMATIONS SUR LA classe*/
	code = MenuListerClasse();

	if (code != 0) {

		rename("../Donnees/Classe.csv", "../Donnees/fichierObsolete.csv");
		copie = fopen("../Donnees/Classe.csv", "a+");
		obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");

	    do { 
	        c = getchar(); 
	    } while (c != '\n' && c != EOF);

		printf("\tNouveau Nom : ");
		fgets(classeModifier.nom, MAX_LONG_NOM, stdin);

		
		if (strlen(classeModifier.nom) >= MAX_LONG_NOM - 1) {
			
		    do { 
		        c = getchar(); 
		    } while (c != '\n' && c != EOF);
		}

		classeModifier.nom[strlen(classeModifier.nom) - 1] = '\0';
		SupprimerEspace(classeModifier.nom);

	   
		printf("\tNiveau classe : \n");
		printf("\t               1 : Licence\n");
		printf("\t               2 : Master\n");
		printf("\tNiveau : ");
		scanf("%d", &niveau);
		getchar();

		while (niveau < 1 || niveau > 2) {
			
			printf("Veillez choisir un niveau correcte !!! : ");
			scanf("%d", &niveau);
		}
		classe.niveau = niveau;

	    /* ON ESSAYE DE COPIER LE FICHIER EN MODIFIANT LA PARTIE QUI NOUS INTERRESSE */


		if (copie != NULL && obsolete != NULL) {
			

			fseek(obsolete, 0, SEEK_SET);

			while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

				fscanf(obsolete, "%d;%s ;%hd", &classe.code, classe.nom, &classe.niveau);

				if (code != classe.code) {
					
					fprintf(copie, "\n%d;%s ;%hd", classe.code, classe.nom, classe.niveau);
							
				} else {

					fprintf(copie, "\n%d;%s ;%hd", code, classeModifier.nom, classeModifier.niveau);
				}

				fseek(obsolete, ftell(obsolete), SEEK_SET);
			}
		}

		fclose(obsolete);
		remove("../Donnees/fichierObsolete.csv");
		fclose(copie);
		}
	}

int SupprimerClasse() {

	int code = 0;

	code = MenuListerClasse();

	if (code != 0) {

		Classe classe;
		char chaine[MAX_CARACTERE_LIGNE];
		FILE *obsolete = NULL, *copie = NULL;

		rename("../Donnees/Classe.csv", "../Donnees/fichierObsolete.csv");

		obsolete = fopen ("../Donnees/fichierObsolete.csv", "r");
		copie = fopen("../Donnees/Classe.csv", "a");

		if (copie != NULL && obsolete != NULL) {
			
			fseek(obsolete, 0, SEEK_SET);

			while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

				fscanf(obsolete, "%d;%s ;%hd", &classe.code, classe.nom, &classe.niveau);

				if (code != classe.code) {
					
					fprintf(copie, "\n%d;%s ;%hd", classe.code, classe.nom, classe.niveau);
				}

				fseek(obsolete, ftell(obsolete), SEEK_SET);
			}
		}

		fclose(obsolete);
		remove("../Donnees/fichierObsolete.csv");
		fclose(copie);

		FILE *fichier = NULL;
		MatiereClasse association;
		int reference = 0;

		fichier = fopen("../Donnees/Matiere.csv", "r");

		if (fichier != NULL) {
			
			fseek(fichier, 0, SEEK_SET);

			while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

				fscanf(fichier, "%d;", &reference);
				association.code = code;
				association.reference = reference;
				SupprimerAssociation(association);
				fseek(fichier, ftell(fichier), SEEK_SET);
			}
		}
		fclose(fichier);
	}
}

int ListerClasse (int choix) {

	if (choix == 0) {
		
		return 0;
	}

	CLEAR;

	FILE *fichier_classe = NULL;
	FILE *fichier_etudiant = NULL;
	int nombreEtudiant = 0;
	char niveau[9] = {'\0'};
	float moyenne = 0;
	int rang = 0;

	Classe classe;
	Etudiant etudiant;

	char chaine[MAX_CARACTERE_LIGNE];

	fichier_classe = fopen("../Donnees/Classe.csv", "r+");
	fichier_etudiant = fopen("../Donnees/Etudiant.csv", "r+");

	if (fichier_classe != NULL) {

		fseek(fichier_classe, 0, SEEK_SET);
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_classe) != NULL) {

			fscanf(fichier_classe, "%d;%s ;%hd", &classe.code, classe.nom, &classe.niveau);

			if (classe.code == choix) {

				if (classe.niveau == Licence)
					strcpy(niveau, "Licence");
				else
					strcpy(niveau, "Master");
				
				printf("+--------------------------------------------------------------------------------------------------------+\n");
				printf("|                                                                                                        |\n");
				printf("|%50s  %9s                                           |\n", classe.nom, niveau);
				printf("|                                                                                                        |\n");
				printf("+-----------------+-----------+------------------+---------------------+----------------+---------+------+\n");
				printf("| Numero Etudiant |    Nom    |      Prenom      |         Mail        | Date Naissance | Moyenne | Rang |\n");
				printf("+-----------------+-----------+------------------+---------------------+----------------+---------+------+\n");

				break;
			}

			fseek(fichier_classe, ftell(fichier_classe), SEEK_SET);
		}

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_etudiant) != NULL) {

			fscanf(fichier_etudiant, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (classe.code == etudiant.classe) {

				moyenne = MoyenneFinale(etudiant.numero, etudiant.classe);
				rang = Rang(etudiant.numero, etudiant.classe);
				
				printf("|%17d|%11s|%18s|%21s|    %02d\\%02d\\%4d  |%9g|%6d|\n",etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee, moyenne, rang);
				printf("+-----------------+-----------+------------------+---------------------+----------------+---------+------+\n");
				nombreEtudiant ++;
			}

			fseek(fichier_etudiant, ftell(fichier_etudiant), SEEK_SET);
		}
		printf("|                                       nombre d'etudiant : %2d                                           |\n", nombreEtudiant);
		printf("+--------------------------------------------------------------------------------------------------------+\n");
	}
	fclose(fichier_classe);
	fclose(fichier_etudiant);
	getchar();
	getchar();
}