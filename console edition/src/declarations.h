#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

/***** Définition des macro-instructions *****/
#define Malloc(t) (t *)malloc(sizeof(t))
#define max(a, b) (a > b) ? a : b

/***** Définition des constantes *****/
#define MAX 50 // Le nombre maximale des catégories des livres

/***** Définition du type booléan *****/
typedef enum
{
    false,
    true
} Bool;

/***** Structure de l'adhérent *****/
typedef struct
{
    int num_adh;
    char nom_adh[15];
    char prenom_adh[15];
    char email_adh[30];
    char adress_adh[50];
    int nbre_emprunts_adh;
} adh;

/***** Liste chaînée des adhérents *****/
typedef struct _listeAdh
{
    adh *info;
    struct _listeAdh *next;
} listeAdh;

/***** Structure du livre *****/
// Structure de l'auteur
struct _auteur
{
    char nom_aut[15];
    char prenom_aut[15];
};
// Structure du livre
typedef struct
{
    int num_liv;
    char titre_liv[30];
    char categ_liv[15];
    struct _auteur auteur;
    int emprunteur_liv;
} liv;

/***** Liste chaînée des livres *****/
typedef struct _listeLiv
{
    liv *info;
    struct _listeLiv *next;
} listeLiv;

/***** Structure de la catégorie des livres *****/
typedef struct
{
    char categ_liv[15]; // La catégorie
    listeLiv *firstLiv; // Liste chaînée des livres de cette catégorie
} categ;

/***** Déclaration des variables externes *****/
extern listeAdh *firstAdh;
extern categ array[MAX];
extern int nbOfCateg;

/***** Prototype des fonctions *****/
// Les fonctions des adhérents
void afficherAdhs();
void insererAdh();
void ajouterAdh(adh *info);
adh *rechercherAdh(char *nom_adh);
void modifierAdh(char *nom_adh);
void supprimerAdh(char *nom_adh);
// Les fonctions des livres
void ordonnerLivs();
void insererLiv();
void ajouterLiv(liv *info);
liv *rechercherLiv(char *categ_liv, char *titre_liv);
void modifierLiv(char *categ_liv, char *titre_liv);
void supprimerLiv(char *categ_liv, char *titre_liv);
// Les fonctions des empruntes
void emprunterLiv(char *nom_adh, char *categ_liv, char *titre_liv);
void afficherLivEmpruntes();
void afficherAdhEmprunteurs(char *categ_liv, char *titre_liv);
void rendreLiv(char *nom_adh, char *categ_liv, char *titre_liv);
// Pour charger et sauvegarder les infos
void chargerInfos();
void sauvegarderInfos();

#endif // DECLARATIONS_H_INCLUDED