// int AjouterEtudiant();
// int ModifierEtudiant();
// int SupprimerEtudiant();
// int ListerEtudiant();
// int TransfererEtudiant();
// void AfficherEtudiant(int numero);
// int ModifierNomPrenom();
// int ModifierDateNaissance();
// int ModifierClasse();
// int ModifierEmail();

/* Cette fonction permet d'enregistrer un etudiant dans le fichier etudiant.csv */

int EnregistrerEtudiant(Etudiant etudiant, int code) {

	/*
	 * Ouverture du fichier etudiant.csv
	 */

	FILE *fichier = NULL;
	fichier = fopen("../Donnees/Etudiant.csv", "a");

	/*
	 * Ces variable vont permettre d'ajouter une note au nouveau
	 * etudiant si la classe avait deja recu une note dans une matiere
	 */

	Note note;
	int tableauReference[MAX_MATIERE] = {0};
	int nombreMatiere = 0;

	// La variable trouver indique si l'etudiant existe deja

	int trouver = 0;

	// Si le fichier n'a pas de probleme on commence la procedure

	if (fichier != NULL) {

		// on recherche d'abord si l'etudiant existe deja avec une fonction booleenne
		trouver = RechercheEtudiant(etudiant);

		//Si non trouver on recupere les informations
		if (!trouver) {
			
			// on verifie si code de la classe est different de zero
			// car l'option code = 0 permet de revenir en arriere

			if (code != 0) {

				// On recupere le code de l'etudiant car il n'a pas était saisi mais choisi avec une menu
				etudiant.classe = code;

				// On creer automatiquement le numero de l'etudiant qui sera composer par le code de la classe
				// fois mille plus sa position durant son inscription
				etudiant.numero = NouveauNumero(etudiant.classe);
				MailGenerateur(etudiant,  etudiant.email);

				// On verifie si la classe a deja recu une note
				nombreMatiere = EstNoters(etudiant.classe, tableauReference);

				//Pour toutes les matieres notees on donne zero au nouuveau etudiant
				for (int i = 0; i < nombreMatiere; i ++) {

					note.reference = tableauReference[i];
					note.numero = etudiant.numero;
					note.noteCC = 0;
					note.noteDS = 0;
				
					NoterEtudiant(note);
				}

				//Enfin on met les information recueillies dans le fichier
				fprintf(fichier, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee, etudiant.classe);
				fclose(fichier);
				return etudiant.numero;

			} else {

				// on retourne en arriere
				fclose(fichier);
				return 1;
			}

		} else {
				
			// l'etudiant existe deja
			fclose(fichier);
			return 0;
		}

	} else {

		fclose(fichier);
		return -1;
	}
}

// Cette fonction permet de saisir les informations sur un etudiant
// elle reçoit a travers une liste de choix le code sa classe

int AjouterEtudiant(int code) {

	Etudiant etudiant;

	// Cette variable permet de voir si l'etudiant a etais ajouter
	int reussi = 0;
  
  	// On vide le buffer avant de commentcer
	int c = 0; 
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF);

    fflush(stdin);

    /*****************************************************************************/
    /*******************ON SAISI LES INFORMATIONS DE L'ETUDIANT*******************/
    /*****************************************************************************/
	printf("|                                                                 |\n");
	printf(" \tNom : ");
	fgets(etudiant.nom, MAX_LONG_NOM, stdin);

	//On vide le buffer si naicessaire
	if (strlen(etudiant.nom) >= MAX_LONG_NOM - 1) {
		
		do { 
        	c = getchar(); 
  		} while (c != '\n' && c != EOF);
	}

	etudiant.nom[strlen(etudiant.nom) - 1] = '\0';

	//On supprime les espaces contenu dans la saisie
	SupprimerEspace(etudiant.nom);
   
	printf(" \tPrenom : ");
	fgets(etudiant.prenom, MAX_LONG_PRENOM, stdin);

	//On vide le buffer si naicessaire
	if (strlen(etudiant.prenom) >= MAX_LONG_PRENOM - 1) {
	
		do { 
    		c = getchar(); 
		} while (c != '\n' && c != EOF);
	}

	etudiant.prenom[strlen(etudiant.prenom) - 1] = '\0';  
	//On supprime les espaces contenu dans la saisie
	SupprimerEspace(etudiant.prenom);

	//L'email de l'etudiant est generer automatiquement

	printf(" \tDate de naissance (jj/mm/aaaa): \n");
	printf("\t\tJour :");
	scanf("%d", &etudiant.dateNaissance.jour);
	printf("\t\tMois :");
	scanf("%d", &etudiant.dateNaissance.mois);
	printf("\t\tAnnee :");
	scanf("%d", &etudiant.dateNaissance.annee);
	
	while (!(etudiant.dateNaissance.jour >= 1 && etudiant.dateNaissance.jour <= 31 && etudiant.dateNaissance.mois >= 1 && etudiant.dateNaissance.mois <= 12 && etudiant.dateNaissance.annee >= 1970 && etudiant.dateNaissance.annee <=2021) || (etudiant.dateNaissance.mois == 2 && etudiant.dateNaissance.jour > 29)) {
	
		printf("Date saisie incorrecte !!!\n");
		printf(" \tDate de naissance (jj/mm/aaaa): \n");
		printf("\t\tJour :");
		scanf("%d", &etudiant.dateNaissance.jour);
		printf("\t\tMois :");
		scanf("%d", &etudiant.dateNaissance.mois);
		printf("\t\tAnnee :");
		scanf("%d", &etudiant.dateNaissance.annee);
	}
    /*****************************************************************************/
    /*****************************************************************************/
    /*****************************************************************************/
	//Si on avait pas encore choisi sa classe on redemande de choisir une classe
	//Cette conditions sera utiliser pour enregistrer plusieurs etudiants
	if (!code) {
		
		etudiant.classe = MenuListerClasse();
		reussi = EnregistrerEtudiant(etudiant, etudiant.classe);

	//Sinon on demare l'enregistrement de l'etudiant
	} else {

		reussi = EnregistrerEtudiant(etudiant, code);
	}

	if (reussi == -1) {

		printf("Ouverture fichier imposible\n");
		return -1;
		
	} else if (reussi > 1) {

		CLEAR;
		//On affiche les information sur letudiant eregistrer
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|                    Vous venez d'ajouter :                       |\n");
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		AfficherEtudiant(reussi);
		getchar();
		getchar();
		return 1;

	} else if (reussi == 0)  {

		printf("Cet etudiant existe deja !!!\n");
		getchar();
		getchar();
		return 0;
	}
}

void AjouterEtudiants (int code) {

	int nombreEtudiant = 0;
	int reussi = 0;

	printf("Entrer le nombre d'etudiant a ajouter : ");
	scanf("%d", &nombreEtudiant);
				
	for (int i = 0; i < nombreEtudiant; ++i) {

		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|                          Etudiant %2d                            |\n", i + 1);
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");

		reussi = AjouterEtudiant(code);

		if (reussi == -1) 
			break;
		else if (!reussi)
			continue;
	}
}

// Cette fonction permet d'enregister les modifications sur un etudiant

int ModifierEtudiant(Etudiant etudiant, int option) {

	// Cette variable sert a lire le fichier et recuperer ses informations
	Etudiant etudiantPresent;

	//la chaine permet de parcourir le fichier
	char chaine[MAX_CARACTERE_LIGNE];

	//On ouvre deux fichiers l'un appeler fichier obsolete pour recuperer les informations valides
	//L'autre appeler copie pour copier les informations valides et la nouvelle

	FILE *obsolete = NULL, *copie = NULL;

	// On renomme le fichier Etudiant.csv pour le supprimer apres modification
	rename("../Donnees/Etudiant.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");
	copie = fopen("../Donnees/Etudiant.csv", "a+");

	if (copie != NULL && obsolete != NULL) {
		
		//On place le curseur au debut du fichier
		fseek(obsolete, 0, SEEK_SET);

		//Grace a la chaine et fgets on vas parcourir le fichier ligne par ligne
		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			//On recupere l'information contenu sur la ligne
			fscanf(obsolete, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiantPresent.numero, etudiantPresent.nom, etudiantPresent.prenom, etudiantPresent.email, &etudiantPresent.dateNaissance.jour, &etudiantPresent.dateNaissance.mois, &etudiantPresent.dateNaissance.annee, &etudiantPresent.classe);

			//Si l'etudiant ne correspond pas on copie l'information present
			//Si l'etudiant correspond on recopie la nouvelle
			if (etudiant.numero != etudiantPresent.numero) {
				
				fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiantPresent.numero, etudiantPresent.nom, etudiantPresent.prenom, etudiantPresent.email, etudiantPresent.dateNaissance.jour, etudiantPresent.dateNaissance.mois, etudiantPresent.dateNaissance.annee, etudiantPresent.classe);
			
			} else {

				//Comme plusieur choix de modifiation sont possible
				//l'appelle de la fonction se fera avec l'option de modification
				switch (option) {
					
					//On modifie Toutes les informations
					case 1: 
						fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee, etudiant.classe);
					break;
					//On modifie le nom et le prenom
					case 2: 
						fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiantPresent.numero, etudiant.nom, etudiant.prenom, etudiantPresent.email, etudiantPresent.dateNaissance.jour, etudiantPresent.dateNaissance.mois, etudiantPresent.dateNaissance.annee, etudiantPresent.classe);
					break;
					//On modifie la date de naissance
					case 3:
						fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiantPresent.numero, etudiantPresent.nom, etudiantPresent.prenom, etudiantPresent.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee, etudiantPresent.classe);
					break;
					//On modifie la classe
					case 4:
						etudiantPresent.numero = NouveauNumero(etudiant.classe);
						fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiantPresent.numero, etudiantPresent.nom, etudiantPresent.prenom, etudiantPresent.email, etudiantPresent.dateNaissance.jour, etudiantPresent.dateNaissance.mois, etudiantPresent.dateNaissance.annee, etudiant.classe);
					break;
					//On modifie l'email
					case 5:
						// fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiantPresent.numero, etudiantPresent.nom, etudiantPresent.prenom, etudiant.email, etudiantPresent.dateNaissance.jour, etudiantPresent.dateNaissance.mois, etudiantPresent.dateNaissance.annee, etudiantPresent.classe);
					break;
				}
			}
			//Pour chaque boucle on replace le curseur 
			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
		// on affiche les modifications
		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|               Vous venez de Modifier l'etudiant %6d:               |\n", etudiant.numero);
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		AfficherEtudiant(etudiant.numero);
		getchar();
		getchar();
	}
	//On supprime les information obsolete et ferme les fichiers
	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);	
}

//Cette fonction permet de supprimer un etudiant

int SupprimerEtudiant(int numero) {

	// Cette variable permet de lire les informations contenu dans le fichier
	Etudiant etudiant;

	//la chaine permet de parcourir le fichier
	char chaine[MAX_CARACTERE_LIGNE];

	FILE *obsolete = NULL, *copie = NULL;

	rename("../Donnees/Etudiant.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");
	copie = fopen("../Donnees/Etudiant.csv", "a+");

	if (copie != NULL && obsolete != NULL) {
		
		//On positionne le curseur au debut
		fseek(obsolete, 0, SEEK_SET);

		//On parcourt le fichier
		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			//On recupere les informations contenu dans le fichier originel
			fscanf(obsolete, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
			//On copie cette informations sauf celle a supprime
			if (numero != etudiant.numero) {
				
				fprintf(copie, "\n%d;%s ;%s ;%s ;%d\\%d\\%d;%d", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee, etudiant.classe);
			}
			//On positionne le curseur pour chaque boucle
			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
		getchar();
	}
	CLEAR;
	printf("\n\t\tEtudiant '%d' supprimer !!!", numero);
	getchar();

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);

	//On regarde a present si l'etudiant avait reçu des notes on supprime ces notes
	SupprimerNoteEtudiant(numero);
}

void SupprimerNoteEtudiant (int numero) {

	FILE *obsolete = NULL, *copie = NULL;
	Note notePresent;
	char chaine[MAX_CARACTERE_LIGNE];

	rename("../Donnees/Note.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");
	copie = fopen("../Donnees/Note.csv", "a");

	if (copie != NULL && obsolete != NULL) {

		//On positionne le curseur au debut
		fseek(obsolete, 0, SEEK_SET);

		//On parcourt le fichier
		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			//on recupere l'information
			fscanf(obsolete, "%d;%d;%f;%f", &notePresent.numero,&notePresent.reference, &notePresent.noteCC, &notePresent.noteDS);
			//on copie tous sauf les mauvaise information
			if (notePresent.numero != numero) {
				
				fprintf(copie, "\n%d;%d;%f;%f", notePresent.numero,notePresent.reference, notePresent.noteCC, notePresent.noteDS);
			}
			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
	}
	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);
}

// Cette fonction permet de lister les etudiants par classe

int ListerEtudiant() {
		
	FILE *fichier_classe = NULL;
	FILE *fichier_etudiant = NULL;

	fichier_etudiant = fopen("../Donnees/Etudiant.csv", "r");
	fichier_classe = fopen("../Donnees/Classe.csv", "r");

	char chaine[MAX_CARACTERE_LIGNE];

	//Les variables classe et etudiant parmettent respectivement de recuperer
	//les informations dans les fichiers classe.csv et etudiant.csv
	Classe classe;
	Etudiant etudiant;

	if (fichier_etudiant != NULL && fichier_classe != NULL) {

		//On positionne le curseur dans le fichier classe.csv
		fseek(fichier_classe, 0, SEEK_SET);
		//On parcourt le fichier classe.csv
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_classe) != NULL) {

			//On recupere les informations on affichie la classe et pour chaque classe on affiche les etudiants
			fscanf(fichier_classe, "%d;%s ;%d", &classe.code, classe.nom, &classe.niveau);

			printf("+---------------------------------------------------------------------------------------+\n");
			printf("|%45s                                          |\n", classe.nom);
			printf("+---------------------------------------------------------------------------------------+\n");
			printf("| Numero Etudiant |    Nom    |      Prenom      |         Mail        | Date Naissance |\n");
			printf("+---------------------------------------------------------------------------------------+\n");

			//ON positionne le curseur dans le fichier etudiant
			fseek(fichier_etudiant, 0, SEEK_SET);
			//on parcourt le fichier etudiant
			while (fgets(chaine, MAX_CARACTERE_LIGNE, fichier_etudiant)) {
				
				//on recupere les informations du fichier
				fscanf(fichier_etudiant, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
				//Si le code de la classe present correspond a celui de l'etudiant on l'affiche
				if (classe.code == etudiant.classe) {
					
					printf("|%17d|%11s|%18s|%21s|    %02d\\%02d\\%4d  |\n",etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee);
					printf("+---------------------------------------------------------------------------------------+\n");
				}
				//On positionne le curseur dans le fichier etudiant
				fseek(fichier_etudiant, ftell(fichier_etudiant), SEEK_SET);
			}
			//On positionne le curseur dans le fichier classe
			fseek(fichier_classe, ftell(fichier_classe), SEEK_SET);
		}
	}
	//On ferme les fichiers
	fclose(fichier_classe);
	fclose(fichier_etudiant);
	return 1;
}
//Cette fonction permet de rechercher et de comparer des etudiants dans le ficher etudiant

int RechercheEtudiant(Etudiant etudiantRechercher) {

	FILE *fichier = NULL;
	//cette variable permrt de parcourir le fichier grace a fgets
	char chaine[MAX_CARACTERE_LIGNE];

	//CEtte variable permet de recuperer les informations sur un etudiant
	Etudiant etudiant;

	//On ouvre le fichier
	fichier = fopen("../Donnees/Etudiant.csv", "r+");

	if (fichier != NULL) {
		
		//On positionne le curseur dans le fichier
		fseek(fichier, 0, SEEK_SET);

		//On parcourt le fichier
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			//On recuperer les informations
			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			//On compare l'etudiant present dans le fichier et l'etudiant rechercher
			if (strcmp(etudiant.nom, etudiantRechercher.nom) == 0 && strcmp(etudiant.prenom, etudiantRechercher.prenom) && etudiant.dateNaissance.jour == etudiantRechercher.dateNaissance.jour && etudiant.dateNaissance.mois == etudiantRechercher.dateNaissance.mois && etudiant.dateNaissance.annee == etudiantRechercher.dateNaissance.annee) {
				
				//S'il trouve l'etudiant on quitte la fonction
				fclose(fichier);
				return 1;
			}
			//On positionne le cureur dans le fichier
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
		fclose(fichier);
		return 0;
	}
}
//Cette fonction permet de modifier tous les informations sur un etudiant
int ModifierEtudiantTous(int numero) {

	//Cette variable permet de saisir les informations sur l'etudiant
	Etudiant etudiant;
	int c = 0;
	//On redonne l'etudiant son numero
	etudiant.numero = numero;

	getchar();
	printf("\nEntrer le Nom:");
	fgets(etudiant.nom, MAX_LONG_NOM, stdin);

	if (strlen(etudiant.nom) >= MAX_LONG_NOM - 1) {
	
		do { 
    		c = getchar(); 
		} while (c != '\n' && c != EOF);
	}
	etudiant.nom[strlen(etudiant.nom) - 1] = '\0';
	//On supprime les espaces present dans la saisie
	SupprimerEspace(etudiant.nom);
	printf("Entrer le Prenom:");
	fgets(etudiant.prenom, MAX_LONG_PRENOM, stdin);

	if (strlen(etudiant.prenom) >= MAX_LONG_PRENOM - 1) {
	
		do { 
    		c = getchar(); 
		} while (c != '\n' && c != EOF);
	}
	SupprimerEspace(etudiant.prenom);
	etudiant.prenom[strlen(etudiant.prenom) - 1] = '\0';

	printf("\n\tDate de naissance (jj\\mm\\aaaa): \n");
	printf("\t\tJour :");
	scanf("%d", &etudiant.dateNaissance.jour);
	printf("\t\tMois :");
	scanf("%d", &etudiant.dateNaissance.mois);
	printf("\t\tAnnee :");
	scanf("%d", &etudiant.dateNaissance.annee);
	
	while (!(etudiant.dateNaissance.jour >= 1 && etudiant.dateNaissance.jour <= 31 && etudiant.dateNaissance.mois >= 1 && etudiant.dateNaissance.mois <= 12 && etudiant.dateNaissance.annee >= 2000 && etudiant.dateNaissance.annee <=2021) || (etudiant.dateNaissance.mois == 2 && etudiant.dateNaissance.jour > 29)) {
	
		printf("\nDate saisie incorrecte !!!\n");
		printf("\n\tDate de naissance (jj\\mm\\aaaa): \n");
		printf("\t\tJour :");
		scanf("%d", &etudiant.dateNaissance.jour);
		printf("\t\tMois :");
		scanf("%d", &etudiant.dateNaissance.mois);
		printf("\t\tAnnee :");
		scanf("%d", &etudiant.dateNaissance.annee);
	}
	etudiant.classe = numero/1000;
	MailGenerateur(etudiant, etudiant.email);

	ModifierEtudiant(etudiant, 1);
	return 1;
}
// Cette fonction permet de modifier le nom et le prenom de l'etudiant

int ModifierNomPrenom(int numero) {

	Etudiant etudiant;
	int c = 0;
	
	etudiant.numero = numero;

	getchar();

	printf("\n\tEntrer le Nom:");
	fgets(etudiant.nom, MAX_LONG_NOM, stdin);
	etudiant.nom[strlen(etudiant.nom) - 1] = '\0';
	SupprimerEspace(etudiant.nom);

	if (strlen(etudiant.nom) >= MAX_LONG_NOM - 1) {
	
		do { 
    		c = getchar(); 
		} while (c != '\n' && c != EOF);
	}
	printf("\tEntrer le Prenom:");
	fgets(etudiant.prenom, MAX_LONG_PRENOM, stdin);
	etudiant.prenom[strlen(etudiant.prenom) - 1] = '\0';
	SupprimerEspace(etudiant.prenom);

	if (strlen(etudiant.prenom) >= MAX_LONG_PRENOM - 1) {
	
		do { 
    		c = getchar(); 
		} while (c != '\n' && c != EOF);
	}
	ModifierEtudiant(etudiant, 2);
	return 0;
}
// Cette fonction permet de modifier la date de naissance

int ModifierDateNaissance(int numero) {

	Etudiant etudiant;

	etudiant.numero = numero;

	printf("\n\tDate de naissance (jj\\mm\\aaaa): \n");
	printf("\t\tJour :");
	scanf("%d", &etudiant.dateNaissance.jour);
	printf("\t\tMois :");
	scanf("%d", &etudiant.dateNaissance.mois);
	printf("\t\tAnnee :");
	scanf("%d", &etudiant.dateNaissance.annee);
	
	while (!(etudiant.dateNaissance.jour >= 1 && etudiant.dateNaissance.jour <= 31 && etudiant.dateNaissance.mois >= 1 && etudiant.dateNaissance.mois <= 12 && etudiant.dateNaissance.annee >= 1970 && etudiant.dateNaissance.annee <=2021) || (etudiant.dateNaissance.mois == 2 && etudiant.dateNaissance.jour > 29)) {
	
		printf("\nDate saisie incorrecte !!!\n");
		printf("\n\tDate de naissance (jj\\mm\\aaaa): \n");
		printf("\t\tJour :");
		scanf("%d", &etudiant.dateNaissance.jour);
		printf("\t\tMois :");
		scanf("%d", &etudiant.dateNaissance.mois);
		printf("\t\tAnnee :");
		scanf("%d", &etudiant.dateNaissance.annee);
	}

	ModifierEtudiant(etudiant, 3);
	return 0;
}

//Cette fonction permet de modifier la classe de l'etudiant

int ModifierClasseEtudiant(int numero) {

	Etudiant etudiant;
	int tableauReference[MAX_MATIERE];
	int nombreMatiere = 0;
	Note note;

	etudiant.numero = numero;

	etudiant.classe = MenuListerClasse();

	if (etudiant.classe != 0) {

		//Si l'etudiant change de classe on supprime ces notes

		SupprimerNoteEtudiant(numero);
		//et si la classe avez recu des notes on lui donne zero

		nombreMatiere = EstNoters(etudiant.classe, tableauReference);

		note.numero = numero;
		for(int i = 0; i < nombreMatiere; i++) {

			note.reference = tableauReference[i];
			note.noteCC = 0;
			note.noteDS = 0;
			NoterEtudiant(note);
		}

		ModifierEtudiant(etudiant, 4);
	}
	return 0;
}

// int ModifierEmail(int numero) {

// 	Etudiant etudiant;
// 	int c = 0;

// 	getchar();

// 	etudiant.numero = numero;

// 	printf("\n\tEntrer le nouveau mail:");
// 	fgets(etudiant.email, MAX_LONG_MAIL, stdin);
// 	etudiant.email[strlen(etudiant.email) - 1] = '\0';
// 	SupprimerEspace(etudiant.email);

// 	if (strlen(etudiant.email) >= MAX_LONG_MAIL - 1) {
	
// 		do { 
//     		c = getchar(); 
// 		} while (c != '\n' && c != EOF);
// 	}
// 	ModifierEtudiant(etudiant, 5);
// 	return 0;
// }

void MailGenerateur(Etudiant etudiant, char *mail) {

	FILE *fichier = NULL;
	char domaine[20] = {'\0'};
	char chaine[7] = {'\0'};
	int n = 100000;
	int nb = 0;


	fichier = fopen("domaine.txt", "r");

	if (fichier != NULL) {
		fscanf(fichier, "%d;%s", &nb, domaine);

		for (int i = 0; i < 6; ++i) {
			
			chaine[i] = etudiant.numero/n + 48;
			etudiant.numero = etudiant.numero - (etudiant.numero/n) * n;
			n = n/10;
		}
		strcat(mail, etudiant.nom);
		strcat(mail, chaine);
		strcat(mail, domaine);
	}

	fclose(fichier);
}

void AfficherEtudiant(int numero) {

	FILE *fichier_etudiant = NULL;
	FILE *fichier_classe = NULL;

	Etudiant etudiant;
	Classe classe;

	char chaine[MAX_CARACTERE_LIGNE];

	fichier_classe = fopen("../Donnees/Classe.csv", "r");
	fichier_etudiant = fopen("../Donnees/Etudiant.csv", "r");

	if (fichier_etudiant != NULL && fichier_classe != NULL) {
		
		fseek(fichier_etudiant, 0, SEEK_SET);

		while (fgets(chaine, MAX_CARACTERE_LIGNE, fichier_etudiant) != NULL) {

			fscanf(fichier_etudiant, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (numero == etudiant.numero) {

				fseek(fichier_classe, 0, SEEK_SET);

				while (fgets(chaine, MAX_CARACTERE_LIGNE, fichier_classe) != NULL) {

					fscanf(fichier_classe, "%d;%s ;%d", &classe.code, classe.nom, &classe.niveau);

					if (etudiant.classe == classe.code) {
						
						printf("+---------------------------------------------------------------------------------------+\n");
						printf("|%45s                                          |\n", classe.nom);
						printf("+---------------------------------------------------------------------------------------+\n");
						printf("| Numero Etudiant |    Nom    |      Prenom      |         Mail        | Date Naissance |\n");
						printf("+---------------------------------------------------------------------------------------+\n");

						break;
					}
					fseek(fichier_classe, ftell(fichier_classe), SEEK_SET);
				}
				printf("|%17d|%11s|%18s|%21s|    %02d\\%02d\\%4d  |\n",etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance.jour, etudiant.dateNaissance.mois, etudiant.dateNaissance.annee);
				printf("+---------------------------------------------------------------------------------------+\n");
				break;
			}
		fseek(fichier_etudiant, ftell(fichier_etudiant), SEEK_SET);
		}
	}
	fclose(fichier_classe);
	fclose(fichier_etudiant);
}

void Appreciation(float moyenne, char *appreciation) {

	if (moyenne < 10) {
		
		strcpy(appreciation, "Insuffisant");
	} else if (moyenne < 12) {

		strcpy(appreciation, "Passable");
	} else if (moyenne < 15) {

		strcpy(appreciation, "Assez Bien");
	} else if (moyenne < 18) {

		strcpy(appreciation, "Bien");
	} else if (moyenne < 20) {

		strcpy(appreciation, "Tres Bien");
	} else {

		strcpy(appreciation, "Exellent");
	}
}