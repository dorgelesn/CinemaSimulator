#include "../include/global.h"
#define Salle SalleStruct

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
        
        if(nbClientsAttenteAuto==0 && nbClientsAttente==0)
        {
            int i;
            ListeSalle l = lesSallesList;
            for(i=0;i<NBSalles;i++){
                pthread_cond_signal(&(l->val->demarrer));
                l=l->nxt;
            }
        }
        
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
    
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;    
    
}






