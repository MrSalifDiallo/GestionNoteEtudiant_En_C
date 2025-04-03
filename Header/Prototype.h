#include "Structure.h"

//***************************************************//
//													 //
//				  Gestion des etudiants 			 //
//													 //
//***************************************************//

int RechercheNumeroEtudiant (int code, int *TableauNumero);
int RechercheEtudiant(Etudiant etudiantRechercher);

//ajouter un etudiant
int AjouterEtudiant();
//ajouter plusieurs etudiants
void AjouterEtudiants();

void MailGenerateur(Etudiant etudiant, char *mail);

//    modifier les info sur un etudiants;
// fonction principale
int ModifierEtudiant(Etudiant etudiant, int option);

//fonction secondaire
int ModifierNomPrenom(int numero);
int ModifierDateNaissance(int numero);
int ModifierClasseEtudiant(int numero);
int ModifierEmail(int numero);
int ModifierEtudiantTous(int numero);

int SupprimerEtudiant(int numero);

// affiche une liste des etudiants par classe
int ListerEtudiant();
//affiCHE les info sur un etudiant
void AfficherEtudiant(int numero);

int MenuModifierOptionEtudiant (int choix);
int MenuEtudiant();
int MenuModifierEtudiant ();
int MenuRechercheEtudiant ();
int MenuAjouterEtudiant ();
int MenuSupprimerEtudiant();
int MenuListerEtudiant();
int MenuRechercheParNumero();
void MenuRechercheParNom();
void MenuTransfererEtudiant();
void MenuRechercheParNomEtClasse();
int MenuChoixEtudiant();

//***************************************************//
//													 //
//				  Gestion des Classes   			 //
//													 //
//***************************************************//

int AjouterClasse();
int ModifierClasse();
int SupprimerClasse();
int ListerClasse (int choix);

int MenuClasse();
void MenuAjouterClasse();
void MenuModifierClasse();
void MenuSupprimerClasse();
int MenuListerClasse();

int RechercheClasse(Classe classe);
int RechercheDansFichier(const char *nomFichier, int valeurChercher);
int RechercheDansFichierChaine(const char *nomFichier, char *chaine);
int RechercheDansFichierCombo(const char *nomFichier, char *chaine, int valeurChercher);

//***************************************************//
//													 //
//				  Gestion des matieres  			 //
//													 //
//***************************************************//



void AjouterMatiere ();
int AssocierMatiere();

void ModifierMatiere ();

int AfficherMatiere();
void ListerMatiere();
int ListerMatiereParClasse();

void SupprimerMatiere (int reference);
void SupprimerAssociation (MatiereClasse association);

int MenuSupprimerAssociation();
int MenuChoixListeMatiere ();
int MenuChoixMatiere (int code);

//***************************************************//
//													 //
//				  Gestion des Notes     			 //
//													 //
//***************************************************//

int AjouterNotePourClasse(int code);
int NoterClasse(MatiereClasse association, NOTER estNoter);
void NoterEtudiant(Note note);

void ModifierNotes();
int ModifierNote(Note note);

int SupprimerNote(MatiereClasse association);

int MenuAfficherNote();

int MenuNote();
int MenuAjouterNote();
int MenuSupprimerNote();
int MenuModifierNote();

NOTER EstNoter(int code, int reference);
int EstNoters(int code, int *tableauReference);

//***************************************************//
//													 //
//				  Autres fonctions      			 //
//													 //
//***************************************************//

void InitialiseChaine();
float MoyenneMatiere (int numero, int reference);
float MoyenneFinale (int numero, int code);
void Bulletin (int numero);
int Rang (int numero, int code);
void SupprimerNoteEtudiant(int numero);
int RangMatiere(int numero, int reference);

#include "LectureFichier.h"

//fichier contenant les fonctions pour la gestion des etudiants
#include "Classe.h"
#include "MenuClasse.h"

//fichier contenant les fonctions pour la gestion des classes
#include "Etudiant.h"
#include "MenuEtudiant.h"

//fichier contenant les fonctions pour la gestion des notes
#include "Note.h"
#include "MenuNote.h"

//fichier contenant les fonctions pour la gestion des des matieres
#include "Matiere-Classe.h"
#include "Matiere.h"
#include "MenuMatiere.h"
