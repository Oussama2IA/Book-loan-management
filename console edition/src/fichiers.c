#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

/***** Pour initialiser le programme *****/
void init()
{
    // Initialiser la liste des adhérents
    firstAdh = NULL;
    // Initialiser le tableau des listes des livres
    int i;
    for (i = 0; i < MAX; i++)
    {
        strcpy(array[i].categ_liv, "");
        array[i].firstLiv = NULL;
    }
    nbOfCateg = 0;
}

/***** Pour charger les informations à partir des fichiers *****/
void chargerInfos()
{
    init();
    // Charger les infos des adhérents
    FILE *ficAdh = fopen("data/adherents.dta", "rb");
    if (ficAdh == NULL)
    {
        fprintf(stderr, "\n\t\t\tErreur ouverture fichier!\n");
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        adh *infoAdh = Malloc(adh);
        fread(infoAdh, sizeof(adh), 1, ficAdh);
        if (feof(ficAdh))
            break;
        ajouterAdh(infoAdh);
    }
    fclose(ficAdh);
    // Charger les infos des livres
    FILE *ficLiv = fopen("data/livres.dta", "rb");
    if (ficLiv == NULL)
    {
        fprintf(stderr, "\n\t\t\tErreur ouverture fichier!\n");
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        liv *infoLiv = Malloc(liv);
        fread(infoLiv, sizeof(liv), 1, ficLiv);
        if (feof(ficLiv))
            break;
        ajouterLiv(infoLiv);
    }
    fclose(ficLiv);
}

/***** Pour sauvegarder les informations sur les fichiers *****/
void sauvegarderInfos()
{
    // Sauvegarder les infos des adhérents
    FILE *ficAdh = fopen("data/adherents.dta", "wb");
    if (ficAdh == NULL)
    {
        fprintf(stderr, "\n\t\t\tErreur ouverture fichier!\n");
        exit(EXIT_FAILURE);
    }
    listeAdh *Adh = firstAdh;
    while (Adh != NULL)
    {
        fwrite(Adh->info, sizeof(adh), 1, ficAdh);
        Adh = Adh->next;
    }
    fclose(ficAdh);
    // Sauvegarder les infos des livres
    FILE *ficLiv = fopen("data/livres.dta", "wb");
    if (ficLiv == NULL)
    {
        fprintf(stderr, "\n\t\t\tErreur ouverture fichier!\n");
        exit(EXIT_FAILURE);
    }
    listeLiv *Liv;
    int i;
    for (i = 0; i < nbOfCateg; i++)
    {
        Liv = array[i].firstLiv;
        while (Liv != NULL)
        {
            fwrite(Liv->info, sizeof(liv), 1, ficLiv);
            Liv = Liv->next;
        }
    }
    fclose(ficLiv);
}