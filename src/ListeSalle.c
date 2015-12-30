#include "../include/global.h"
ListeSalle ajouterSalle(ListeSalle liste, SalleStruct* valeur)
{
    //NBSalles++;
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->nxt = liste;
    return nouvelElement;
    
}

void detruireLesSalles(){
    
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