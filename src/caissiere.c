#include "../include/global.h"

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

void * fonc_caisse(void *i)
{                          
    argStruct *arg = i;
    while (1)  {
        VendreBillet(arg->num);
        usleep(200000);
    }
}   