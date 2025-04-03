
int GestionNotes() {

	int choix = 0;

	Debut:

	choix = MenuNote();

	switch (choix) {

		case 1:
			MenuAjouterNote();
		break;

		case 2:
			MenuModifierNote();
		break;

		case 3:
			MenuAfficherNote();
		break;

		case 4:
			MenuSupprimerNote();
		break;

		default: return 1;
	}
	goto Debut;
}

int MenuAfficherNote() {

	int choix = 0;
	int code = 0;
	int numero = 0;

	Debut :

	CLEAR;

	printf("+-----------------------------------------------------------------+\n");
	printf("|                                                                 |\n");
	printf("|                            SenGNote                             |\n");
	printf("|                                                                 |\n");
	printf("|                        GESTION DES NOTES                        |\n");
	printf("|                                                                 |\n");
	printf("+-----------------------------------------------------------------+\n");

	printf("|                                                                 |\n");
	printf("|\t     Choisissez une option :                              |\n");
	printf("|                                                                 |\n");
	printf("|\t\t   1 : Afficher les notes d'une classe            |\n");
	printf("|\t\t   2 : Afficher les notes d'un etudiant           |\n");
	printf("|\t\t   3 : Revenir en arriere                         |\n");
	printf("|                                                                 |\n");

	printf("\t     Votre choix (1\\2\\3) : ");
	scanf("%d", &choix);


	while (choix < 1 || choix > 3) {

		CLEAR;
		printf("+-----------------------------------------------------------------+\n");
		printf("|                                                                 |\n");
		printf("|            Vous devez choisir entre (1\\2\\3)!                  |\n");
		printf("|                                                                 |\n");
		printf("+-----------------------------------------------------------------+\n");
		getchar();
		getchar();
		CLEAR;
		
		goto Debut;
	}

	switch(choix) {

		case 1:
			ListerNote();
		break;
		case 2: 
			code = MenuListerClasse();
			if (code != 0) {
				numero = MenuChoixEtudiant(code);
				if (numero != 0) {
					Bulletin(numero);
				}
			}
		break;
		default: return 1;
	}
	goto Debut;
}

int MenuNote() {

	int choix = 0;

	Debut :
	NJ;
	CLEAR;

	
	printf("+----------------------------------------------------------------+\n");
    printf("|                                            _______________     |\n");
    printf("| Choisissez une Option:                    |@@@@|     |####|    |\n");
    printf("| 1.Ajout Notes                             |@@@@|     |####|    |\n");
    printf("| 2.Modification Notes                      |@@@@|     |####|    |\n");
    printf("| 3.Lister Notes                            \\@@@@|     |####/   |\n");
    printf("| 4.Supprimer Notes                          \\@@@|     |###/    |\n");
    printf("| 5.Revenr en arriere                         `@@|_____|##'      |\n");
    printf("|                                                  (O)           |\n");
    printf("|                                               .-'''''-.        |\n");
    printf("|                                             .'  * * *  `.      |\n");
    printf("|                                            :  *       *  :     |\n");
    printf("|                                           : ~ E X C E L ~ :    |\n");
    printf("|                                           : ~ L E N C E ~ :    |\n");
    printf("|                                            :  *       *  :     |\n");
    printf("|                                             `.  E S P  .'      |\n");
    printf("|                                               `-.....-'        |\n");
	printf("\t     Votre choix (1\\2\\3\\4\\5) : ");
	scanf("%d", &choix);


	while (choix < 1 || choix > 5) {

		CLEAR;
		
		goto Debut;
	}

	return choix;
}

int MenuAjouterNote () {

	CLEAR;

	printf("      _/_/    _/                        _/   \n");
	printf("   _/    _/        _/_/    _/    _/  _/_/_/_/\n");   
	printf("  _/_/_/_/  _/  _/    _/  _/    _/    _/     \n");   
	printf(" _/    _/  _/  _/    _/  _/    _/    _/      \n");   
	printf("_/    _/  _/    _/_/      _/_/_/      _/_/   \n");   
	printf("         _/                                  \n");   
	printf("      _/                                     \n");
	int code = 0;

	code = MenuListerClasse();

	if (code == 0)
		return 1;
	else
		AjouterNotePourClasse(code);
}

int MenuModifierNote () {

	int choix = 0;

	MatiereClasse association;
	Note note;
	if (association.code != 0) {
		
		Debut:
		CLEAR;
		printf("+----------------------------------------------------------------+\n");
    	printf("|                                            _______________     |\n");
    	printf("| Choisissez une Option:                    |@@@@|     |####|    |\n");
    	printf("| 1.Modifier une note                       |@@@@|     |####|    |\n");
    	printf("| 2.Modifier toutes les Notes               |@@@@|     |####|    |\n");
    	printf("| 3.Menu precedent                          \\@@@@|     |####/   |\n");
    	printf("|                                            \\@@@|     |###/    |\n");
    	printf("|                                             `@@|_____|##'      |\n");
    	printf("|                                                  (O)           |\n");
    	printf("|                                               .-'''''-.        |\n");
    	printf("|                                             .'  * * *  `.      |\n");
    	printf("|                                            :  *       *  :     |\n");
    	printf("|                                           : ~ E X C E L ~ :    |\n");
    	printf("|                                           : ~ L E N C E ~ :    |\n");
    	printf("|                                            :  *       *  :     |\n");
    	printf("|                                             `.  E S P  .'      |\n");
    	printf("|                                               `-.....-'        |\n");

		printf("\t     Votre choix (1\\2\\3) : ");
		scanf("%d", &choix);


		while (choix < 1 || choix > 5) {

			CLEAR;
			
			goto Debut;
		}

		switch(choix) {

			case 1:

				association.code = MenuListerClasse();
				association.reference = MenuChoixMatiere(association.code);
				if (EstNoter(association.code, association.reference) == oui) {			

					if (association.reference != 0){

						note.reference = association.reference;
						note.numero = MenuChoixEtudiant(association.code);

						if (note.numero != 0)
							ModifierNote(note);
						else
							return 1;
					} else
						return 1;
				} else {

					CLEAR;
					printf("+--------------------------------------------------------------------+\n");
					printf("|L'etudiant ne peut pas etre noter si la classe n'a recue aucune note|\n");
					printf("+--------------------------------------------------------------------+\n");
					getchar();
					getchar();
					return 0;
				}

			break;
			case 2:
				ModifierNotes();
			break;
			default: return 1;
		}
	} else
		return 1;
}

int MenuSupprimerNote () {

	MatiereClasse association;
	Note note;

	association.code = MenuListerClasse();

	if (association.code != 0) {

		association.reference = MenuChoixMatiere(association.code);

		if (association.reference != 0){

			note.reference = association.reference;
			SupprimerNote(association);
		} else
			return 1;
	} else
		return 1;
}