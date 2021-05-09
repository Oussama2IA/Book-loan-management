#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

/***** Déclaration des variables globales *****/
categ array[MAX]; // Tableau des listes chaînées des livres par catégorie
int nbOfCateg;    // Nombre de catégories existe dans le tableau

/***** Pour ordonner les infos des livres par catégorie *****/
void ordonnerLivs()
{
    listeLiv *p;
    int i;
    for (i = 0; i < nbOfCateg; i++)
    {
        p = array[i].firstLiv;
        printf("  | %-15s ", array[i].categ_liv);
        int j = -1;
        while (p != NULL)
        {
            if (j == 0)
                printf("  | %-15s ", "");
            j = 0;
            printf("| %-03d ", p->info->num_liv);
            printf("| %-30s ", p->info->titre_liv);
            printf("| %-15s ", p->info->auteur.nom_aut);
            printf("| %-15s  |\n", p->info->auteur.prenom_aut);
            p = p->next;
        }
        printf("  +-----------------+-----+--------------------------------+-----------------+------------------+\n");
    }
    printf("\n");
}

/***** Génerer un numéro unique au livre *****/
int numUnqiueLiv()
{
    int maxNum = 0;
    int numLiv;
    listeLiv *Liv;
    int i;
    for (i = 0; i < nbOfCateg; i++)
    {
        Liv = array[i].firstLiv;
        while (Liv != NULL)
        {
            numLiv = Liv->info->num_liv;
            maxNum = max(maxNum, numLiv);
            Liv = Liv->next;
        }
    }
    return maxNum + 1;
}

/***** Pour ajouter un livre au tableau *****/
void ajouterLiv(liv *info)
{
    int i;
    for (i = 0; i < nbOfCateg; i++)
        if (strcmp(array[i].categ_liv, info->categ_liv) == 0)
            break;
    if (i == nbOfCateg)
    {
        if (nbOfCateg == MAX)
            return;
        strcpy(array[i].categ_liv, info->categ_liv);
        nbOfCateg++;
    }
    listeLiv *newLiv = Malloc(listeLiv);
    newLiv->info = info;
    newLiv->next = NULL;
    if (array[i].firstLiv == NULL)
    {
        array[i].firstLiv = newLiv;
        return;
    }
    listeLiv *p = array[i].firstLiv;
    listeLiv *pred;
    while (p != NULL)
    {
        pred = p;
        p = p->next;
    }
    pred->next = newLiv;
}

/***** Pour inserer les infos du livre *****/
void insererLiv()
{
    liv *info = Malloc(liv);
    // Génerer un numéro unique au livre
    info->num_liv = numUnqiueLiv();
    // Initialiser le numéro d'adhérent qui emprunte ce livre
    info->emprunteur_liv = 0; // 0 : aucun adhérent à emprunter ce livre
    // Saisir les infos de livre
    printf("\t\tSaisir les infos de livre:\n");
    printf("\t\t\tSon titre: ");
    gets(info->titre_liv);
    printf("\t\t\tSa cat%cgorie: ", 130);
    gets(info->categ_liv);
    printf("\t\t\tLe nom de l'auteur: ");
    gets(info->auteur.nom_aut);
    printf("\t\t\tLe pr%cnom de l'auteur: ", 130);
    gets(info->auteur.prenom_aut);
    ajouterLiv(info);
}

/***** Pour rechercher sur un livre (par sa catégorie et son titre) *****/
liv *rechercherLiv(char *categ_liv, char *titre_liv)
{
    int i;
    for (i = 0; i < nbOfCateg; i++)
        if (strcmp(array[i].categ_liv, categ_liv) == 0)
            break;
    if (i != nbOfCateg)
    {
        listeLiv *p = array[i].firstLiv;
        while (p != NULL)
        {
            if (strcmp(p->info->titre_liv, titre_liv) == 0)
                return p->info;
            p = p->next;
        }
    }
    liv *info = NULL;
    return info;
}

/***** Pour modifier les infos d'un livre *****/
void modifierLiv(char *categ_liv, char *titre_liv)
{
    liv *info = rechercherLiv(categ_liv, titre_liv);
    if (info == NULL)
    {
        printf("\n\t\t\t%s n'existe pas!\n\n", titre_liv);
        return;
    }
    printf("\t\tSaisir les nouvelles infos de livre:\n");
    printf("\t\t\tSon titre: ");
    gets(info->titre_liv);
    printf("\t\t\tLe nom de l'auteur: ");
    gets(info->auteur.nom_aut);
    printf("\t\t\tLe pr%cnom de l'auteur: ", 130);
    gets(info->auteur.prenom_aut);
}

/***** Pour suprrimer un livre *****/
void supprimerLiv(char *categ_liv, char *titre_liv)
{
    int i;
    for (i = 0; i < nbOfCateg; i++)
        if ((strcmp(array[i].categ_liv, categ_liv) == 0))
            break;
    if (i == nbOfCateg)
    {
        printf("\n\t\t\t%s n'existe pas!\n\n", titre_liv);
        return;
    }
    listeLiv *p = array[i].firstLiv;
    listeLiv *pred;
    while ((p != NULL) && (strcmp(p->info->titre_liv, titre_liv) != 0))
    {
        pred = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("\n\t\t\t%s n'existe pas!\n\n", titre_liv);
        return;
    }
    if (p == array[i].firstLiv)
        array[i].firstLiv = p->next;
    else
        pred->next = p->next;
    free(p);
}