#include "../include/global.h"
 
 
void * fonc_managerSalles(void *i){
    
    pthread_mutex_lock(&mutex_attenteClient);
    SalleStruct* this = (SalleStruct*)i; 
    
    //printf("test %d %s\n",&(this->demarrer), this->film->titre);
    
    while(1)
    {
        pthread_cond_wait(&(this->demarrer),&mutex_attenteClient);
        
       // printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        
        this->personnesAttendent=this->NBPersonnes;
        pthread_cond_signal(&(this->conditionEntrerSalle));
        pthread_cond_wait(&(this->toutLemondeDansLaSalle),&mutex_attenteClient);
        printf("Le film %s commence\n",this->film->titre);
        //duree du film
        usleep((this->film->duree)*10);
        
        this->personnesAttendent=this->NBPersonnes;
        pthread_cond_signal(&(this->filmTermine));
        pthread_cond_wait(&(this->toutLemondeEstSorti),&mutex_attenteClient);
        
        this->NBPersonnes=0;
        
        
    } 
        pthread_mutex_unlock(&mutex_attenteClient);
        return 0;
    
    
}