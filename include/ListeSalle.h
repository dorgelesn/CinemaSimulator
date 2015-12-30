typedef struct element element;
struct element
{
    SalleStruct* val;
    struct element *nxt;

};

typedef element* ListeSalle;

ListeSalle ajouterSalle(ListeSalle lesSalles, SalleStruct* salle);

void detruireLesSalles();