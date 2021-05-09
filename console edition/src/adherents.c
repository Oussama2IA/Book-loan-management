#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

/***** Déclaration des variables globales *****/
listeAdh *firstAdh; // Liste chaînée des adhérents

/***** Pour afficher les infos des adhérents *****/
void afficherAdhs()
{
    listeAdh *p = firstAdh;
    while (p != NULL)
    {
        printf("  | %-03d ", p->info->num_adh);
        printf("| %-15s ", p->info->nom_adh);
        printf("| %-15s ", p->info->prenom_adh);
        printf("| %-30s ", p->info->email_adh);
        printf("| %-50s |\n", p->info->adress_adh);
        p = p->next;
    }
    printf("  +-----+-----------------+-----------------+--------------------------------+----------------------------------------------------+\n\n");
}

/***** Génerer un numéro unique à l'adhérent *****/
int numUnqiueAdh()
{
    int num = 1;
    listeAdh *Adh = firstAdh;
    while (Adh != NULL)
    {
        num = Adh->info->num_adh + 1;
        Adh = Adh->next;
    }
    return num;
}

/***** Pour ajouter un adhérent à la liste *****/
void ajouterAdh(adh *info)
{
    listeAdh *newAdh = Malloc(listeAdh);
    newAdh->info = info;
    newAdh->next = NULL;
    if (firstAdh == NULL)
    {
        firstAdh = newAdh;
        return;
    }
    listeAdh *p = firstAdh;
    listeAdh *pred;
    while (p != NULL)
    {
        pred = p;
        p = p->next;
    }
    pred->next = newAdh;
}

/***** Pour insérer les infos de l'adhérent *****/
void insererAdh()
{
    adh *info = Malloc(adh);
    // Génerer un numéro unique à l'adhérent
    info->num_adh = numUnqiueAdh();
    // Initialiser le nombre d'empruntes
    info->nbre_emprunts_adh = 0;
    // Saisir les infos d'adhérent
    printf("\t\tSaisir les infos d'adh%crent:\n", 130);
    printf("\t\t\tSon nom: ");
    gets(info->nom_adh);
    printf("\t\t\tSon pr%cnom: ", 130);
    gets(info->prenom_adh);
    printf("\t\t\tSon adresse %cmail: ", 130);
    gets(info->email_adh);
    printf("\t\t\tSon adresse personnelle: ");
    gets(info->adress_adh);
    ajouterAdh(info);
}

/***** Pour rechercher sur l'adhérent (par son nom) *****/
adh *rechercherAdh(char *nom_adh)
{
    listeAdh *p = firstAdh;
    while (p != NULL)
    {
        if (strcmp(p->info->nom_adh, nom_adh) == 0)
            return p->info;
        p = p->next;
    }
    adh *info = NULL;
    return info;
}

/***** Pour modifier les informations d'un adhérent *****/
void modifierAdh(char *nom_adh)
{
    adh *info = rechercherAdh(nom_adh);
    if (info == NULL)
    {
        printf("\n\t\t\t%s n'existe pas!\n\n", nom_adh);
        return;
    }
    printf("\t\tRessaisir les infos d'adh%crent:\n", 130);
    printf("\t\t\tSon nom: ");
    gets(info->nom_adh);
    printf("\t\t\tSon pr%cnom: ", 130);
    gets(info->prenom_adh);
    printf("\t\t\tSon adresse %cmail: ", 130);
    gets(info->email_adh);
    printf("\t\t\tSon adresse personnelle: ");
    gets(info->adress_adh);
}

/***** Pour suprrimer un adhérent *****/
void supprimerAdh(char *nom_adh)
{
    listeAdh *p = firstAdh;
    listeAdh *pred;
    while ((p != NULL) && (strcmp(p->info->nom_adh, nom_adh) != 0))
    {
        pred = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("\n\t\t\t%s n'existe pas!\n\n", nom_adh);
        return;
    }
    if (p == firstAdh)
        firstAdh = p->next;
    else
        pred->next = p->next;
    free(p);
}