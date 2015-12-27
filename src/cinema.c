/* coiffeur.c */

#include "../include/global.h"



int main()
{
    nbClientsAttente=0;
    nbClientsAttenteAuto=0;
    nbAppelCaisse=0;
    int num;
    pthread_mutex_init(&mutex_attenteClient, NULL);
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir,NULL);
    pthread_cond_init(&attendreAuto, NULL);
    pthread_cond_init(&dormirAuto,NULL);
    
    srand(time(NULL));
    
    // creation des salles /!\ fuite memoire
    
    int numSalle;
    char *nom[5]={"toto au cine","starw wars","maze runner","spectre","un avion se crash"};
    char *genres[5]={"comedie","science-fiction","aventure","action","drame"};
    int duree[5]={120,90,180,111,10};
    int horaire[5]={1,2,1,2,1};
    int pegi[5]={3,12,12,16,18};
    
    int i;
    for(i = 0; i<5; i++)
    {
        FilmStruct * unFilm = malloc(sizeof(FilmStruct));
        unFilm->titre = nom[i];
        unFilm->genre = genres[i];
        unFilm->duree = duree[i];
        unFilm->horaire = horaire[i];
        unFilm->pegi = pegi[i];
        lesFilms[i] = unFilm;
        
    }
    
    for(numSalle =1; numSalle <= NBSalles; numSalle++){
            SalleStruct * uneSalle = malloc(sizeof(SalleStruct));
            uneSalle->film=lesFilms[numSalle-1];
            uneSalle->numero=numSalle;
            uneSalle->CAPACITE = 120;
            lesSalles[numSalle-1] = uneSalle;
    }
    
    int testt;
    
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d \n",lesSalles[testt]->numero, (lesSalles[testt]->film)->titre, lesSalles[testt]->CAPACITE);   
        
    }
    
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
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    sleep(10);
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("#########################################\n");
    sleep(10);
    for(num=(NbClients+Nbcaisses+NbcaissesAuto)/2;num<(NbClients+Nbcaisses+NbcaissesAuto);num++){
        argStruct *numClient = malloc(sizeof(*numClient));
        numClient->num = num-Nbcaisses-NbcaissesAuto;
        pthread_create(tid+num,0,(void *(*)())fonc_client,numClient);
    }
    
        sleep(20);
    printf("#########################################\n");
    printf("appels caisse %d\n",nbAppelCaisse);
    for(testt=0; testt < NBSalles; testt++){
     printf("Salle n° %d film %s CAPACITE %d NBPersonnes %d\n",lesSalles[testt]->numero, lesSalles[testt]->film->titre, lesSalles[testt]->CAPACITE, lesSalles[testt]->NBPersonnes);   
        
    }
    printf("#########################################\n");
    
    //attend la fin de toutes les threads clients
    for(num=0;num<NbClients+Nbcaisses+NbcaissesAuto;num ++)
        pthread_join(tid[num],NULL);

    
    /* liberation des ressources");*/
    
    
    
    exit(0);
}
