#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

/***** Pour emprunté un livre *****/
void emprunterLiv(char *nom_adh, char *categ_liv, char *titre_liv)
{
    adh *infoAdh = rechercherAdh(nom_adh);
    liv *infoLiv = rechercherLiv(categ_liv, titre_liv);
    // Gestion des erreurs
    if ((infoAdh == NULL) || (infoLiv == NULL) ||
        (infoAdh->nbre_emprunts_adh == 3) ||
        (infoLiv->emprunteur_liv != 0))
    {
        printf("\n\t\t\tOp%cration a %cchou%c!\n\n", 130, 130, 130);
        return;
    }
    // Emprunté le livre
    infoAdh->nbre_emprunts_adh++;
    infoLiv->emprunteur_liv = infoAdh->num_adh;
}

/***** Pour affichier les livres empruntés *****/
void afficherLivEmpruntes()
{
    listeLiv *p;
    int i;
    for (i = 0; i < nbOfCateg; i++)
    {
        p = array[i].firstLiv;
        while (p != NULL)
        {
            if (p->info->emprunteur_liv != 0)
            {
                printf("  | %-03d ", p->info->num_liv);
                printf("| %-30s ", p->info->titre_liv);
                printf("| %-15s ", p->info->categ_liv);
                printf("| %-15s ", p->info->auteur.nom_aut);
                printf("| %-15s  |\n", p->info->auteur.prenom_aut);
            }
            p = p->next;
        }
    }
    printf("  +-----+--------------------------------+-----------------+-----------------+------------------+\n\n");
}

/***** Pour afficher les adhérents emprunteurs de livre *****/
void afficherAdhEmprunteurs(char *categ_liv, char *titre_liv)
{
    liv *infoLiv = rechercherLiv(categ_liv, titre_liv);
    if ((infoLiv == NULL) || (infoLiv->emprunteur_liv == 0))
        return;
    listeAdh *p = firstAdh;
    while (p != NULL)
    {
        if (infoLiv->emprunteur_liv == p->info->num_adh)
        {
            printf("\n\t\t -L'emprunteur de %s est: %s\n\n", titre_liv, p->info->nom_adh);
            return;
        }
        p = p->next;
    }
}

/***** Pour rendre le livre *****/
void rendreLiv(char *nom_adh, char *categ_liv, char *titre_liv)
{
    adh *infoAdh = rechercherAdh(nom_adh);
    liv *infoLiv = rechercherLiv(categ_liv, titre_liv);
    // Gestion des erreurs
    if ((infoAdh == NULL) || (infoLiv == NULL) ||
        (infoLiv->emprunteur_liv != infoAdh->num_adh))
    {
        printf("\n\t\t\tOp%cration a %cchou%c!\n\n", 130, 130, 130);
        return;
    }
    // Rendre le livre
    infoAdh->nbre_emprunts_adh--;
    infoLiv->emprunteur_liv = 0;
}