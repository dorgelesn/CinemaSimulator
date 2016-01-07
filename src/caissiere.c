#include "../include/global.h"



//La caissière attend un client, si il y en a un Elle l'appelle et lui vends son billet 

void VendreBillet(int numCaisse){
    
    pthread_mutex_lock(&mutex_attenteClient);
    
    if(nbClientsAttente == 0 && nbAbonneeAttente == 0)
    {
        printf("pas de clients à la caisse numero %d \n",numCaisse);
        pthread_cond_wait(&dormir, &mutex_attenteClient);
        
        //	usleep(200000);	
    }
    printf("la caissière n° %d appelle un client !\n",numCaisse);
    nbAppelCaisse++;
    //Les abonnees son prioritaires.
    if(nbAbonneeAttente==0)
        pthread_cond_signal(&attendre);
    else
        pthread_cond_signal(&attendreAbonnee);
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void * fonc_caisse(void *i)
{                          
    argStruct *arg = i;
    while (1)  {
        VendreBillet(arg->num);
        usleep(200000);
    }
}   