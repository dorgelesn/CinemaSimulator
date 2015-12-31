#include "../include/global.h"

void * fonc_abonnee(void *i)
{
    argStruct *arg = i;
    nbAbonnee++;
    //50% des clients vont au caisses et 50% vont au caisses automatiques
    int random = rand()%(100-0) +0;
        if((random>20)&&(Nbcaisses!=0))
        {
            AcheterBilletAbonnee(arg->num);
            printf("L'abonnee %d à acheté son billet auprès d'une caissière\n", arg->num);
        }
        else
            if((random<10)&&(NbcaissesAuto!=0))
        {
            AcheterBilletAutoAbonnee(arg->num);
            printf("L'abonnee %d à acheté son billet à la caisse automatique\n", arg->num);
        }
        else
        {
            AcheterBilletInternetAbonnee(arg->num);
            printf("L'abonnee %d à acheté son billet sur internet\n", arg->num);
        }
    
    
    /* temps de vente */
    //usleep(200000);
    
    return 0;
}

void AcheterBilletInternetAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    printf("L'abonnee %d fait son achat sur internet \n",i);
    if(choisirFilm(i)==1){
        nbAbonneeAcheteBillet++;
        
    }
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void AcheterBilletAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbAbonneeAttente++;
    pthread_cond_signal(&dormir);
    printf("L'abonnee %d arrive \n",i);
    pthread_cond_wait(&attendreAbonnee,&mutex_attenteClient);
    if(choisirFilm(i)==1)
    {
     
        nbAbonneeAcheteBillet++;
    }
    nbAbonneeAttente --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void AcheterBilletAutoAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttenteAuto++;
    pthread_cond_signal(&dormirAuto);
    printf("L'abonnee %d arrive en caisse automatique\n",i);
    pthread_cond_wait(&attendreAuto,&mutex_attenteClient);
    if(choisirFilm(i)==1)
    {
        nbAbonneeAcheteBillet++;
    }
    nbClientsAttenteAuto --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}






