/* coiffeur.c */

#include "../include/global.h"



int main()
{
    nbClientsAttente=0;
    nbAppelCaisse=0;
    int num;
    pthread_mutex_init(&mutex_attenteClient, NULL);
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir,NULL);
    
    // creation des caisses
    for(num=0;num<Nbcaisses;num++){
        argStruct *numCaisse = malloc(sizeof(*numCaisse));
        numCaisse->num = num;
        pthread_create(tid+num,0,(void *(*)())fonc_caisse,numCaisse);
    }
    
    //creation des threads clients
    for(num=Nbcaisses;num<(NbClients+Nbcaisses)/2;num ++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num;
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    sleep(20);
    for(num=(NbClients+Nbcaisses)/2;num<(NbClients+Nbcaisses);num++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num;
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    //attend la fin de toutes les threads clients
    for(num=0;num<NbClients+Nbcaisses;num ++)
        pthread_join(tid[num],NULL);
    
    
    /* liberation des ressources");*/
    
    exit(0);
}
