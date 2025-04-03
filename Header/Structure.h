//Cette variable permet d'effacer le menu precedant avec cls sur windows et clean sur un autre os
#ifdef _WIN32

	#define CLEAR system("cls")
	#define P system("pause")
	#define CLS system("cls")
	#define NB system("Color 01")
	#define NR system("COLOR 04")
	#define NE system("Color 0E")
	#define NJ system("color 06")
	#define BV system("92")
#else

	#define CLEAR system("clear")
	#define P system("pause")
	#define CLS system("cls")
	#define NB system("Color 01")
	#define NR system("COLOR 04")
	#define NO system("Color 0F")
	#define NE system("Color 0E")
	#define NJ system("color 06")
	#define BV system("92")

#endif
//***************************************************//
//													 //
//					STRUCTURE MATIERE				 //
//													 //
//***************************************************//

#define MAX_LONG_LIBELLE 15
#define MAX_MATIERE 15

typedef struct {

	int reference;
	char libelle[MAX_LONG_LIBELLE];
	short int coefficient;

} Matiere;

// Cette fonction permet de creer automatiquement un nouveau Reference matiere
//elle li un fichier qui contient le dernier reference et l'increment
int NouveauReferenceMatiere () {

	FILE *fichier = NULL;

	int reference = 0;

	fichier = fopen("../Donnees/Reference.txt", "a+");

	if (fichier != NULL) {

		fscanf(fichier,"%d", &reference);
		reference ++;
	}
	fclose(fichier);
	remove("../Donnees/Reference.txt");

	fichier = fopen("../Donnees/Reference.txt", "a+");

	if (fichier != NULL) {
		
		fprintf(fichier,"%d", reference);
	}

	fclose(fichier);
	return reference;
}

//***************************************************//
//													 //
//					STRUCTURE CLASSE				 //
//													 //
//***************************************************//

#define MAX_LONG_NOM 30
#define MAX_ETUDIANT 100

typedef enum {
	vid,
	Licence,
	Master

} Niveau;

typedef struct {

	int code;
	char nom[MAX_LONG_NOM];
	Niveau niveau;

} Classe;
// Cette fonction permet de creer automatiquement un nouveau Code d'une  classe
//elle li une fichier qui contient les derniers codes des licences et des masters
//Une classe licence a un code commencent par 1 et les masters commence par 2
//un code est composer de 3 chiffres
int NouveauCode (int niveau) {

	FILE *fichier = NULL;
	FILE *fichier_Numero = NULL;

	int code1 = 0;
	int code2 = 0;
	int nouveauNumero = 0;

	fichier = fopen("../Donnees/code.txt", "a+");
	fichier_Numero = fopen("../Donnees/Numero.txt", "a");

	if (fichier != NULL) {

		fscanf(fichier,"%d;%d", &code1, &code2);
	}

	fclose(fichier);
	remove("../Donnees/code.txt");

	fichier = fopen("../Donnees/code.txt", "a+");

	if (fichier != NULL & fichier_Numero != NULL) {
		
		if (niveau == 1) {

			code1++;
			nouveauNumero = code1 * 1000;
			fprintf(fichier,"%d;%d", code1, code2);
			fprintf(fichier_Numero, "\n%d", nouveauNumero);
			fclose(fichier);
			fclose(fichier_Numero);
			return code1;
		
		} else{

			code2++;
			nouveauNumero = code2 * 1000;
			fprintf(fichier,"%d;%d", code1, code2);
			fprintf(fichier_Numero, "\n%d", nouveauNumero);
			fclose(fichier);
			fclose(fichier_Numero);
			return code2;
		}

	} else 
		return 0;
}

//***************************************************//
//													 //
//					STRUCTURE ETUDIANT				 //
//													 //
//***************************************************//

#define MAX_LONG_NOM 30
#define MAX_LONG_PRENOM 20
#define MAX_LONG_MAIL 20
#define MAX_CARACTERE_LIGNE 100
#define MAX_NUM 10

typedef struct {

	int jour;
	int mois;
	int annee;

} Date;

typedef struct {

	int numero;
	char nom[MAX_LONG_NOM];
	char prenom[MAX_LONG_PRENOM];
	char email[MAX_LONG_MAIL];
	int classe;
	Date dateNaissance;

} Etudiant;

// Cette fonction permet de creer automatiquement un nouveau numero etudiant
// le numero etudiant est composer du code de la classe et une suite de 3 chiffes
// elle li une fichier qui contient lesderniers numero etudiant de tout les classes puis
// grace au parametre code elle va prendre le dernier numero de la classe concerne 
int NouveauNumero (int code) {

	FILE *fichier = NULL;
	FILE *copie = NULL;

	int numero = 0;
	int nouveauNumero = 0;
	char chaine[MAX_CARACTERE_LIGNE];

	fichier = fopen("../Donnees/Numero.txt", "a+");
	copie = fopen("../Donnees/Numero1.txt", "a+");

	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);
		while (fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier,"%d", &numero);

			if (numero/1000 == code) {

				nouveauNumero = numero + 1;
			
			} else {

				fprintf(copie, "\n%d", numero);
			}
			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}

	fclose(fichier);
	fclose(copie);
	remove("../Donnees/Numero.txt");
	rename("../Donnees/Numero1.txt", "../Donnees/Numero.txt");

	fichier = fopen("../Donnees/Numero.txt", "a+");

	if (fichier != NULL) {
		
		fprintf(fichier, "\n%d", nouveauNumero);
	}
	fclose(fichier);
	return nouveauNumero;
}

//***************************************************//
//													 //
//				STRUCTURE NOTE			 //
//													 //
//***************************************************//


typedef struct {
	
	int numero;
	int reference;
	float noteCC;
	float noteDS;

} Note;

//***************************************************//
//													 //
//				STRUCTURE MATIERE_CLASSE			 //
//													 //
//***************************************************//

typedef enum {

	non,
	oui,
	note_erreur

} NOTER;

typedef struct {
	
	int code;
	int reference;
	NOTER estNoter;

} MatiereClasse;

//Cette fonction permet de supprimer les espace present dans les prenoms et de mettre la premiere lettre en majuscule
void SupprimerEspace(char *chaine) {

	if (*(chaine + 0) >= 'a') {
		
		*(chaine + 0) = *(chaine + 0) - 32;
	}

	for(int i = 1; i < strlen(chaine); i ++) {

		if (*(chaine + i) < 'a' && *(chaine + i) != ' ' && *(chaine + i) >= 'A') {
			
			*(chaine + i) = *(chaine + i) + 32;
		}

		if (*(chaine + i) == ' ') {
			
			*(chaine + i) = '_';
		}

		if (*(chaine + i - 1) == '_') {
			
			if (*(chaine + i) >= 'a' && *(chaine + i) <= 'z') {
				
				*(chaine + i) = *(chaine + i) - 32;
			}
		}
	}
}
//cette fonction permet de remettre les espaces supprimes
void RemettreEspace(char *chaine) {

	for (int i = 0; i < strlen(chaine); ++i) {
		
		if (*(chaine + i) == '_') {
			
			*(chaine + i) = ' ';
		}
	}
}