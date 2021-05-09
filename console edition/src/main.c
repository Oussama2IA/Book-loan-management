#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "declarations.h"

/*
    system("TITLE titre")            : Le titre de la console
    system("cls")                    : Effacer la console
    system("pasue")                  : Pause la console
    system("color couleur")          : Changer la couleur de la console
    system("mode con lines=largeur") : Largeur de la console
    system("mode con cols=longeur")  : Longuer de la console
*/

/***** Déclaration des variables globales *****/
char key;    // Variable pour naviguer entre les fonctions du programme
Bool close;  // Si close reçoit true le programme s'arrêtera
Bool retour; // Si retour reçoit true le programme reviendra au menu principal

/***** Les fonctions de menu *****/
void gestionAdhs();
void gestionLivs();
void gestionEmpruntes();
void quitterProgramme();

/***** La fonction main *****/
int main()
{
    system("TITLE Gestion de prets de livres");
    system("mode con lines=21");
    system("mode con cols=85");
    system("color 4F");
    chargerInfos(); // Charger les infos à partir des fichiers
    close = false;
    while (!close)
    {
        /***** Menu principal ******/
        system("cls");
        printf("\n\t\t+---------------------------------------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|          GESTION DE PRET DE LIVRES          |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n\n");
        printf("\n\t\t+---------------Menu Principal----------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|         1. Gestion des adh%crents            |\n", 130);
        printf("\t\t|         2. Gestion des livres               |\n");
        printf("\t\t|         3. Gestion des emprunts             |\n");
        printf("\t\t|         4. Quitter l'application            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n");
        key = getch();
        switch (key)
        {
        case '1':
            /****** gestion des adhérents ******/
            gestionAdhs();
            break;
        case '2':
            /****** gestion des livres ******/
            gestionLivs();
            break;
        case '3':
            /****** gestion des empruntes ******/
            gestionEmpruntes();
            break;
        case '4':
            /****** Quitter l'application ******/
            quitterProgramme();
            break;
        default:
            break;
        }
    }

    exit(EXIT_SUCCESS);
}

/***** Menu de gestion des adhérents *****/
void gestionAdhs()
{
    system("color 1F");
    char nom_adh[15];
    retour = false;
    while (!retour)
    {
        system("cls");
        printf("\n\t\t+---------------------------------------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|            GESTION DES ADHERENTS            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n\n");
        printf("\n\t\t+------------Gestion des adh%crents------------+\n", 130);
        printf("\t\t|                                             |\n");
        printf("\t\t|         1. Afficher les adh%crents           |\n", 130);
        printf("\t\t|         2. Ajouter un adh%crent              |\n", 130);
        printf("\t\t|         3. Modifier un adh%crent             |\n", 130);
        printf("\t\t|         4. Supprimer un adh%crent            |\n", 130);
        printf("\t\t|         5. Rechercher sur un adh%crent       |\n", 130);
        printf("\t\t|         6. Retour Menu Principal            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n");
        key = getch();
        switch (key)
        {
        case '1':
            /****** Afficher les adhérents ******/
            system("cls");
            system("mode con lines=33");
            system("mode con cols=133");
            printf("\n  +-------------------------------------------------------------------------------------------------------------------------------+\n");
            printf("  |                                                                                                                               |\n");
            printf("  |                                                     Liste des adh%crents                                                       |\n", 130);
            printf("  |                                                                                                                               |\n");
            printf("  +-------------------------------------------------------------------------------------------------------------------------------+\n\n");
            printf("  +-----+-----------------+-----------------+--------------------------------+----------------------------------------------------+\n");
            printf("  |Num  | Nom             | Pr%cnom          | E-mail                         |Adress                                              |\n", 130);
            printf("  +-----+-----------------+-----------------+--------------------------------+----------------------------------------------------+\n");
            afficherAdhs();
            printf("  ");
            system("pause");
            system("mode con lines=21");
            system("mode con cols=85");
            break;
        case '2':
            /****** Ajouter un adhérent ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES ADHERENTS            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            insererAdh();
            printf("\t\t");
            system("pause");
            break;
        case '3':
            /****** Modifier un adhérent ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES ADHERENTS            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner le nom d'adh%crent: ", 130);
            gets(nom_adh);
            modifierAdh(nom_adh);
            printf("\t\t");
            system("pause");
            break;
        case '4':
            /****** Supprimer un adhérent ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES ADHERENTS            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner le nom d'adh%crent: ", 130);
            gets(nom_adh);
            supprimerAdh(nom_adh);
            printf("\t\t");
            system("pause");
            break;
        case '5':
            /****** Rechercher sur un adhérent ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES ADHERENTS            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner le nom d'adh%crent: ", 130);
            gets(nom_adh);
            adh *info = rechercherAdh(nom_adh);
            if (info == NULL)
                printf("\n\t\t\t%s n'existe pas!\n\n", nom_adh);
            else
            {
                printf("\t\tL'adh%crent num%cro %d:\n", 130, 130, info->num_adh);
                printf("\t\t\tNom et pr%cnom: %s %s\n", 130, info->nom_adh, info->prenom_adh);
                printf("\t\t\tEmail: %s\n", info->email_adh);
                printf("\t\t\tAdresse: %s\n", info->adress_adh);
            }
            printf("\t\t");
            system("pause");
            break;
        case '6':
            system("color 4F");
            retour = true; // Retour au menu principal
            break;
        default:
            break;
        }
    }
}

/***** Menu de gestion des livres *****/
void gestionLivs()
{
    system("color 5F");
    char categ_liv[15];
    char titre_liv[30];
    retour = false;
    while (!retour)
    {
        system("cls");
        printf("\n\t\t+---------------------------------------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|              GESTION DES LIVRES             |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n\n");
        printf("\n\t\t+-------------Gestion des livres--------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|         1. Ordonner les livres              |\n");
        printf("\t\t|         2. Ajouter un livre                 |\n");
        printf("\t\t|         3. Modifier un livre                |\n");
        printf("\t\t|         4. Supprimer un livre               |\n");
        printf("\t\t|         5. Rechercher sur un livre          |\n");
        printf("\t\t|         6. Retour Menu Principal            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n");
        key = getch();
        switch (key)
        {
        case '1':
            /****** Ordonner les livres ******/
            system("cls");
            system("mode con lines=25");
            system("mode con cols=100");
            printf("\n  +---------------------------------------------------------------------------------------------+\n");
            printf("  |                                                                                             |\n");
            printf("  |                               Ordonner les livres par cat%cgorie                             |\n", 130);
            printf("  |                                                                                             |\n");
            printf("  +---------------------------------------------------------------------------------------------+\n\n");
            printf("  +-----------------+-----+--------------------------------+-----------------+------------------+\n");
            printf("  | Cat%cgorie       |Num  | Titre                          | Nom de l'auteur |Pr%cnom de l'auteur|\n", 130, 130);
            printf("  +-----------------+-----+--------------------------------+-----------------+------------------+\n");
            ordonnerLivs();
            printf("  ");
            system("pause");
            system("mode con lines=21");
            system("mode con cols=85");
            break;
        case '2':
            /****** Ajouter un livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|              GESTION DES LIVRES             |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            insererLiv();
            printf("\t\t");
            system("pause");
            break;
        case '3':
            /****** Modifier un livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|              GESTION DES LIVRES             |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            modifierLiv(categ_liv, titre_liv);
            printf("\t\t");
            system("pause");
            break;
        case '4':
            /****** Supprimer un livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|              GESTION DES LIVRES             |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            supprimerLiv(categ_liv, titre_liv);
            printf("\t\t");
            system("pause");
            break;
        case '5':
            /****** Rechercher sur un livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|              GESTION DES LIVRES             |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            liv *info = rechercherLiv(categ_liv, titre_liv);
            if (info == NULL)
                printf("\n\t\t\t%s n'existe pas!\n\n", titre_liv);
            else
            {
                printf("\t\tLe livre num%cro %d:\n", 130, info->num_liv);
                printf("\t\t\tSon titre: %s\n", info->titre_liv);
                printf("\t\t\tSa cat%cgorie: %s\n", 130, info->categ_liv);
                printf("\t\t\tNom et pr%cnom de l'auteur: %s %s\n", 130, info->auteur.nom_aut, info->auteur.prenom_aut);
            }
            printf("\t\t");
            system("pause");
            break;
        case '6':
            system("color 4F");
            retour = true; // Retour au menu principal
            break;
        default:
            break;
        }
    }
}

/***** Menu de gestion des empruntes *****/
void gestionEmpruntes()
{
    system("color 2F");
    char nom_adh[15];
    char categ_liv[15];
    char titre_liv[30];
    retour = false;
    while (!retour)
    {
        system("cls");
        printf("\n\t\t+---------------------------------------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|            GESTION DES EMPRUNTES            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n\n");
        printf("\n\t\t+------------Gestion des empruntes------------+\n");
        printf("\t\t|                                             |\n");
        printf("\t\t|         1. Emprunter un livre               |\n");
        printf("\t\t|         2. Les livres emprunt%cs             |\n", 130);
        printf("\t\t|         3. Les emprunteurs de livre         |\n");
        printf("\t\t|         4. Rendre un livre                  |\n");
        printf("\t\t|         5. Retour Menu Principal            |\n");
        printf("\t\t|                                             |\n");
        printf("\t\t+---------------------------------------------+\n");
        key = getch();
        switch (key)
        {
        case '1':
            /****** Emprunter un livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES EMPRUNTES            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner le nom d'adh%crent: ", 130);
            gets(nom_adh);
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            emprunterLiv(nom_adh, categ_liv, titre_liv);
            printf("\t\t");
            system("pause");
            break;
        case '2':
            /****** Afficher les livres empruntés ******/
            system("cls");
            system("mode con lines=25");
            system("mode con cols=100");
            printf("\n  +---------------------------------------------------------------------------------------------+\n");
            printf("  |                                                                                             |\n");
            printf("  |                                  Liste des livres emprunt%cs                                 |\n", 130);
            printf("  |                                                                                             |\n");
            printf("  +---------------------------------------------------------------------------------------------+\n\n");
            printf("  +-----+--------------------------------+-----------------+-----------------+------------------+\n");
            printf("  |Num  | Titre                          | Cat%cgorie       | Nom de l'auteur |Pr%cnom de l'auteur|\n", 130, 130);
            printf("  +-----+--------------------------------+-----------------+-----------------+------------------+\n");
            afficherLivEmpruntes();
            printf("  ");
            system("pause");
            system("mode con lines=21");
            system("mode con cols=85");
            break;
        case '3':
            /****** Afficher les emprunteurs de livre ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES EMPRUNTES            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            afficherAdhEmprunteurs(categ_liv, titre_liv);
            printf("\t\t");
            system("pause");
            break;
        case '4':
            /****** Rendre un livre  ******/
            system("cls");
            printf("\n\t\t+---------------------------------------------+\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|            GESTION DES EMPRUNTES            |\n");
            printf("\t\t|                                             |\n");
            printf("\t\t+---------------------------------------------+\n\n");
            printf("\t\tDonner le nom d'adh%crent: ", 130);
            gets(nom_adh);
            printf("\t\tDonner la cat%cgorie de livre: ", 130);
            gets(categ_liv);
            printf("\t\tDonner le titre de livre: ");
            gets(titre_liv);
            rendreLiv(nom_adh, categ_liv, titre_liv);
            printf("\t\t");
            system("pause");
            break;
        case '5':
            system("color 4F");
            retour = true; // Retour au menu principal
            break;
        default:
            break;
        }
    }
}

/****** Quitter l'application et sauvegarder les modifications ******/
void quitterProgramme()
{
    char save;
    do
    {
        system("cls");
        system("mode con lines=13");
        system("mode con cols=90");
        printf("\n\n\t+------------------------------------------------------------------------+");
        printf("\n\t|                                                                        |");
        printf("\n\t|           Vous voulez sauvegarder les modifications ?[o/n]:            |");
        printf("\n\t|                                                                        |");
        printf("\n\t|                 - o: oui                                               |");
        printf("\n\t|                 - n: non                                               |");
        printf("\n\t|                                                                        |");
        printf("\n\t+------------------------------------------------------------------------+\n\n");
        save = getch();
    } while ((save != 'o') && (save != 'n'));
    if (save == 'o')
        sauvegarderInfos(); // Sauvegarder les modifications sur les fichiers
    close = true;           // Quitter le programme
}