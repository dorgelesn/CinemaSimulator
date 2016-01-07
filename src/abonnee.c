#include "../include/global.h"
#define Salle SalleStruct

//L'abonne à le même fonctionnement que le client. C'est les caissières qui gèrent les priorités

void * fonc_abonnee(void *i)
{
    argStruct *arg = i;
    nbAbonnee++;
    Salle* maSalle=NULL;
    //50% des clients vont au caisses et 50% vont au caisses automatiques
    int random = rand()%(100-0) +0;
    if((random>20)&&(Nbcaisses!=0))
    {
        maSalle=AcheterBilletAbonnee(arg->num);
        printf("L'abonnee %d à acheté son billet auprès d'une caissière\n", arg->num);
    }
    else
        if((random<10)&&(NbcaissesAuto!=0))
        {
            maSalle=AcheterBilletAutoAbonnee(arg->num);
            printf("L'abonnee %d à acheté son billet à la caisse automatique\n", arg->num);
        }
        else
        {
            maSalle=AcheterBilletInternetAbonnee(arg->num);
            printf("L'abonnee %d à acheté son billet sur internet\n", arg->num);
        }
        
        checkFileDattente();
        
        allerVoirFilm(maSalle, arg, "abonnee");
        printf("L'abonnee %d sort du cinema\n", arg->num);
        
        /* temps de vente */
        //usleep(200000);
        
        return 0;
}

Salle * AcheterBilletInternetAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    Salle * laSalle=NULL;
    printf("L'abonnee %d fait son achat sur internet \n",i);
    laSalle=choisirFilm(i);
    if(laSalle!=NULL)
    {
        nbAbonneeAcheteBillet++;
        
    }
   // checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;
    
}

Salle * AcheterBilletAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    Salle * laSalle=NULL;
    nbAbonneeAttente++;
    pthread_cond_signal(&dormir);
    printf("L'abonnee %d arrive \n",i);
    pthread_cond_wait(&attendreAbonnee,&mutex_attenteClient);
    laSalle=choisirFilm(i);
    if(laSalle!=NULL)
    {
        
        nbAbonneeAcheteBillet++;
    }
    nbAbonneeAttente --;
   // checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;
    
}

Salle * AcheterBilletAutoAbonnee(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    Salle * laSalle=NULL;
    nbClientsAttenteAuto++;
    pthread_cond_signal(&dormirAuto);
    printf("L'abonnee %d arrive en caisse automatique\n",i);
    pthread_cond_wait(&attendreAuto,&mutex_attenteClient);
    laSalle=choisirFilm(i);
    if(laSalle!=NULL)
    {
        nbAbonneeAcheteBillet++;
    }
    nbClientsAttenteAuto --;
    //checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;    
    
}






