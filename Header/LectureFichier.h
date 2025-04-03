// int RechercheDansFichier(const char *nomFichier, int valeurChercher);
// int RechercheDansFichierChaine(const char *nomFichier, char *chaine);
// int RechercheDansFichierCombo(const char *nomFichier, char *chaine, int valeurChercher);

int RechercheDansFichier(const char *nomFichier, int valeurChercher) {

	FILE *fichier = NULL;
	char chaine[MAX_CARACTERE_LIGNE];
	int valeurDansFichier = 0;

	fichier = fopen(nomFichier, "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fseek(fichier, ftell(fichier), SEEK_SET);
			fscanf(fichier, "%d;", &valeurDansFichier);

			if (valeurChercher == valeurDansFichier) {
				
				fclose(fichier);
				return 1;
			}
		}
		fclose(fichier);
		return 0;
	}

}

int RechercheDansFichierChaine(const char *nomFichier, char *chaine) {

	FILE *fichier = NULL;
	char chaineLu[MAX_CARACTERE_LIGNE];

	int trouver = 0;
	int ref = 0;

	Etudiant etudiant;

	fichier = fopen(nomFichier, "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaineLu, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d\\;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (strcmp(chaine, etudiant.nom) == 0 && ref != etudiant.numero) {
				
				ref = etudiant.numero;
				AfficherEtudiant(etudiant.numero);
				trouver = 1;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
		if (!trouver) {

			printf("\n\tAucun etudiant pourtant ce nom trouver !!!\n");
			getchar();
			CLEAR;
		
		} else {

			getchar();
			CLEAR;
		}
	}
	fclose(fichier);
	return trouver;
}

int RechercheDansFichierCombo(const char *nomFichier, char *chaine, int valeurChercher) {


	FILE *fichier = NULL;
	char chaineLu[MAX_CARACTERE_LIGNE];

	int trouver = 0;

	Etudiant etudiant;

	fichier = fopen(nomFichier, "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaineLu, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (strcmp(chaine, etudiant.nom) == 0 && etudiant.classe == valeurChercher) {
				
				AfficherEtudiant(etudiant.numero);
				trouver = 1;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
		if (!trouver) {
			
			printf("\n\tAucun etudiant pourtant ce nom trouver !!!\n");
			getchar();
			getchar();
			CLEAR;
		
		} else {

			getchar();
			getchar();
			CLEAR;
		}
	}
	fclose(fichier);
	return trouver;
}

int RechercheNumeroEtudiant (int code, int *TableauNumero) {

	FILE *fichier = NULL;

	char chaine[MAX_CARACTERE_LIGNE];
	Etudiant etudiant;
	
	int nombreEtudiant = 0;

	fichier = fopen("../Donnees/Etudiant.csv", "r");

	if (fichier != NULL) {
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (code == etudiant.classe) {
				
				*(TableauNumero + nombreEtudiant) = etudiant.numero;
				nombreEtudiant ++;
			}

			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}

	fclose (fichier);
	return nombreEtudiant;
}