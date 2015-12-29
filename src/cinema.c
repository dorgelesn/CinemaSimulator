/* coiffeur.c */

#include "../include/global.h"
#include "../include/parseConfig.h"



int main()
{
    nbClientsAttente=0;
    nbClientsAttenteAuto=0;
    nbAppelCaisse=0;
    nbAbonneeAttente=0;
    nbAbonnee=0;
    nbAbonneeAcheteBillet=0;
    int num;
    pthread_mutex_init(&mutex_attenteClient, NULL);
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir,NULL);
    pthread_cond_init(&attendreAuto, NULL);
    pthread_cond_init(&dormirAuto,NULL);
    pthread_cond_init(&attendreAbonnee,NULL);
    
    srand(time(NULL));
    parserConfig();
    pthread_t tid2[NbClients+Nbcaisses+NbcaissesAuto];
    tid=tid2;
    //tid=malloc((NbClients+Nbcaisses+NbcaissesAuto)*sizeof(pthread_t));
    // creation des salles /!\ fuite memoire
    
    int testt;
    
    //lesSalles[0]->film = lesSalles[1]->film;
    //  printf("adresses %d %d\n",lesSalles[0]->film, lesSalles[1]->film);
    
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d %d\n",lesSalles[testt]->numero, (lesSalles[testt]->film)->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    sleep(20);
    
    
    
    // creation des caisses et des caisses auto /!\ fuite memoire
    for(num=0;num<Nbcaisses+NbcaissesAuto;num++){
        if(num<NbcaissesAuto)
        {
            argStruct *numCaisse = malloc(sizeof(*numCaisse));
            numCaisse->num = num;
            pthread_create(tid+num,0,(void *(*)())fonc_caisseAuto,numCaisse);
        }else
        {
            argStruct *numCaisse = malloc(sizeof(*numCaisse));
            numCaisse->num = num-NbcaissesAuto;
            pthread_create(tid+num,0,(void *(*)())fonc_caisse,numCaisse);
        }
    }
    
    //creation des threads clients /!\ fuite memoire
    for(num=Nbcaisses+NbcaissesAuto;num<(NbClients+Nbcaisses+NbcaissesAuto)/2;num ++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num-Nbcaisses-NbcaissesAuto;
        
        int rng = rand()%(100-0) +0;
        if(rng<=PourcentAbonnee)
            pthread_create(tid+num,0,(void *(*)())fonc_abonnee,numClient);
        else        
            pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    sleep(10);
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("Abonnees :\n sont venus : %d\nOn eu leur billet :%d\n ",nbAbonnee, nbAbonneeAcheteBillet);
    printf("#########################################\n");
    sleep(10);
    for(num=(NbClients+Nbcaisses+NbcaissesAuto)/2;num<(NbClients+Nbcaisses+NbcaissesAuto);num++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num-Nbcaisses-NbcaissesAuto;
        int rng = rand()%(100-0) +0;
        if(rng<=PourcentAbonnee)
            pthread_create(tid+num,0,(void *(*)())fonc_abonnee,numClient);
        else        
            pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    
        sleep(20);
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("Abonnees :\n sont venus : %d\nOn eu leur billet :%d\n ",nbAbonnee, nbAbonneeAcheteBillet);
    printf("#########################################\n");
    
    //attend la fin de toutes les threads clients
    for(num=0;num<NbClients+Nbcaisses+NbcaissesAuto;num ++)
        pthread_join(tid[num],NULL);

    
    /* liberation des ressources");*/
    
    
    
    exit(0);
}
