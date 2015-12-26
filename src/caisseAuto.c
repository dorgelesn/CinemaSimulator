#include "../include/global.h"


void VendreBilletAuto(int numCaisse){
    
    pthread_mutex_lock(&mutex_attenteClient);
    
    if(nbClientsAttenteAuto == 0)
    {
        printf("pas de clients à la caisse auto n° %d \n",numCaisse);
        pthread_cond_wait(&dormirAuto, &mutex_attenteClient);
        
        //	usleep(200000);	
    }
    printf("Un client Arrive à la caisse automatique n° %d  !\n",numCaisse);
    nbAppelCaisse++;
    pthread_cond_signal(&attendreAuto);
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void * fonc_caisseAuto(void *i)
{                          
    argStruct *arg = i;
    while (1)  {
        VendreBilletAuto(arg->num);
        usleep(300000);
    }
}   