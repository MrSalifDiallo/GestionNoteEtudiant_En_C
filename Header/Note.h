//Cette fonction permet de donner une note a une classe dans une matiere

int AjouterNotePourClasse(int code){

	char chaine[MAX_CARACTERE_LIGNE];

	FILE *fichier_etudiant = NULL;

	Note note;
	Etudiant etudiant;
	MatiereClasse association;
	NOTER dejaNoter;

	int nombreEtudiant = 0;

	//On affiche le menu pour choisir la matiere
	note.reference = MenuChoixMatiere(code);

	//La variable association permet de retrouver la classe et la matiere
	association.code = code;
	association.reference = note.reference;
	
	//dejaNoter permet de savoir si la classe a deja recu une note
	dejaNoter = EstNoter(code, note.reference);

	//si la classe n'a pas recu de note on commence l'enregistrement des notes
	if (note.reference != 0 && dejaNoter == non) {
		
		fichier_etudiant = fopen("../Donnees/Etudiant.csv", "r+");

		if (fichier_etudiant != NULL) {
			
			CLEAR;
			fseek(fichier_etudiant, 0, SEEK_SET);

			//On parcourt le fichier etudiant pour afficher les etudiants
			while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_etudiant) != NULL) {

				//On recupere l'etudiant
				fscanf(fichier_etudiant, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
				
				//Si l'etudiant appartien a la classe on l'affiche et on demande ses notes
				if (code == etudiant.classe) {
					
					SupprimerEspace(etudiant.prenom);
					printf("%d %s %s :\n", etudiant.numero, etudiant.prenom, etudiant.nom);
					printf("\tNote Control Continue : ");
					scanf("%f", &note.noteCC);

					while (note.noteCC > 20 || note.noteCC < 0){
			
						printf("Une note ne peut pas etre >20 ou <0 !!!\n");
						printf("\tNoteCC : ");
						scanf("%f", &note.noteCC);
					}

					printf("\tNote Devoir Surveille : ");
					scanf("%f", &note.noteDS);
					
					while(note.noteDS > 20 ||note.noteDS < 0) {

						printf("Une note ne peut pas etre >20 ou <0 !!!\n");
						printf("\tNoteCC : ");
						scanf("%f", &note.noteDS);
					}

					note.numero = etudiant.numero;

					//On donne la note a la fonction NoterEtudiant qui met la note dans le fichier note.csv
					NoterEtudiant(note);
					nombreEtudiant ++;
				}
				//ON replace le curseur
				fseek(fichier_etudiant, ftell(fichier_etudiant), SEEK_SET);
			}
		}
		fclose(fichier_etudiant);

		// si la classe n'a pas d'etudiant on afficher ceci
		if (nombreEtudiant == 0) {

			CLEAR;

			printf("\n\t+-------------------------------------------+\n");
			printf("\t|       cette classe n'a pas etudiant       |\n");
			printf("\t+-------------------------------------------+\n");
			getchar();
			getchar();
		} else {//si la classe a recu les notes on precies dans le fichier matiere-classe que la classe a eu
			//une note dans cette matiere

			NoterClasse(association, oui);

			CLEAR;
			printf("\n\t+-------------------------------------------+\n");
			printf("\t|             Notes enregistrer             |\n");
			printf("\t+-------------------------------------------+\n");
			getchar();
			getchar();
		}
		return 1;
	
	} else if (dejaNoter == oui) {
		
		CLEAR;

		printf("\n\t+-----------------------------------------------------------+\n");
		printf("\t|      cette classe a deja etais noter dans cette matiere     |\n");
		printf("\t+-------------------------------------------------------------+\n");
		getchar();
		getchar();
	}
}
//Cette fonction permet de noter un etudiant
//elle ajoute les notes recue en parametre dans le fichier note.csv
void NoterEtudiant(Note note) {

	FILE *fichier = NULL;
	
	char chaine[MAX_CARACTERE_LIGNE];

	fichier = fopen("../Donnees/Note.csv", "a");

	if (fichier != NULL) {
		
		fprintf(fichier, "\n%d;%d;%g;%g", note.numero, note.reference, note.noteCC, note.noteDS);
	}

	fclose(fichier);
}

//Cette fonction permet de modifier les notes d'un etudiant
// elle reçoit le numero de l'etudiant et la reference de la matiere
int ModifierNote(Note note){

	Note noteModifier;
	Note notePresent;

	char chaine[MAX_CARACTERE_LIGNE];
	FILE *obsolete = NULL, *copie = NULL;

//ON renomme le fichier a supprimer
	rename("../Donnees/Note.csv", "../Donnees/fichierObsolete.csv");
// on cree une fichier copie
	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");
	copie = fopen("../Donnees/Note.csv", "a+");


	if (copie != NULL && obsolete != NULL) {
		// on demande l'utilisateur de saisir les informations

		printf("\tNote Controle continue : ");
		scanf("%f", &noteModifier.noteCC);

		while (noteModifier.noteCC > 20 || noteModifier.noteCC < 0){
			
			printf("Une note ne peut pas etre >20 ou <0 !!!\n");
			printf("\tNoteCC : ");
			scanf("%f", &noteModifier.noteCC);
		}

		printf("\tNote Devoir Surveille : ");
		scanf("%f", &noteModifier.noteDS);
		
		while(noteModifier.noteDS > 20 ||noteModifier.noteDS < 0) {

			printf("Une note ne peut pas etre >20 ou <0 !!!\n");
			printf("\tNoteCC : ");
			scanf("%f", &noteModifier.noteDS);
		}

		fseek(obsolete, 0, SEEK_SET);

		//on commence la modification des notes
		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {
			//on recupere les informations sur le fichier
			fscanf(obsolete, "%d;%d;%f;%f", &notePresent.numero,&notePresent.reference, &notePresent.noteCC, &notePresent.noteDS);
			//on compare le numero etudiant et le reference de la matiere
			//si le numero et la reference correspende on modifie sinon on copie la ligne 
			if (note.numero == notePresent.numero && note.reference == notePresent.reference) {
				
				fprintf(copie, "\n%d;%d;%f;%f", note.numero, note.reference, noteModifier.noteCC, noteModifier.noteDS);
			
			} else {

				fprintf(copie, "\n%d;%d;%f;%f", notePresent.numero,notePresent.reference, notePresent.noteCC, notePresent.noteDS);
			}

			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
		getchar();
	} else {

		printf("erreur !!!");
		getchar();
		getchar();
		fclose(copie);
		fclose(obsolete);
		remove("../Donnees/Note.csv");
		rename("../Donnees/fichierObsolete.csv", "../Donnees/Note.csv");
		return 0;
	}

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);
	return 1;
}
	
//Cette fonction permet de modifier tous les notes d'un etudiant dans tous les matieres

void ModifierNotes() {

	int code = 0;
	int nombreDeMatiere = 0;
	int tableauReference[MAX_MATIERE] = {0};
	Note note;
	Matiere matiere;
	FILE *fichier = NULL;

	char chaine[MAX_CARACTERE_LIGNE];

	fichier = fopen("../Donnees/Matiere.csv", "r");

	code = MenuListerClasse();
	if (code != 0 && fichier != NULL) {
	
	 	note.numero = MenuChoixEtudiant(code);
		if (note.numero != 0) {

			nombreDeMatiere = EstNoters(code, tableauReference);
			if (nombreDeMatiere != 0) {

				for(int i = 0; i < nombreDeMatiere; i ++) {

					CLEAR;
					note.reference = tableauReference[i];
					fseek(fichier, 0, SEEK_SET);
					while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL){

						fscanf(fichier, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);
						if (note.reference == matiere.reference) {

							printf("%s\n", matiere.libelle);
							break;
						}
						fseek(fichier, ftell(fichier), SEEK_SET);
					}
					ModifierNote(note);
				}
				fclose(fichier);
			} else {

				CLEAR;
				printf("+--------------------------------------------------------------------+\n");
				printf("|L'etudiant ne peut pas etre noter si la classe n'a recue aucune note|\n");
				printf("+--------------------------------------------------------------------+\n");
				getchar();
				getchar();
			}
		}
	}
}

//Cette fonction supprime les notes de toute une classe
// elle recoit le code de la classe et la reference de la matiere
// elle recherche les etudiants de la classe et supprime leur note
int SupprimerNote(MatiereClasse association){

	Note notePresent;

	char chaine[MAX_CARACTERE_LIGNE];
	FILE *obsolete = NULL, *copie = NULL;

	rename("../Donnees/Note.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r+");
	copie = fopen("../Donnees/Note.csv", "a");

	if (copie != NULL && obsolete != NULL && association.estNoter == oui) {

		fseek(obsolete, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			fscanf(obsolete, "%d;%d;%f;%f", &notePresent.numero,&notePresent.reference, &notePresent.noteCC, &notePresent.noteDS);

			if (!(association.reference == notePresent.reference && notePresent.numero/1000 == association.code)) {
				
				fprintf(copie, "\n%d;%d;%f;%f", notePresent.numero,notePresent.reference, notePresent.noteCC, notePresent.noteDS);
			}
			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
	}

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);

	NoterClasse(association, non);

	return 1;
}

//cette fonction liste les notes de tous les etudiants d'une classe dans une matiere

int ListerNote() {

	FILE *fichier_note = NULL;
	FILE *fichier_etudiant = NULL;

	char chaine[MAX_CARACTERE_LIGNE];

	fichier_etudiant = fopen("../Donnees/Etudiant.csv", "r");
	fichier_note = fopen("../Donnees/Note.csv", "r");

	Note note;
	Etudiant etudiant;

	int code = 0;
	int reference = 0;
	float moyenne = 0;
	code = MenuListerClasse();
	reference = MenuChoixMatiere(code);

	printf("+--------+-------------------------+---------+---------+---------+\n");
	printf("| Numero |       Nom complet       | note CC | note DS | moyenne |\n");

	if (code != 0 && reference != 0) {
		if (fichier_note != NULL && fichier_etudiant != NULL) {
		
			fseek(fichier_etudiant, 0, SEEK_SET);

			while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_etudiant) != NULL) {

				fscanf(fichier_etudiant, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
				if (code == etudiant.classe) {
					
					fseek(fichier_note, 0, SEEK_SET);

					while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_note) != NULL) {

						fscanf(fichier_note, "%d;%d;%f;%f", &note.numero, &note.reference, &note.noteCC, &note.noteDS);
						if (note.numero == etudiant.numero && note.reference == reference) {
							
							moyenne = MoyenneMatiere(etudiant.numero, reference);
							printf("|--------|-------------------------|---------|---------|---------|\n");
							printf("| %6d |  %14s %6s  | %2.4f | %2.4f | %2.4f |\n", etudiant.numero, etudiant.prenom, etudiant.nom, note.noteCC, note.noteDS, moyenne);
						}
					}
					fseek(fichier_note, ftell(fichier_note), SEEK_SET);
				}
				fseek(fichier_etudiant, ftell(fichier_etudiant), SEEK_SET);
			}
		}
		printf("+--------+-------------------------+---------+---------+---------+\n");
		getchar();
		getchar();

		fclose(fichier_note);
		fclose(fichier_etudiant);
		return 1;
	}
	return 0;
}

// cette fonction permet de dire si une classe a deja recue une note
// elle recoit le le code et la reference pour ajouter oui ou non dans le fichier classe matiere
// si laa classe recoit une note elle met oui si on suppime les notes elle met non 
int NoterClasse(MatiereClasse association, NOTER estNoter) {

	char chaine[MAX_CARACTERE_LIGNE];
	FILE *obsolete = NULL, *copie = NULL;

	rename("../Donnees/MatiereClasse.csv", "../Donnees/fichierObsolete.csv");

	obsolete = fopen ("../Donnees/fichierObsolete.csv", "r");
	copie = fopen("../Donnees/MatiereClasse.csv", "a");

	MatiereClasse associationPresent;

	if (copie != NULL && obsolete != NULL) {

		fseek(obsolete, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, obsolete) != NULL) {

			fscanf(obsolete, "%d;%d;%d", &associationPresent.code,&associationPresent.reference, &associationPresent.estNoter);

			if (!(association.reference == associationPresent.reference && association.code == associationPresent.code)) {
				
				fprintf(copie, "\n%d;%d;%d", associationPresent.code,associationPresent.reference, associationPresent.estNoter);
			} else {

				associationPresent.estNoter = estNoter;
				fprintf(copie, "\n%d;%d;%d", associationPresent.code,associationPresent.reference, associationPresent.estNoter);
			}

			fseek(obsolete, ftell(obsolete), SEEK_SET);
		}
		getchar();
	} else {

		printf("erreur !!!");
		getchar();
		getchar();
	}

	fclose(obsolete);
	remove("../Donnees/fichierObsolete.csv");
	fclose(copie);
}

//cette fonction permet de verifier si une classe a deja recu une note
NOTER EstNoter(int code, int reference) {

	char chaine[MAX_CARACTERE_LIGNE];
	FILE *fichier = NULL;

	MatiereClasse associationPresent;

	fichier = fopen ("../Donnees/MatiereClasse.csv", "r+");

	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%d;%d", &associationPresent.code,&associationPresent.reference, &associationPresent.estNoter);

			if (associationPresent.code == code && associationPresent.reference == reference) {
				
				fclose(fichier);
				return associationPresent.estNoter;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);
	return note_erreur;
}

// cette fonction permet de recuperer la liste des matieres dans lesquelles une classe a recu des notes
int EstNoters(int code, int *tableauReference) {

	char chaine[MAX_CARACTERE_LIGNE];
	FILE *fichier = NULL, *copie = NULL;

	int nombreDeNote =0;

	MatiereClasse associationPresent;

	fichier = fopen ("../Donnees/MatiereClasse.csv", "r+");


	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);

		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%d;%d", &associationPresent.code,&associationPresent.reference, &associationPresent.estNoter);

			if (associationPresent.code == code && associationPresent.estNoter == oui) {
				
				*(tableauReference + nombreDeNote) = associationPresent.reference;
				nombreDeNote ++;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);
	return nombreDeNote;
}

//cette fonction calcul la moyenne total d'un etudiant
// elle recupere toute les matieres dans lesquelle l'etudiant a recu une note puis
//calcul la moynne

float MoyenneFinale (int numero, int code) {

	FILE *fichier = NULL;
	Matiere matiere;

	char chaine[MAX_CARACTERE_LIGNE];
	float moyenne = 0;
	int nombreMatiere = 0;
	int tableauReference[MAX_MATIERE] = {0};
	int sommeCoefficient = 0;

	//ON RECUPERE LE COEFFICIENT DE LA MATIERE
	nombreMatiere = EstNoters(code, tableauReference);

	fichier = fopen("../Donnees/Matiere.csv", "r");

	if (fichier != NULL && nombreMatiere != 0) {
		
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);
			for (int i = 0; i < nombreMatiere; i++) {

				if (matiere.reference == tableauReference[i]) {
					
					moyenne = moyenne + MoyenneMatiere(numero, tableauReference[i]) * matiere.coefficient;
					sommeCoefficient = sommeCoefficient + matiere.coefficient;
				}
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
		moyenne = moyenne / sommeCoefficient;
	}
	fclose (fichier);

	return moyenne;
}

//cette fonction calcule la moyenne d'un etudiant dans une maiere

float MoyenneMatiere (int numero, int reference) {

	FILE *fichier = NULL;
	
	Note note;
	note.noteCC =0;
	note.noteDS =0;

	char chaine[MAX_CARACTERE_LIGNE];
	float moyenne = 0;

	//ON CALCULE LA MOYENNE

	fichier = fopen("../Donnees/Note.csv", "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%d;%f;%f", &note.numero, &note.reference, &note.noteCC, &note.noteDS);
			if (note.reference == reference && note.numero == numero) {
				
				moyenne = (note.noteCC + note.noteDS * 2) / 3;
				break;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose (fichier);

	return moyenne;
}

// cette fonction calcule le rang d'un etudiant dans une matiere
int RangMatiere(int numero, int reference) {

	int rang = 1;
	float moyenneEtudiant = 0;
	char chaine[MAX_CARACTERE_LIGNE];
	Etudiant etudiant;

	moyenneEtudiant = MoyenneMatiere(numero, reference);

	FILE *fichier = fopen("../Donnees/Etudiant.csv", "r");

	if (fichier != NULL) {
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
			if (etudiant.classe == numero/1000 && etudiant.numero != numero) {

					if (moyenneEtudiant < MoyenneMatiere(etudiant.numero, reference))						
						rang ++;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	return rang;
}

// cette fonction calcul le rang general d'un etudiant
int Rang (int numero, int code) {

	int rang = 1;
	float moyenneEtudiant = 0;
	char chaine[MAX_CARACTERE_LIGNE];

	moyenneEtudiant = MoyenneFinale(numero, code);

	FILE *fichier = NULL;
	Etudiant etudiant;

	fichier = fopen("../Donnees/Etudiant.csv", "r");

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);
			if (etudiant.classe == code && etudiant.numero != numero) {

					if (moyenneEtudiant < MoyenneFinale(etudiant.numero, etudiant.classe))						
						rang ++;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);
	return rang;
}
// cette fonction construit le bulletin d'un etudiant
void Bulletin (int numero) {

	FILE *fichier = NULL;
	char appreciation[100] = {'\0'};
	int code = 0;

	CLEAR;
	printf("+---------------------------------------------------------------------+\n");
	printf("|                                                                     |\n");
	printf("|                          Bulletin de Notes                          |\n");
	printf("|                                                                     |\n");
	printf("|---------------------------------------------------------------------|\n");
	printf("|---------------------------------------------------------------------|\n");

	fichier = fopen("../Donnees/Etudiant.csv", "r");

	Etudiant etudiant;
	Etudiant etudiantLu;

	int nombreEtudiant = 0;
	char chaine[MAX_CARACTERE_LIGNE];

	if (fichier != NULL) {
		
		code = numero/1000;
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiantLu.numero, etudiantLu.nom, etudiantLu.prenom, etudiantLu.email, &etudiantLu.dateNaissance.jour, &etudiantLu.dateNaissance.mois, &etudiantLu.dateNaissance.annee, &etudiantLu.classe);
		
			if (etudiantLu.numero == numero) {

				strcpy(etudiant.nom, etudiantLu.nom);
				strcpy(etudiant.prenom, etudiantLu.prenom);
				strcpy(etudiant.email, etudiantLu.email);
				etudiant.dateNaissance.jour = etudiantLu.dateNaissance.jour;
				etudiant.dateNaissance.mois = etudiantLu.dateNaissance.mois;
				etudiant.dateNaissance.annee = etudiantLu.dateNaissance.annee;
				etudiant.numero = etudiantLu.numero;
				RemettreEspace(etudiant.prenom);
				printf("|        Prenoms : %20s   Nom : %10s            |\n", etudiant.prenom, etudiant.nom);
			}
		
			if (etudiantLu.classe == code)
				nombreEtudiant ++;

			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);

	fichier = fopen("../Donnees/Classe.csv", "r");
	Classe classe;

	if (fichier != NULL) {
		
		fseek(fichier, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s %d", &classe.code, classe.nom, &classe.niveau);
			if (classe.code == code) {
				
				printf("|        Date de naissance : %2d/%2d/%4d  Classe : %10s          |\n",etudiant.dateNaissance.jour ,etudiant.dateNaissance.mois ,etudiant.dateNaissance.annee, classe.nom);
				break;
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}
	fclose(fichier);

	printf("|        Mail : %20s                                  |\n", etudiant.email);
	printf("|        Numero etudiant : %6d  Nombre d'eleves : %d                |\n", etudiant.numero, nombreEtudiant);


	printf("|---------------------------------------------------------------------|\n");
	printf("|-----------+--------+--------+------+---------+------+---------------|\n");
	printf("|  Matiere  | NoteCC | NoteDS | Coef | Moyenne | Rang | Appreciations |\n");

	FILE *fichier_matiere = NULL;
	FILE *fichier_Note = NULL;
	FILE *fichier_MatiereClasse = NULL;

	fichier_matiere = fopen("../Donnees/Matiere.csv", "r");
	fichier_Note = fopen("../Donnees/Note.csv", "r");
	fichier_MatiereClasse = fopen("../Donnees/MatiereClasse.csv", "r");

	float moyenne = 0;
	int rang = 0;

	Matiere matiere;
	MatiereClasse association;
	Note note;

	if (fichier_matiere != NULL && fichier_Note != NULL && fichier_MatiereClasse != NULL) {
	
		fseek(fichier_MatiereClasse, 0, SEEK_SET);
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_MatiereClasse) != NULL) {

			fscanf(fichier_MatiereClasse, "%d;%d;%d", &association.code, &association.reference, &association.estNoter);
			if (association.code == code) {
				
				fseek(fichier_matiere, 0, SEEK_SET);
				while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_matiere) != NULL) {

					fscanf(fichier_matiere, "%d;%s ;%d", &matiere.reference, matiere.libelle, &matiere.coefficient);
					if (matiere.reference == association.reference) {
						
						if (association.estNoter == oui) {

							moyenne = MoyenneMatiere(numero, matiere.reference);
							Appreciation(moyenne, appreciation);
							rang = RangMatiere(numero, matiere.reference);
							fseek(fichier_Note, 0, SEEK_SET);
							while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier_Note) != NULL) {

								fscanf(fichier_Note, "%d;%d;%f;%f", &note.numero, &note.reference, &note.noteCC, &note.noteDS);
								if (matiere.reference == note.reference && etudiant.numero == note.numero){
									
									printf("|-----------|--------|--------|------|---------|------|---------------|\n");
									printf("|%11s|%8g|%8g|%6d|%9g|%6d|%15s|\n", matiere.libelle,note.noteCC, note.noteDS, matiere.coefficient, moyenne, rang, appreciation);
									break;
								}
								fseek(fichier_Note, ftell(fichier_Note), SEEK_SET);
							}
						} else {

							moyenne = 0;
							note.noteCC = 0;
							note.noteDS = 0;
							rang = 1;
									printf("|-----------|--------|--------|------|---------|------|---------------|\n");
									printf("|%11s|%8g|%8g|%6d|%9g|%6d|%15s|\n", matiere.libelle,note.noteCC, note.noteDS, matiere.coefficient, moyenne, rang, appreciation);
						}
						break;
					}
					fseek(fichier_matiere, ftell(fichier_matiere), SEEK_SET);
				}
			}
			fseek(fichier_MatiereClasse, ftell(fichier_MatiereClasse), SEEK_SET);
		}		
	}
	moyenne = MoyenneFinale(numero, code);
	Appreciation(moyenne, appreciation);
	rang = Rang(numero, code);
	printf("|-----------+--------+--------+------+---------+------+---------------|\n");
	printf("|--------------------+---------------+----------------+---------------|\n");
	printf("|  Moyenne Generale  : %7g       | Rang : %7d | %13s |\n", moyenne, rang, appreciation);
	printf("+--------------------+---------------+----------------+---------------+\n");
	fclose(fichier_Note);
	fclose(fichier_matiere);
	fclose(fichier_MatiereClasse);
	getchar();
	getchar();
	CLEAR;
}