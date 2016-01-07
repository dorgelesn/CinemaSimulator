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
    NbSalleMax=0;
    nbClientInternet=0;
    passed=0;
    lesSallesList = NULL;
    int num;
    pthread_mutex_init(&mutex_attenteClient, NULL);
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir,NULL);
    pthread_cond_init(&attendreAuto, NULL);
    pthread_cond_init(&dormirAuto,NULL);
    pthread_cond_init(&conditionEntrerSalle, NULL);
    pthread_cond_init(&demarrer,NULL);
    pthread_cond_init(&attendreAbonnee,NULL);
    signal(SIGINT, netoyerFin);
    
    srand(time(NULL));
    parserConfig();
    //pthread_t tid2[NbClients+Nbcaisses+NbcaissesAuto];
    tid=malloc((NbClients+Nbcaisses+NbcaissesAuto)*sizeof(pthread_t));
    arguments=malloc((NbClients+Nbcaisses+NbcaissesAuto)*sizeof(argStruct*));
    
    int j;
    for(j = 0; j<(NbClients+Nbcaisses+NbcaissesAuto);j++)
    {
        tid[j]=(pthread_t)NULL;
        arguments[j]=NULL;
    }
    
    afficherSalles();
    //int testt;
    
    /*for(testt=0; testt < NBSalles; testt++){
     *     printf("Salle n° %d film %s CAPACITE %d %d\n",lesSalles[testt]->numero, (lesSalles[testt]->film)->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
     *        
}*/
    sleep(3);
    signal(SIGINT, netoyer);
    
    
    
    // creation des caisses et des caisses auto /!\ fuite memoire
    for(num=0;num<Nbcaisses+NbcaissesAuto;num++){
        if(num<NbcaissesAuto)
        {
            arguments[num] = malloc(sizeof(argStruct*));
            argStruct* numCaisse = arguments[num];
            numCaisse->num = num;
            
            pthread_create(tid+num,0,(void *(*)())fonc_caisseAuto,numCaisse);
        }else
        {
            arguments[num] = malloc(sizeof(argStruct*));
            argStruct* numCaisse = arguments[num];
            numCaisse->num = num-NbcaissesAuto;
            pthread_create(tid+num,0,(void *(*)())fonc_caisse,numCaisse);
        }
    }
    ListeSalle l = lesSallesList;
    int h;
    for(h=0;h<NBSalles;h++){
        pthread_create(threadManagement+h,0,(void *(*)())fonc_managerSalles,l->val);
        l=l->nxt;
    }
    sleep(10);
    
    //creation des threads clients /!\ fuite memoire
    for(num=Nbcaisses+NbcaissesAuto;num<(NbClients+Nbcaisses+NbcaissesAuto);num ++){
        arguments[num] = malloc(sizeof(argStruct*));
        argStruct* numClient=arguments[num];
        numClient->num = num-Nbcaisses-NbcaissesAuto;
        
        
        int rng = rand()%(100-0) +0;
        if(rng<=PourcentAbonnee)
            pthread_create(tid+num,0,(void *(*)())fonc_abonnee,numClient);
        else        
            pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    
    
    //attend la fin de toutes les threads clients
    for(num=Nbcaisses+NbcaissesAuto;num<NbClients+Nbcaisses+NbcaissesAuto;num ++)
        pthread_join(tid[num],NULL);
    
    printf("###fin des clients###\n");
    
    for(num=0; num<Nbcaisses+NbcaissesAuto;num++){
        pthread_cancel(tid[num]);
    }
    
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    afficherSalles();
    printf("Abonnees :\n sont venus : %d\nOn eu leur billet :%d\n ",nbAbonnee, nbAbonneeAcheteBillet);
    printf("#########################################\n");
    signal(SIGINT, netoyerFin);
    sleep(10);
    netoyerFin();
    
    /* liberation des ressources");*/
    
    
    
    exit(0);
}
