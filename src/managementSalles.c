#include "../include/global.h"
 
 
void * fonc_managerSalles(void *i){
    
    pthread_mutex_lock(&mutex_attenteClient);
    SalleStruct* this = (SalleStruct*)i; 
    
    while(1)
    {
        
        pthread_cond_wait(&(demarrer),&mutex_attenteClient);
        
        pthread_cond_broadcast(&(conditionEntrerSalle));
        printf("Reveillee\n");
       // pthread_cond_wait(&(this->toutLemondeDansLaSalle),&mutex_attenteClient);
        printf("Le film %s commence\n",this->film->titre);
        //duree du film
        //usleep((this->film->duree)*10);
        
        //pthread_cond_broadcast(&(this->filmTermine));
        //pthread_cond_wait(&(this->toutLemondeEstSorti),&mutex_attenteClient);
        
        this->NBPersonnes=0;
        
        
    } 
        pthread_mutex_unlock(&mutex_attenteClient);
        return 0;
    
    
}