#include "../include/global.h"

void * fonc_client(void *i)
{
    argStruct *arg = i;
    //50% des clients vont au caisses et 50% vont au caisses automatiques
    int random = rand()%(100-0) +0;
        if(random>60)
        {
            AcheterBillet(arg->num);
            printf("Le client %d à acheté son billet auprès d'une caissière\n", arg->num);
        }
        else
            if(random<30)
        {
            AcheterBilletAuto(arg->num);
            printf("Le client %d à acheté son billet à la caisse automatique\n", arg->num);
        }
        else
        {
            AcheterBilletInternet(arg->num);
            printf("Le client %d à acheté son billet sur internet\n", arg->num);
        }
    
    
    /* temps de vente */
    //usleep(200000);
    
    return 0;
}

void AcheterBilletInternet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttente++;
    printf("Le client %d fait son achat sur internet \n",i);
    choisirFilm(i);    
    nbClientsAttente --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void AcheterBillet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttente++;
    pthread_cond_signal(&dormir);
    printf("Le client %d arrive \n",i);
    pthread_cond_wait(&attendre,&mutex_attenteClient);
    choisirFilm(i);
    
    nbClientsAttente --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

void AcheterBilletAuto(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttenteAuto++;
    pthread_cond_signal(&dormirAuto);
    printf("Le client %d arrive en caisse automatique\n",i);
    pthread_cond_wait(&attendreAuto,&mutex_attenteClient);
    choisirFilm(i);
    
    nbClientsAttenteAuto --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

//le client choisis un film, si il n'y a plus de place il y a 80 % de chance
// pour que le client quitte le cinema, sinon il choisis un autre film.

void choisirFilm(int i)
{
    
    int film = rand()%(NBFilms-0) +0;
    printf("client %d veut voir le film %s\n",i, lesFilms[film]->titre);
    
    SalleStruct * laSalle = choixSalle(lesFilms[film]);
    
    if(laSalle == NULL)
    {
        printf("il n'y a plus de place pour le film %s\n",lesSalles[film]->film->titre);
        int random = rand()%(100-0) +0;
        if(random >= 80)
        {
            printf("le client %d va essayer de voir un autre film\n",i);
            choisirFilm(i);
        }
        else{
            printf("le client %d sort du cinema car il n'y avait plus de place pour son film\n",i);
        }
            
        
    }
    else
    {
        printf("client %d à acheté sa place pour le film %s dans la salle %d à la place %d\n",i,laSalle->film->titre,laSalle->numero,laSalle->NBPersonnes+1);
        //Ajouter un mutex pour la capaacité des salles quand il y aura 3 moyens de commander les billets 
        (laSalle->NBPersonnes)++;
        
    }
    
    
}

SalleStruct* choixSalle(FilmStruct * unFilm)
{
    int i;
    for(i=0;i<NBSalles;i++){
            
        if(lesSalles[i]->film == unFilm){
            
            if(lesSalles[i]->NBPersonnes<lesSalles[i]->CAPACITE)
            {
                return lesSalles[i];
            }
            
        }
        
    }
    return NULL;
}








