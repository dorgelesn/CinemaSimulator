#include "../include/global.h"

void * fonc_client(void *i)
{
    argStruct *arg = i;
    AcheterBillet(arg->num);
    
    /* temps de vente */
    //usleep(200000);
    printf("Le client %d à acheté son billet auprès d'une caissière\n", arg->num);
    return 0;
}

void AcheterBillet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttente++;
    pthread_cond_signal(&dormir);
    printf("Le client %d arrive \n",i);
    pthread_cond_wait(&attendre,&mutex_attenteClient);
    printf("client %d vient acheter sa place \n",(int)i);
    nbClientsAttente --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}