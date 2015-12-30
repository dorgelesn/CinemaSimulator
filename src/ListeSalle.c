#include "../include/global.h"
ListeSalle ajouterSalle(ListeSalle liste, SalleStruct* valeur)
{
    NBSalles++;
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->nxt = liste;
    return nouvelElement;
    
}

void detruireLesSalles(){
    
}