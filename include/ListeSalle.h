typedef struct element element;
struct element
{
    SalleStruct* val;
    struct element *nxt;

};

typedef element* ListeSalle;

ListeSalle ajouterSalle(ListeSalle liste, SalleStruct* salle);

void detruireLesSalles();
void afficherSalles();