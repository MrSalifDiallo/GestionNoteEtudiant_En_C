// int MenuEtudiant();
// int MenuModifierEtudiant ();
// int MenuRechercheEtudiant ();
// void MenuAjouterEtudiant ();
// void MenuSupprimerEtudiant();
// void MenuListerEtudiant();
// void MenuTransfererEtudiant();
// void MenuRechercheParNumero();
// void MenuRechercheParNom();
// void MenuRechercheParNomEtClasse();

int GestionEtudiants () {

	int choix = 0;

	CLEAR;

	Debut :

	choix = MenuEtudiant();

	switch (choix) {

		case 1:

			MenuRechercheEtudiant();

		break;

		case 2:
			MenuAjouterEtudiant();
		break;

		case 3:
			MenuModifierEtudiant();
		break;

		case 4:
			MenuSupprimerEtudiant();
		break;

		case 5:
			MenuListerEtudiant();				
		break;

		default :return 1;
	}
		goto Debut;
}

int MenuEtudiant() {

	int choix = 0;

	Debut :
	CLEAR;
	NB;
	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("|             Choisissez une option :                                              |\n");
	printf("|                                     1 : Rechercher un Etudiant                   |\n");
    printf("|               .odbo.                2 : Ajouter Etudiant(s)                      |\n");               
    printf("|           .od88888888bo.            3 : Modifier les informations sur un Etudiant|\n");      
    printf("|       .od8888888888888888bo.        4 : Supprimer un Etudiant                    |\n");
    printf("|   .od888888888888888888888888bo.    5 : Lister les Etudiants                     |\n");
    printf("|od88888888888888888888888888888888bo 6 : Revenir en arriere                       |\n");
    printf("| `~888888888888888888888888888888~'                                               |\n");
    printf("|   `~888888888888888888888888~' |                                                 |\n");
    printf("|       `~888888888888888888~'  E|S                                                |\n");
    printf("|         |`~888888888888~'|     P                                                 |\n");
    printf("|         \\   `~888888~'  /                                                        |\n");     
    printf("|          `-_   `~~'   _-'                                                        |\n");      
    printf("|             `--____--'                                                           |\n");
    printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("|\t     Votre choix (1\\2\\3\\4\\5\\6) :");
    scanf("%d",&choix);


	while (choix < 1 || choix > 6) {

		CLEAR;
		goto Debut;
		break;
	}
	
	return choix;
}
int MenuModifierEtudiant () {

	int choix = 0;
	Debut:
	
	CLEAR;

	printf("+--------------------------------------------------------------+\n");            
    printf("_______________________________Choissisez une option:          |\n");
    printf("|@@@@@@@@   @@@@@@   @@@@@@@  |   1.Entrer son numero          |\n");
    printf("|@@@@@@@@  @@@@@@@   @@@@@@@@ |   2.Rechercher l'etudiant      |\n");      
    printf("|@@!       !@@       @@!  @@@ |   3.Menu precedent             |\n");
    printf("|!@!       !@!       !@!  @!@ |                                |\n");
    printf("|@!!!:!    !!@@!!    @!@@!@!  |                                |\n");
    printf("|!!!!!:     !!@!!!   !!@!!!   |                                |\n");
    printf("|!!:            !:!  !!:      |                                |\n");
    printf("|:!:           !:!   :!:      |                                |\n");
    printf("| :: ::::  :::: ::    ::      |                                |\n");
    printf("|: :: ::   :: : :     :       |                                |\n");
    printf("|-----------------------------|                                |\n");
	printf("\t     Votre choix (1\\2\\3) : ");
	scanf("%d", &choix);

	while(choix < 1 || choix > 3) {

		CLEAR;

		goto Debut;
	}
	if (choix != 3) {

		MenuModifierOptionEtudiant(choix);
		goto Debut;
	
	} else
	
		return 1;
}

int MenuModifierOptionEtudiant (int choix) {

	int choixModification = 0;
	int code = 0;
	int numero = 0;
	Debut:

	if (choix == 1) {
			
		numero = MenuRechercheParNumero();

	} else {

		code = MenuListerClasse();

		if (code != 0) {	

			numero = MenuChoixEtudiant(code);
			
		} else return 0;
	}

	CLEAR;

	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                       GESTION ETUDIANTS                         |\n");
	printf("|                                                                 |\n");
	printf("|                      Modifier un Etudiant                       |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez une option :                              |\n");
	printf("|                                                                 |\n");
	printf("|\t\t   1 : Tous Modifier                              |\n");
	printf("|\t\t   2 : Modifier nom et prenom                     |\n");
	printf("|\t\t   3 : Modifier date de naissance                 |\n");
	printf("|\t\t   4 : Modifier la classe et niveau               |\n");
	printf("|\t\t   5 : Revenir en arriere                         |\n");
	printf("|                                                                 |\n");

	printf("\t     Votre choix (1\\2\\3\\4\\5) : ");

	scanf("%d", &choixModification);

	while(choixModification < 1 || choixModification > 5) {
		CLEAR;

		goto Debut;
	}

	if (choixModification == 6) {
		
		return 1;
	
	} else {

		if (numero != 0) {
			switch (choixModification) {

				case 1:
					ModifierEtudiantTous(numero);
				break;
				case 2:
					ModifierNomPrenom(numero);
				break;

				case 3:
					ModifierDateNaissance(numero);
				break;

				case 4:
					ModifierClasseEtudiant(numero);
				break;

				default: return 1;
			}
		}
	}
}

int MenuRechercheEtudiant () {

	int choix = 0;

	CLEAR;

	Debut:
	
	printf("+--------------------------------------------------------+\n");            
    printf("_______________________________Choissisez une option:    |\n");
    printf("|@@@@@@@@   @@@@@@   @@@@@@@  |   1.Rechercher par numero|\n");
    printf("|@@@@@@@@  @@@@@@@   @@@@@@@@ |   2.Rechercher par nom   |\n");      
    printf("|@@!       !@@       @@!  @@@ |   3.Retour               |\n");
    printf("|!@!       !@!       !@!  @!@ |                          |\n");
    printf("|@!!!:!    !!@@!!    @!@@!@!  |                          |\n");
    printf("|!!!!!:     !!@!!!   !!@!!!   |                          |\n");
    printf("|!!:            !:!  !!:      |                          |\n");
    printf("|:!:           !:!   :!:      |                          |\n");
    printf("| :: ::::  :::: ::    ::      |                          |\n");
    printf("|: :: ::   :: : :     :       |                          |\n");
    printf("|-----------------------------|                          |\n");
    printf("\t     Votre choix (1\\2\\3) : ");
	scanf("%d", &choix);

	while(choix < 1 || choix > 3) {

		CLEAR;
		goto Debut;
	}

	switch (choix) {
				
		case 1: 
			MenuRechercheParNumero();
		break;

		case 2:
			MenuRechercheParNom();
		break;

		default:
		
		return 1;
	}

	goto Debut;
}

int MenuAjouterEtudiant () {

	int choix = 0;

	Debut:
	
	CLEAR;

	printf("+--------------------------------------------------------------+\n");            
    printf("_______________________________Choissisez une option:          |\n");
    printf("|@@@@@@@@   @@@@@@   @@@@@@@  |   1.Ajouter plusieurs etudiants|\n");
    printf("|@@@@@@@@  @@@@@@@   @@@@@@@@ |   2.Ajouter un seul etudiant   |\n");      
    printf("|@@!       !@@       @@!  @@@ |   3.Menu precedent             |\n");
    printf("|!@!       !@!       !@!  @!@ |                                |\n");
    printf("|@!!!:!    !!@@!!    @!@@!@!  |                                |\n");
    printf("|!!!!!:     !!@!!!   !!@!!!   |                                |\n");
    printf("|!!:            !:!  !!:      |                                |\n");
    printf("|:!:           !:!   :!:      |                                |\n");
    printf("| :: ::::  :::: ::    ::      |                                |\n");
    printf("|: :: ::   :: : :     :       |                                |\n");
    printf("|-----------------------------|                                |\n");
	printf("\t     Votre choix (1\\2\\3) : ");

	scanf("%d", &choix);

	while(choix < 1 || choix > 3) {
		CLEAR;

		goto Debut;
	}
	switch (choix) {

		case 1:
			AjouterEtudiants(MenuListerClasse());
		break;

		case 2:
			AjouterEtudiant(0);
		break;

		default :
		 return 1;
	}
		goto Debut;
}

int MenuRecherche() {}

int MenuSupprimerEtudiant() {

	int numero = 0;
	int numero_existe = 0;
	int choix = 0;
	Debut:
	
	CLEAR;

	printf("+--------------------------------------------------------+\n");            
    printf("_______________________________Choissisez une option:    |\n");
    printf("|@@@@@@@@   @@@@@@   @@@@@@@  |   1.Entrer son numero    |\n");
    printf("|@@@@@@@@  @@@@@@@   @@@@@@@@ |   2.Rechercher l'etudiant|\n");      
    printf("|@@!       !@@       @@!  @@@ |   3.Menu precedent       |\n");
    printf("|!@!       !@!       !@!  @!@ |                          |\n");
    printf("|@!!!:!    !!@@!!    @!@@!@!  |                          |\n");
    printf("|!!!!!:     !!@!!!   !!@!!!   |                          |\n");
    printf("|!!:            !:!  !!:      |                          |\n");
    printf("|:!:           !:!   :!:      |                          |\n");
    printf("| :: ::::  :::: ::    ::      |                          |\n");
    printf("|: :: ::   :: : :     :       |                          |\n");
    printf("|-----------------------------|                          |\n");
	printf("\t     Votre choix (1\\2\\3) : ");

	scanf("%d", &choix);

	while(choix < 1 || choix > 3) {

		CLEAR;

		goto Debut;
	}
	switch (choix) {

		case 1:
			printf("\tEntrer le numero de l'etudiant :");
			scanf("%d", &numero);
			numero_existe = RechercheDansFichier("../Donnees/Etudiant.csv", numero);

			while(!numero_existe){

				printf("ce numero n'existe pas !!!\n");
				printf("\tEntrer le numero de l'etudiant :");
				scanf("%d", &numero);
				numero_existe = RechercheDansFichier("../Donnees/Etudiant.csv", numero);
			}
			SupprimerEtudiant(numero);
		break;

		case 2:
			SupprimerEtudiant(MenuChoixEtudiant(MenuListerClasse()));
		break;

		default :
		
		 return 1;
	}
		goto Debut;
	
}

int MenuListerEtudiant() {

	int choix = 0;
	int choixListe = 0;

	Debut:
	
	CLEAR;

	printf("+----------------------------------------------------------------+\n");            
    printf("_______________________________Choissisez une option:            |\n");
    printf("|@@@@@@@@   @@@@@@   @@@@@@@  |   1.Lister tous les etudiants    |\n");
    printf("|@@@@@@@@  @@@@@@@   @@@@@@@@ |   2.Lister une classe            |\n");      
    printf("|@@!       !@@       @@!  @@@ |   3.Menu precedent               |\n");
    printf("|!@!       !@!       !@!  @!@ |                                  |\n");
    printf("|@!!!:!    !!@@!!    @!@@!@!  |                                  |\n");
    printf("|!!!!!:     !!@!!!   !!@!!!   |                                  |\n");
    printf("|!!:            !:!  !!:      |                                  |\n");
    printf("|:!:           !:!   :!:      |                                  |\n");
    printf("| :: ::::  :::: ::    ::      |                                  |\n");
    printf("|: :: ::   :: : :     :       |                                  |\n");
    printf("|-----------------------------|                                  |\n");
	printf("\t     Votre choix (1\\2\\3) : ");

	scanf("%d", &choix);

	while(choix < 1 || choix > 3) {

		CLEAR;

		goto Debut;
	}
	switch (choix) {

		case 1:
			
			CLEAR;
			ListerEtudiant();
			getchar();
			getchar();

		break;

		case 2:

			choixListe = MenuListerClasse();
			ListerClasse(choixListe);

		break;

		default :
		 return 1;
	}
		goto Debut;
}

int MenuRechercheParNumero() {

	int numero = 0;
	int trouver = 0;

	char nom[MAX_LONG_NOM];
	const char nomFichier[] ="../Donnees/Etudiant.csv";

	CLEAR;
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      recherche Par numero                       |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("\tEntrer le numero de l'etudiant : ");
	scanf("%d", &numero);

	if (trouver = RechercheDansFichier(nomFichier, numero)) {

		CLEAR;
		AfficherEtudiant(numero);
		getchar();
		getchar();
		return numero;
	} else {

		printf("\n\tNous avons pas trouver d'etudiant !!!\n");
		getchar();
		getchar();
		CLEAR;
		return 0;
	}
}

void MenuRechercheParNom () {

	int c = 0;

	char nom[MAX_LONG_NOM];
	const char nomFichier[] ="../Donnees/Etudiant.csv";

	CLEAR;
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      GESTION DES ETUDIANTS                      |\n");
	printf("|                                                                 |\n");
	printf("|                        recherche Par Nom                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");
	printf("\tEntrer le nom de l'etudiant : ");

	fscanf (stdin, "%s", nom);
	do { 
		c = getchar(); 
	} while (c != '\n' && c != EOF);

	SupprimerEspace(nom);
	CLEAR;
	RechercheDansFichierChaine (nomFichier, nom);
}

void MenuRechercheParNomEtClasse () {

	int c = 0;

	char nom[MAX_LONG_NOM];
	const char nomFichier[] ="../Donnees/Etudiant.csv";

	int code = 0;

	CLEAR;
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                      GESTION DES ETUDIANTS                      |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("\tEntrer le nom de l'etudiant : ");
	fscanf (stdin, "%s", nom);

    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF);
	SupprimerEspace(nom);

	code = MenuListerClasse();

	if (code != 0) {
		
		RechercheDansFichierCombo (nomFichier, nom, code);
	}
}


int MenuChoixEtudiant(int code) {

	int choix = 0;

	Debut:

	CLEAR;
	
	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                     Liste des Etudiants                         |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez un Etudiant :                             |\n");
	printf("|                                                                 |\n");

	FILE *fichier= NULL;

	Etudiant etudiant;

	char chaine[MAX_CARACTERE_LIGNE];
	int nombreEtudiant = 0;

	const int MAX_TABLEAU = 100;

	int tableauNumero[MAX_TABLEAU];

	fichier = fopen("../Donnees/Etudiant.csv", "r");

	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_SET);
		
		while(fgets(chaine, MAX_CARACTERE_LIGNE, fichier) != NULL) {

			fscanf(fichier, "%d;%s ;%s ;%s ;%d\\%d\\%d;%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, &etudiant.dateNaissance.jour, &etudiant.dateNaissance.mois, &etudiant.dateNaissance.annee, &etudiant.classe);

			if (code == etudiant.classe) {

				nombreEtudiant ++;
				tableauNumero[nombreEtudiant] = etudiant.numero;
				printf("|\t%d : %d %18s %10s                  |\n", nombreEtudiant, etudiant.numero, etudiant.prenom, etudiant.nom);
			}

			fseek(fichier, ftell(fichier), SEEK_SET);
		}
	}

	fclose(fichier);

	printf("| 0 : revenir en arriere                                          |\n");
	printf("|                                                                 |\n");

	printf("\t     Votre choix entre (0..%d) : ", nombreEtudiant);
	scanf("%d", &choix);


	while (choix < 0 || choix > nombreEtudiant) {

		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (0..%d)!                    |\n", nombreEtudiant);
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
		return tableauNumero[choix];
}
