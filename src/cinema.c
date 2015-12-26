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
    srand(time(NULL));
    
    // creation des salles /!\ fuite memoire
    
    int numSalle;
    char *lesfilms[5]={"toto au cine","starw wars","maze runner","spectre","un avion se crash"};
    for(numSalle =1; numSalle <= NBSalles; numSalle++){
            SalleStruct * uneSalle = malloc(sizeof(SalleStruct));
            uneSalle->film=lesfilms[numSalle-1];
            uneSalle->numero=numSalle;
            uneSalle->CAPACITE = 120;
            lesSalles[numSalle-1] = uneSalle;
    }
    
    int testt;
    
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d \n",lesSalles[testt]->numero, lesSalles[testt]->film, lesSalles[testt]->CAPACITE);   
        
    }
    
    // creation des caisses /!\ fuite memoire
    for(num=0;num<Nbcaisses;num++){
        argStruct *numCaisse = malloc(sizeof(*numCaisse));
        numCaisse->num = num;
        pthread_create(tid+num,0,(void *(*)())fonc_caisse,numCaisse);
    }
    
    //creation des threads clients /!\ fuite memoire
    for(num=Nbcaisses;num<(NbClients+Nbcaisses)/2;num ++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num-Nbcaisses;
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    sleep(10);
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("#########################################\n");
    sleep(10);
    for(num=(NbClients+Nbcaisses)/2;num<(NbClients+Nbcaisses);num++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num-Nbcaisses;
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    
        sleep(20);
    printf("#########################################\n");
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("#########################################\n");
    
    //attend la fin de toutes les threads clients
    for(num=0;num<NbClients+Nbcaisses;num ++)
        pthread_join(tid[num],NULL);

    
    /* liberation des ressources");*/
    
    
    
    exit(0);
}
