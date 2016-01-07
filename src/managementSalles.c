#include "../include/global.h"
 
 
 /*
  * 
  * Cette fonction gère le lancement des séances lorsque tous les clients sont passés en caisse.
  * 
  */
 
void * fonc_managerSalles(void *i){
    
    pthread_mutex_lock(&mutex_attenteClient);
    SalleStruct* this = (SalleStruct*)i; 
    
    while(1)
    {
        
        pthread_cond_wait(&(demarrer),&mutex_attenteClient);
        
        pthread_cond_broadcast(&(conditionEntrerSalle));
        printf("Le film %s commence\n",this->film->titre);

        this->NBPersonnes=0;
        
        
    } 
        pthread_mutex_unlock(&mutex_attenteClient);
        return 0;
    
    
}