typedef struct SalleStruct{
    int CAPACITE;
    int NBPersonnes;
    FilmStruct * film;
    int numero;
    pthread_cond_t conditionEntrerSalle;
    pthread_cond_t filmTermine;
}SalleStruct;