/* coiffeur.c */

#include <stdio.h>
#include <pthread.h>
#define Nbcaisses 8 
#define NbClients 1000


pthread_t tid[NbClients+Nbcaisses];
pthread_mutex_t mutex_attenteClient;
pthread_cond_t attendre, dormir;

int nbClientsAttente=0;
int nbAppelCaisse=0;

void VendreBillet(int numCaisse){
    
    pthread_mutex_lock(&mutex_attenteClient);
    
    if(nbClientsAttente == 0)
    {
        printf("pas de clients à la caisse numero %d \n",numCaisse);
        printf("appels caisse %d\n",nbAppelCaisse);	
        pthread_cond_wait(&dormir, &mutex_attenteClient);
        
        //	usleep(200000);	
    }
    printf("la caissière n° %d appelle un client !\n",numCaisse);
    nbAppelCaisse++;
    pthread_cond_signal(&attendre);
    pthread_mutex_unlock(&mutex_attenteClient);
    
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

void * fonc_caisse(void *i)
{                          
    
    while (1)  {
        VendreBillet((int)i);
        usleep(200000);
    }
}

void * fonc_client(void *i)
{
    int numClient = (int)i;
    AcheterBillet(numClient);
    
    /* temps de vente */
    //usleep(200000);
    printf("Le client %d à acheté son billet auprès d'une caissière\n", (int) i);
}


int main()
{
    int num;
    pthread_mutex_init(&mutex_attenteClient, NULL);
    pthread_cond_init(&attendre, NULL);
    pthread_cond_init(&dormir,NULL);
    
    // creation des caisses
    for(num=0;num<Nbcaisses;num++)
        pthread_create(tid+num,0,(void *(*)())fonc_caisse,(void*)num);
    
    //creation des threads clients
    for(num=Nbcaisses;num<(NbClients+Nbcaisses)/2;num ++)
        pthread_create(tid+num,0,(void *(*)())fonc_client,(void*)num);
    sleep(20);
    for(num=(NbClients+Nbcaisses)/2;num<(NbClients+Nbcaisses);num++)
        pthread_create(tid+num,0,(void *(*)())fonc_client,(void*)num);
    //attend la fin de toutes les threads clients
    for(num=0;num<NbClients+Nbcaisses;num ++)
        pthread_join(tid[num],NULL);
    
    
    /* liberation des ressources");*/
    
    exit(0);
}
