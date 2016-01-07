typedef struct SalleStruct{
    int CAPACITE;
    int NBPersonnes;
    FilmStruct * film;
    int numero;
    int personnesAttendent;
    int personnesAttendent2;
    
    pthread_cond_t conditionEntrerSalle;
    pthread_cond_t toutLemondeDansLaSalle;
    pthread_cond_t toutLemondeEstSorti;
    pthread_cond_t filmTermine;
    pthread_cond_t demarrer;
}SalleStruct;