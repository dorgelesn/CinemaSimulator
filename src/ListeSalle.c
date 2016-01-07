#include "../include/global.h"

/*
 * 
 * Les salles sont stockées dans une liste chainée car on
 * souhaite avoir un ajout dynamique des salles en fonction du nombre de billets 
 * refusés pour un film.
 * 
 */

ListeSalle ajouterSalle(ListeSalle liste, SalleStruct* valeur)
{
    //NBSalles++;
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->nxt = liste;
    return nouvelElement;
    
}

ListeSalle supprimerElementEnTete()
{
    if(lesSallesList != NULL)
    {
        element* aRenvoyer = lesSallesList->nxt;
        printf("netoyage de la salle n°%d\n",lesSallesList->val->numero);
        free(lesSallesList->val);
        free(lesSallesList);
        return aRenvoyer;
    }
    else
    {
        return NULL;
    }
}

void detruireLesSalles(){
    while((lesSallesList)!=NULL)
    {
        lesSallesList=supprimerElementEnTete();
    }
}

void afficherSalles()
{
    element *tmp = lesSallesList;
    while(tmp != NULL)
    {
        printf("Salle n° %d film %s CAPACITE %d %d\n",tmp->val->numero, (tmp->val->film)->titre, tmp->val->CAPACITE, tmp->val->NBPersonnes);
        tmp = tmp->nxt;

    }
}